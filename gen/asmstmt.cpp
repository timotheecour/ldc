// Taken from GDC source tree. Original by David Friedman.
// Released under the Artistic License found in dmd/artistic.txt

#include "gen/llvm.h"
#include "llvm/InlineAsm.h"

//#include "d-gcc-includes.h"
//#include "total.h"
#include "dmd/statement.h"
#include "dmd/scope.h"
#include "dmd/declaration.h"
#include "dmd/dsymbol.h"

#include <cassert>
#include <deque>
#include <iostream>
#include <sstream>
#include <cstring>

//#include "d-lang.h"
//#include "d-codegen.h"

#include "gen/irstate.h"
#include "gen/dvalue.h"
#include "gen/tollvm.h"
#include "gen/logger.h"
#include "gen/todebug.h"
#include "gen/llvmhelpers.h"

typedef enum {
    Arg_Integer,
    Arg_Pointer,
    Arg_Memory,
    Arg_FrameRelative,
    Arg_LocalSize,
    Arg_Dollar
} AsmArgType;

typedef enum {
    Mode_Input,
    Mode_Output,
    Mode_Update
} AsmArgMode;

struct AsmArg {
    AsmArgType   type;
    Expression * expr;
    AsmArgMode   mode;
    AsmArg(AsmArgType type, Expression * expr, AsmArgMode mode) {
	this->type = type;
	this->expr = expr;
	this->mode = mode;
    }
};

struct AsmCode {
    char *   insnTemplate;
    unsigned insnTemplateLen;
    Array    args; // of AsmArg
    unsigned moreRegs;
    unsigned dollarLabel;
    int      clobbersMemory;
    AsmCode() {
	insnTemplate = NULL;
	insnTemplateLen = 0;
	moreRegs = 0;
	dollarLabel = 0;
	clobbersMemory = 0;
    }
};

AsmStatement::AsmStatement(Loc loc, Token *tokens) :
    Statement(loc)
{
    this->tokens = tokens; // Do I need to copy these?
    asmcode = 0;
    asmalign = 0;
    refparam = 0;
    naked = 0;
    regs = 0;

    isBranchToLabel = NULL;
}

Statement *AsmStatement::syntaxCopy()
{
    // copy tokens? copy 'code'?
    AsmStatement * a_s = new AsmStatement(loc,tokens);
    a_s->asmcode = asmcode;
    a_s->refparam = refparam;
    a_s->naked = naked;
    a_s->regs = a_s->regs;
    return a_s;
}

void AsmStatement::toCBuffer(OutBuffer *buf, HdrGenState *hgs)
{
    bool sep = 0, nsep = 0;
    buf->writestring("asm { ");
    
    for (Token * t = tokens; t; t = t->next) {	
	switch (t->value) {
	case TOKlparen:
	case TOKrparen:
	case TOKlbracket:
	case TOKrbracket:
	case TOKcolon:
	case TOKsemicolon:
	case TOKcomma:
	case TOKstring:
	case TOKcharv:
	case TOKwcharv:
	case TOKdcharv:
	    nsep = 0;
	    break;
	default:
	    nsep = 1;
	}
	if (sep + nsep == 2)
    		buf->writeByte(' ');
	sep = nsep;
	buf->writestring(t->toChars());
    }
    buf->writestring("; }");
    buf->writenl();
}

int AsmStatement::comeFrom()
{
    return FALSE;
}


#include "d-asm-i386.h"

bool d_have_inline_asm() { return true; }

Statement *AsmStatement::semantic(Scope *sc)
{
    bool err = false;
    if (global.params.cpu != ARCHx86)
    {
        error("inline asm is not supported for the \"%s\" architecture", global.params.llvmArch);
        err = true;
    }
    if (!global.params.useInlineAsm)
    {
        error("inline asm is not allowed when the -noasm switch is used");
        err = true;
    }
    if (err)
        fatal();

    sc->func->inlineAsm = 1;
    sc->func->inlineStatus = ILSno; // %% not sure
    // %% need to set DECL_UNINLINABLE too?
    sc->func->hasReturnExp = 1; // %% DMD does this, apparently...
    
    // empty statement -- still do the above things because they might be expected?
    if (! tokens)
	return this;
    
    AsmProcessor ap(sc, this);
    ap.run();
    return this;
}

void
AsmStatement::toIR(IRState * irs)
{
    Logger::println("AsmStatement::toIR(): %s", loc.toChars());
    LOG_SCOPE;

    // get asm block
    IRAsmBlock* asmblock = irs->asmBlock;
    assert(asmblock);

    // debug info
    if (global.params.symdebug)
        DtoDwarfStopPoint(loc.linnum);

    if (! asmcode)
    return;

    static std::string i_cns = "i";
    static std::string p_cns = "i";
    static std::string m_cns = "*m";
    static std::string mw_cns = "=*m";
    static std::string mrw_cns = "+*m";
    static std::string memory_name = "memory";

    AsmCode * code = (AsmCode *) asmcode;
    std::deque<LLValue*> input_values;
    std::deque<std::string> input_constraints;
    std::deque<LLValue*> output_values;
    std::deque<std::string> output_constraints;
    std::deque<std::string> clobbers;

// FIXME
    #define HOST_WIDE_INT long
    HOST_WIDE_INT var_frame_offset; // "frame_offset" is a macro
    bool clobbers_mem = code->clobbersMemory;
    int input_idx = 0;
    int n_outputs = 0;
    int arg_map[10];

    assert(code->args.dim <= 10);

    for (unsigned i = 0; i < code->args.dim; i++) {
	AsmArg * arg = (AsmArg *) code->args.data[i];
	
	bool is_input = true;
	LLValue* arg_val = 0;
	std::string cns;

	switch (arg->type) {
	case Arg_Integer:
	    arg_val = arg->expr->toElem(irs)->getRVal();
	do_integer:
	    cns = i_cns;
	    break;
	case Arg_Pointer:
        assert(arg->expr->op == TOKvar);
        arg_val = arg->expr->toElem(irs)->getRVal();
        cns = p_cns;

	    break;
	case Arg_Memory:
        arg_val = arg->expr->toElem(irs)->getRVal();

	    switch (arg->mode) {
	    case Mode_Input:  cns = m_cns; break;
	    case Mode_Output: cns = mw_cns;  is_input = false; break;
	    case Mode_Update: cns = mrw_cns; is_input = false; break;
	    default: assert(0); break;
	    }
	    break;
	case Arg_FrameRelative:
// FIXME
std::cout << "asm fixme Arg_FrameRelative" << std::endl;
assert(0);
/*	    if (arg->expr->op == TOKvar)
		arg_val = ((VarExp *) arg->expr)->var->toSymbol()->Stree;
	    else
		assert(0);*/
	    if ( getFrameRelativeValue(arg_val, & var_frame_offset) ) {
//		arg_val = irs->integerConstant(var_frame_offset);
		cns = i_cns;
	    } else {
		this->error("%s", "argument not frame relative");
		return;
	    }
	    if (arg->mode != Mode_Input)
		clobbers_mem = true;
	    break;
	case Arg_LocalSize:
// FIXME
std::cout << "asm fixme Arg_LocalSize" << std::endl;
assert(0);
/*	    var_frame_offset = cfun->x_frame_offset;
	    if (var_frame_offset < 0)
		var_frame_offset = - var_frame_offset;
	    arg_val = irs->integerConstant( var_frame_offset );*/
	    goto do_integer;
	default:
	    assert(0);
	}

	if (is_input) {
	    arg_map[i] = --input_idx;
	    //inputs.cons(tree_cons(NULL_TREE, cns, NULL_TREE), arg_val);
	    input_values.push_back(arg_val);
	    input_constraints.push_back(cns);
	} else {
	    arg_map[i] = n_outputs++;
	    //outputs.cons(tree_cons(NULL_TREE, cns, NULL_TREE), arg_val);
	    output_values.push_back(arg_val);
	    output_constraints.push_back(cns);
	}
    }

    // Telling GCC that callee-saved registers are clobbered makes it preserve
    // those registers.   This changes the stack from what a naked function
    // expects.
    
// FIXME
//    if (! irs->func->naked) {
	for (int i = 0; i < 32; i++) {
	    if (regs & (1 << i)) {
		//clobbers.cons(NULL_TREE, regInfo[i].gccName);
		clobbers.push_back(regInfo[i].gccName);
	    }
	}
	for (int i = 0; i < 32; i++) {
	    if (code->moreRegs & (1 << (i-32))) {
		//clobbers.cons(NULL_TREE, regInfo[i].gccName);
		clobbers.push_back(regInfo[i].gccName);
	    }
	}
	if (clobbers_mem)
	    clobbers.push_back(memory_name);
	    //clobbers.cons(NULL_TREE, memory_name);
//    }


    // Remap argument numbers
    for (unsigned i = 0; i < code->args.dim; i++) {
	if (arg_map[i] < 0)
	    arg_map[i] = -arg_map[i] - 1 + n_outputs;
    }
    
    bool pct = false;
    char * p = code->insnTemplate;
    char * q = p + code->insnTemplateLen;
    //printf("start: %.*s\n", code->insnTemplateLen, code->insnTemplate);
    while (p < q) {
	if (pct) {
	    if (*p >= '0' && *p <= '9') {
		// %% doesn't check against nargs
		*p = '0' + arg_map[*p - '0'];
		pct = false;
	    } else if (*p == '$') {
		pct = false;
	    }
	    //assert(*p == '%');// could be 'a', etc. so forget it..
	} else if (*p == '$')
	    pct = true;
	++p;
    }

    Logger::println("final asm: %.*s", code->insnTemplateLen, code->insnTemplate);

    std::string insnt(code->insnTemplate, code->insnTemplateLen);

    // rewrite GCC-style constraints to LLVM-style constraints
    std::string llvmOutConstraints;
    std::string llvmInConstraints;
    int n = 0;
    typedef std::deque<std::string>::iterator it;
    for(it i = output_constraints.begin(), e = output_constraints.end(); i != e; ++i, ++n) {
        // rewrite update constraint to in and out constraints
        if((*i)[0] == '+') {
            (*i)[0] = '=';
            std::string input_constraint;
            std::stringstream ss;
            ss << n;
            ss >> input_constraint;
            //FIXME: I think multiple inout constraints will mess up the order!
            input_constraints.push_front(input_constraint);
            input_values.push_front(output_values[n]);
        }
        llvmOutConstraints += *i;
        llvmOutConstraints += ",";
    }
    for(it i = input_constraints.begin(), e = input_constraints.end(); i != e; ++i) {
        llvmInConstraints += *i;
        llvmInConstraints += ",";
    }

    std::string clobstr;
    for(it i = clobbers.begin(), e = clobbers.end(); i != e; ++i) {
        clobstr = "~{" + *i + "},";
        asmblock->clobs.insert(clobstr);
    }

    // excessive commas are removed later...

    // push asm statement
    IRAsmStmt* asmStmt = new IRAsmStmt;
    asmStmt->code = insnt;
    asmStmt->out_c = llvmOutConstraints;
    asmStmt->in_c = llvmInConstraints;
    asmStmt->out.insert(asmStmt->out.begin(), output_values.begin(), output_values.end());
    asmStmt->in.insert(asmStmt->in.begin(), input_values.begin(), input_values.end());
    asmStmt->isBranchToLabel = isBranchToLabel;
    asmblock->s.push_back(asmStmt);
}

//////////////////////////////////////////////////////////////////////////////

AsmBlockStatement::AsmBlockStatement(Loc loc, Statements* s)
:   CompoundStatement(loc, s)
{
    enclosingtryfinally = NULL;
}

// rewrite argument indices to the block scope indices
static void remap_outargs(std::string& insnt, size_t nargs, size_t& idx)
{
    static const std::string digits[10] =
    {
        "0","1","2","3","4",
        "5","6","7","8","9"
    };
    assert(nargs <= 10);

    static const std::string prefix("<<out");
    static const std::string suffix(">>");
    std::string argnum;
    std::string needle;
    char buf[10];
    for (unsigned i = 0; i < nargs; i++) {
        needle = prefix + digits[i] + suffix;
        size_t pos = insnt.find(needle);
        if(std::string::npos != pos)
            sprintf(buf, "%u", idx++);
        while(std::string::npos != (pos = insnt.find(needle)))
            insnt.replace(pos, needle.size(), buf);
    }
}

// rewrite argument indices to the block scope indices
static void remap_inargs(std::string& insnt, size_t nargs, size_t& idx)
{
    static const std::string digits[10] =
    {
        "0","1","2","3","4",
        "5","6","7","8","9"
    };
    assert(nargs <= 10);

    static const std::string prefix("<<in");
    static const std::string suffix(">>");
    std::string argnum;
    std::string needle;
    char buf[10];
    for (unsigned i = 0; i < nargs; i++) {
        needle = prefix + digits[i] + suffix;
        size_t pos = insnt.find(needle);
        if(std::string::npos != pos)
            sprintf(buf, "%u", idx++);
        while(std::string::npos != (pos = insnt.find(needle)))
            insnt.replace(pos, needle.size(), buf);
    }
}

void AsmBlockStatement::toIR(IRState* p)
{
    Logger::println("AsmBlockStatement::toIR(): %s", loc.toChars());
    LOG_SCOPE;
    Logger::println("BEGIN ASM");

    // create asm block structure
    assert(!p->asmBlock);
    IRAsmBlock* asmblock = new IRAsmBlock;
    assert(asmblock);
    p->asmBlock = asmblock;

    // do asm statements
    for (int i=0; i<statements->dim; i++)
    {
        Statement* s = (Statement*)statements->data[i];
        if (s) {
            s->toIR(p);
        }
    }

    // build forwarder for in-asm branches to external labels
    // this additional asm code sets the __llvm_jump_target variable
    // to a unique value that will identify the jump target in
    // a post-asm switch

    // maps each special value to a goto destination
    std::map<int, Identifier*> valToGoto;

    // location of the value containing the index into the valToGoto map
    // will be set if post-asm dispatcher block is needed
    llvm::AllocaInst* jump_target;

    {
        FuncDeclaration* fd = gIR->func()->decl;
        char* fdmangle = fd->mangle();

        // we use a simple static counter to make sure the new end labels are unique
        static size_t uniqueLabelsId = 0;
        std::ostringstream asmGotoEndLabel;
        asmGotoEndLabel << "." << fdmangle << "__llvm_asm_end" << uniqueLabelsId++;

        // initialize the setter statement we're going to build
        IRAsmStmt* outSetterStmt = new IRAsmStmt;
        std::string asmGotoEnd = "jmp "+asmGotoEndLabel.str()+" ; ";
        std::ostringstream code;
        code << asmGotoEnd;

        int n_goto = 1;

        size_t n = asmblock->s.size();
        for(size_t i=0; i<n; ++i)
        {
            IRAsmStmt* a = asmblock->s[i];

            // skip non-branch statements
            if(!a->isBranchToLabel)
                continue;

            // if internal, no special handling is necessary, skip
            std::vector<Identifier*>::const_iterator it, end;
            end = asmblock->internalLabels.end();
            bool skip = false;
            for(it = asmblock->internalLabels.begin(); it != end; ++it)
                if((*it)->equals(a->isBranchToLabel))
                    skip = true;
            if(skip) 
                continue;

            // record that the jump needs to be handled in the post-asm dispatcher
            valToGoto[n_goto] = a->isBranchToLabel;

            // provide an in-asm target for the branch and set value
            Logger::println("statement '%s' references outer label '%s': creating forwarder", a->code.c_str(), a->isBranchToLabel->string);
            code << fdmangle << '_' << a->isBranchToLabel->string << ": ; ";
            code << "movl $<<in" << n_goto << ">>, $<<out0>> ; ";
            //FIXME: Store the value -> label mapping somewhere, so it can be referenced later
            outSetterStmt->in.push_back(DtoConstUint(n_goto));
            outSetterStmt->in_c += "i,";
            code << asmGotoEnd;

            ++n_goto;
        }
        if(code.str() != asmGotoEnd)
        {
            // finalize code
            outSetterStmt->code = code.str();
            outSetterStmt->code += asmGotoEndLabel.str()+": ; ";

            // create storage for and initialize the temporary
            jump_target = new llvm::AllocaInst(llvm::IntegerType::get(32), "__llvm_jump_target", p->topallocapoint());
            gIR->ir->CreateStore(DtoConstUint(0), jump_target);
            // setup variable for output from asm
            outSetterStmt->out_c = "=*m,";
            outSetterStmt->out.push_back(jump_target);

            asmblock->s.push_back(outSetterStmt);
        }
        else
            delete outSetterStmt;
    }


    // build asm block
    std::vector<LLValue*> outargs;
    std::vector<LLValue*> inargs;
    std::vector<const LLType*> outtypes;
    std::vector<const LLType*> intypes;
    std::string out_c;
    std::string in_c;
    std::string clobbers;
    std::string code;
    size_t asmIdx = 0;

    size_t n = asmblock->s.size();
    for (size_t i=0; i<n; ++i)
    {
        IRAsmStmt* a = asmblock->s[i];
        assert(a);
        size_t onn = a->out.size();
        for (size_t j=0; j<onn; ++j)
        {
            outargs.push_back(a->out[j]);
            outtypes.push_back(a->out[j]->getType());
        }
        if (!a->out_c.empty())
        {
            out_c += a->out_c;
        }
        remap_outargs(a->code, onn+a->in.size(), asmIdx);
    }
    for (size_t i=0; i<n; ++i)
    {
        IRAsmStmt* a = asmblock->s[i];
        assert(a);
        size_t inn = a->in.size();
        for (size_t j=0; j<inn; ++j)
        {
            inargs.push_back(a->in[j]);
            intypes.push_back(a->in[j]->getType());
        }
        if (!a->in_c.empty())
        {
            in_c += a->in_c;
        }
        remap_inargs(a->code, inn+a->out.size(), asmIdx);
        if (!code.empty())
            code += " ; ";
        code += a->code;
    }
    asmblock->s.clear();

    // append inputs
    out_c += in_c;

    // append clobbers
    typedef std::set<std::string>::iterator clobs_it;
    for (clobs_it i=asmblock->clobs.begin(); i!=asmblock->clobs.end(); ++i)
    {
        out_c += *i;
    }

    // remove excessive comma
    if (!out_c.empty())
        out_c.resize(out_c.size()-1);

    Logger::println("code = \"%s\"", code.c_str());
    Logger::println("constraints = \"%s\"", out_c.c_str());

    std::vector<const LLType*> types;
    types.insert(types.end(), outtypes.begin(), outtypes.end());
    types.insert(types.end(), intypes.begin(), intypes.end());
    llvm::FunctionType* fty = llvm::FunctionType::get(llvm::Type::VoidTy, types, false);
    Logger::cout() << "function type = " << *fty << '\n';
    llvm::InlineAsm* ia = llvm::InlineAsm::get(fty, code, out_c, true);

    std::vector<LLValue*> args;
    args.insert(args.end(), outargs.begin(), outargs.end());
    args.insert(args.end(), inargs.begin(), inargs.end());
    llvm::CallInst* call = p->ir->CreateCall(ia, args.begin(), args.end(), "");

    p->asmBlock = NULL;
    Logger::println("END ASM");

    // if asm contained external branches, emit goto forwarder code
    if(!valToGoto.empty())
    {
        assert(jump_target);

        // make new blocks
        llvm::BasicBlock* oldend = gIR->scopeend();
        llvm::BasicBlock* bb = llvm::BasicBlock::Create("afterasmgotoforwarder", p->topfunc(), oldend);

        llvm::LoadInst* val = p->ir->CreateLoad(jump_target, "__llvm_jump_target_value");
        llvm::SwitchInst* sw = p->ir->CreateSwitch(val, bb, valToGoto.size());

        // add all cases
        std::map<int, Identifier*>::iterator it, end = valToGoto.end();
        for(it = valToGoto.begin(); it != end; ++it)
        {
            llvm::BasicBlock* casebb = llvm::BasicBlock::Create("case", p->topfunc(), bb);
            sw->addCase(llvm::ConstantInt::get(llvm::IntegerType::get(32), it->first), casebb);

            p->scope() = IRScope(casebb,bb);
            DtoGoto(&loc, it->second, enclosingtryfinally);
        }

        p->scope() = IRScope(bb,oldend);
    }
}

// the whole idea of this statement is to avoid the flattening
Statements* AsmBlockStatement::flatten(Scope* sc)
{
    return NULL;
}

Statement *AsmBlockStatement::syntaxCopy()
{
    Statements *a = new Statements();
    a->setDim(statements->dim);
    for (size_t i = 0; i < statements->dim; i++)
    {
        Statement *s = (Statement *)statements->data[i];
        if (s)
            s = s->syntaxCopy();
        a->data[i] = s;
    }
    AsmBlockStatement *cs = new AsmBlockStatement(loc, a);
    return cs;
}

// necessary for in-asm branches
Statement *AsmBlockStatement::semantic(Scope *sc)
{
    enclosingtryfinally = sc->tfOfTry;

    return CompoundStatement::semantic(sc);
}
