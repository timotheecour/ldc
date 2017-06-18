// Automatically generated by gen_ddmdstructor

#include "expression.h"

RootObject* new_RootObject();
StoppableVisitor* new_StoppableVisitor();
Dsymbol* new_Dsymbol();
Dsymbol* new_Dsymbol(Identifier *arg0);
ScopeDsymbol* new_ScopeDsymbol();
ScopeDsymbol* new_ScopeDsymbol(Identifier *id);
WithScopeSymbol* new_WithScopeSymbol(WithStatement *withstate);
ArrayScopeSymbol* new_ArrayScopeSymbol(Scope *sc, Expression *e);
ArrayScopeSymbol* new_ArrayScopeSymbol(Scope *sc, TypeTuple *t);
ArrayScopeSymbol* new_ArrayScopeSymbol(Scope *sc, TupleDeclaration *td);
OverloadSet* new_OverloadSet(Identifier *ident, OverloadSet *os);
DsymbolTable* new_DsymbolTable();
Identifier* new_Identifier(const char *_string, unsigned long length, int value);
Expression* new_Expression(Loc loc, TOK op, int size);
IntegerExp* new_IntegerExp(Loc loc, dinteger_t value, Type *type);
IntegerExp* new_IntegerExp(dinteger_t value);
ErrorExp* new_ErrorExp();
RealExp* new_RealExp(Loc loc, real_t value, Type *type);
ComplexExp* new_ComplexExp(Loc loc, complex_t value, Type *type);
IdentifierExp* new_IdentifierExp(Loc loc, Identifier *ident);
DollarExp* new_DollarExp(Loc loc);
DsymbolExp* new_DsymbolExp(Loc loc, Dsymbol *s, bool hasOverloads);
ThisExp* new_ThisExp(Loc loc);
SuperExp* new_SuperExp(Loc loc);
NullExp* new_NullExp(Loc loc, Type *t = nullptr);
StringExp* new_StringExp(Loc loc, char *s);
StringExp* new_StringExp(Loc loc, void *s, size_t len);
StringExp* new_StringExp(Loc loc, void *s, size_t len, utf8_t postfix);
TupleExp* new_TupleExp(Loc loc, Expression *e0, Expressions *exps);
TupleExp* new_TupleExp(Loc loc, Expressions *exps);
TupleExp* new_TupleExp(Loc loc, TupleDeclaration *tup);
ArrayLiteralExp* new_ArrayLiteralExp(Loc loc, Expressions *elements);
ArrayLiteralExp* new_ArrayLiteralExp(Loc loc, Expression *e);
ArrayLiteralExp* new_ArrayLiteralExp(Loc loc, Expression *basis, Expressions *elements);
ArrayLiteralExp* new_ArrayLiteralExp(Loc loc, Expression *basis, size_t dim);
AssocArrayLiteralExp* new_AssocArrayLiteralExp(Loc loc, Expressions *keys, Expressions *values);
StructLiteralExp* new_StructLiteralExp(Loc loc, AggregateDeclaration *sd, Expressions *elements, Type *stype);
TypeExp* new_TypeExp(Loc loc, Type *type);
ScopeExp* new_ScopeExp(Loc loc, ScopeDsymbol *sds);
TemplateExp* new_TemplateExp(Loc loc, TemplateDeclaration *td, FuncDeclaration *fd = nullptr);
NewExp* new_NewExp(Loc loc, Expression *thisexp, Expressions *newargs, Type *newtype, Expressions *arguments);
NewAnonClassExp* new_NewAnonClassExp(Loc loc, Expression *thisexp, Expressions *newargs, ClassDeclaration *cd, Expressions *arguments);
SymbolExp* new_SymbolExp(Loc loc, TOK op, int size, Declaration *var, bool hasOverloads);
SymOffExp* new_SymOffExp(Loc loc, Declaration *var, dinteger_t offset, bool hasOverloads);
VarExp* new_VarExp(Loc loc, Declaration *var, bool hasOverloads = true);
OverExp* new_OverExp(Loc loc, OverloadSet *s);
FuncExp* new_FuncExp(Loc loc, Dsymbol *s);
DeclarationExp* new_DeclarationExp(Loc loc, Dsymbol *declaration);
TypeidExp* new_TypeidExp(Loc loc, RootObject *obj);
TraitsExp* new_TraitsExp(Loc loc, Identifier *ident, Objects *args);
HaltExp* new_HaltExp(Loc loc);
IsExp* new_IsExp(Loc loc, Type *targ, Identifier *id, TOK tok, Type *tspec, TOK tok2, TemplateParameters *parameters);
BinAssignExp* new_BinAssignExp(Loc loc, TOK op, int size, Expression *e1, Expression *e2);
CompileExp* new_CompileExp(Loc loc, Expression *e);
ImportExp* new_ImportExp(Loc loc, Expression *e);
AssertExp* new_AssertExp(Loc loc, Expression *e, Expression *msg);
DotIdExp* new_DotIdExp(Loc loc, Expression *e, Identifier *ident);
DotTemplateExp* new_DotTemplateExp(Loc loc, Expression *e, TemplateDeclaration *td);
DotVarExp* new_DotVarExp(Loc loc, Expression *e, Declaration *var, bool hasOverloads = true);
DotTemplateInstanceExp* new_DotTemplateInstanceExp(Loc loc, Expression *e, Identifier *name, Objects *tiargs);
DotTemplateInstanceExp* new_DotTemplateInstanceExp(Loc loc, Expression *e, TemplateInstance *ti);
DelegateExp* new_DelegateExp(Loc loc, Expression *e, FuncDeclaration *func, bool hasOverloads);
DotTypeExp* new_DotTypeExp(Loc loc, Expression *e, Dsymbol *sym);
CallExp* new_CallExp(Loc loc, Expression *e, Expressions *exps);
CallExp* new_CallExp(Loc loc, Expression *e);
CallExp* new_CallExp(Loc loc, Expression *e, Expression *earg1);
CallExp* new_CallExp(Loc loc, Expression *e, Expression *earg1, Expression *earg2);
AddrExp* new_AddrExp(Loc loc, Expression *e);
PtrExp* new_PtrExp(Loc loc, Expression *e);
PtrExp* new_PtrExp(Loc loc, Expression *e, Type *t);
NegExp* new_NegExp(Loc loc, Expression *e);
UAddExp* new_UAddExp(Loc loc, Expression *e);
ComExp* new_ComExp(Loc loc, Expression *e);
NotExp* new_NotExp(Loc loc, Expression *e);
DeleteExp* new_DeleteExp(Loc loc, Expression *e, bool isRAII);
CastExp* new_CastExp(Loc loc, Expression *e, Type *t);
CastExp* new_CastExp(Loc loc, Expression *e, unsigned char mod);
VectorExp* new_VectorExp(Loc loc, Expression *e, Type *t);
SliceExp* new_SliceExp(Loc loc, Expression *e1, IntervalExp *ie);
SliceExp* new_SliceExp(Loc loc, Expression *e1, Expression *lwr, Expression *upr);
ArrayLengthExp* new_ArrayLengthExp(Loc loc, Expression *e1);
IntervalExp* new_IntervalExp(Loc loc, Expression *lwr, Expression *upr);
DelegatePtrExp* new_DelegatePtrExp(Loc loc, Expression *e1);
DelegateFuncptrExp* new_DelegateFuncptrExp(Loc loc, Expression *e1);
ArrayExp* new_ArrayExp(Loc loc, Expression *e1, Expression *index);
ArrayExp* new_ArrayExp(Loc loc, Expression *e1, Expressions *args);
DotExp* new_DotExp(Loc loc, Expression *e1, Expression *e2);
CommaExp* new_CommaExp(Loc loc, Expression *e1, Expression *e2);
IndexExp* new_IndexExp(Loc loc, Expression *e1, Expression *e2);
PostExp* new_PostExp(TOK op, Loc loc, Expression *e);
PreExp* new_PreExp(TOK op, Loc loc, Expression *e);
AssignExp* new_AssignExp(Loc loc, Expression *e1, Expression *e2);
ConstructExp* new_ConstructExp(Loc loc, Expression *e1, Expression *e2);
ConstructExp* new_ConstructExp(Loc loc, VarDeclaration *v, Expression *e2);
BlitExp* new_BlitExp(Loc loc, Expression *e1, Expression *e2);
BlitExp* new_BlitExp(Loc loc, VarDeclaration *v, Expression *e2);
AddAssignExp* new_AddAssignExp(Loc loc, Expression *e1, Expression *e2);
MinAssignExp* new_MinAssignExp(Loc loc, Expression *e1, Expression *e2);
MulAssignExp* new_MulAssignExp(Loc loc, Expression *e1, Expression *e2);
DivAssignExp* new_DivAssignExp(Loc loc, Expression *e1, Expression *e2);
ModAssignExp* new_ModAssignExp(Loc loc, Expression *e1, Expression *e2);
AndAssignExp* new_AndAssignExp(Loc loc, Expression *e1, Expression *e2);
OrAssignExp* new_OrAssignExp(Loc loc, Expression *e1, Expression *e2);
XorAssignExp* new_XorAssignExp(Loc loc, Expression *e1, Expression *e2);
PowAssignExp* new_PowAssignExp(Loc loc, Expression *e1, Expression *e2);
ShlAssignExp* new_ShlAssignExp(Loc loc, Expression *e1, Expression *e2);
ShrAssignExp* new_ShrAssignExp(Loc loc, Expression *e1, Expression *e2);
UshrAssignExp* new_UshrAssignExp(Loc loc, Expression *e1, Expression *e2);
CatAssignExp* new_CatAssignExp(Loc loc, Expression *e1, Expression *e2);
AddExp* new_AddExp(Loc loc, Expression *e1, Expression *e2);
MinExp* new_MinExp(Loc loc, Expression *e1, Expression *e2);
CatExp* new_CatExp(Loc loc, Expression *e1, Expression *e2);
MulExp* new_MulExp(Loc loc, Expression *e1, Expression *e2);
DivExp* new_DivExp(Loc loc, Expression *e1, Expression *e2);
ModExp* new_ModExp(Loc loc, Expression *e1, Expression *e2);
PowExp* new_PowExp(Loc loc, Expression *e1, Expression *e2);
ShlExp* new_ShlExp(Loc loc, Expression *e1, Expression *e2);
ShrExp* new_ShrExp(Loc loc, Expression *e1, Expression *e2);
UshrExp* new_UshrExp(Loc loc, Expression *e1, Expression *e2);
AndExp* new_AndExp(Loc loc, Expression *e1, Expression *e2);
OrExp* new_OrExp(Loc loc, Expression *e1, Expression *e2);
XorExp* new_XorExp(Loc loc, Expression *e1, Expression *e2);
OrOrExp* new_OrOrExp(Loc loc, Expression *e1, Expression *e2);
AndAndExp* new_AndAndExp(Loc loc, Expression *e1, Expression *e2);
CmpExp* new_CmpExp(TOK op, Loc loc, Expression *e1, Expression *e2);
InExp* new_InExp(Loc loc, Expression *e1, Expression *e2);
RemoveExp* new_RemoveExp(Loc loc, Expression *e1, Expression *e2);
EqualExp* new_EqualExp(TOK op, Loc loc, Expression *e1, Expression *e2);
IdentityExp* new_IdentityExp(TOK op, Loc loc, Expression *e1, Expression *e2);
CondExp* new_CondExp(Loc loc, Expression *econd, Expression *e1, Expression *e2);
DefaultInitExp* new_DefaultInitExp(Loc loc, TOK subop, int size);
FileInitExp* new_FileInitExp(Loc loc, TOK tok);
LineInitExp* new_LineInitExp(Loc loc);
ModuleInitExp* new_ModuleInitExp(Loc loc);
FuncInitExp* new_FuncInitExp(Loc loc);
PrettyFuncInitExp* new_PrettyFuncInitExp(Loc loc);
TypeError* new_TypeError();
TypeBasic* new_TypeBasic(TY ty);
TypeVector* new_TypeVector(Loc loc, Type *basetype);
TypeArray* new_TypeArray(TY ty, Type *next);
TypeSArray* new_TypeSArray(Type *t, Expression *dim);
TypeDArray* new_TypeDArray(Type *t);
TypeAArray* new_TypeAArray(Type *t, Type *index);
TypePointer* new_TypePointer(Type *t);
TypeReference* new_TypeReference(Type *t);
TypeFunction* new_TypeFunction(Parameters *parameters, Type *treturn, int varargs, LINK linkage, StorageClass stc = 0);
TypeDelegate* new_TypeDelegate(Type *t);
TypeIdentifier* new_TypeIdentifier(Loc loc, Identifier *ident);
TypeInstance* new_TypeInstance(Loc loc, TemplateInstance *tempinst);
TypeTypeof* new_TypeTypeof(Loc loc, Expression *exp);
TypeReturn* new_TypeReturn(Loc loc);
TypeStruct* new_TypeStruct(StructDeclaration *sym);
TypeEnum* new_TypeEnum(EnumDeclaration *sym);
TypeClass* new_TypeClass(ClassDeclaration *sym);
TypeTuple* new_TypeTuple(Parameters *arguments);
TypeTuple* new_TypeTuple(Expressions *exps);
TypeTuple* new_TypeTuple();
TypeTuple* new_TypeTuple(Type *t1);
TypeTuple* new_TypeTuple(Type *t1, Type *t2);
TypeSlice* new_TypeSlice(Type *next, Expression *lwr, Expression *upr);
TypeNull* new_TypeNull();
Parameter* new_Parameter(StorageClass storageClass, Type *type, Identifier *ident, Expression *defaultArg);
TupleDeclaration* new_TupleDeclaration(Loc loc, Identifier *ident, Objects *objects);
AliasDeclaration* new_AliasDeclaration(Loc loc, Identifier *ident, Type *type);
AliasDeclaration* new_AliasDeclaration(Loc loc, Identifier *ident, Dsymbol *s);
OverDeclaration* new_OverDeclaration(Identifier *ident, Dsymbol *s, bool hasOverloads);
VarDeclaration* new_VarDeclaration(Loc loc, Type *t, Identifier *id, Initializer *init);
SymbolDeclaration* new_SymbolDeclaration(Loc loc, StructDeclaration *dsym);
TypeInfoDeclaration* new_TypeInfoDeclaration(Type *tinfo);
TypeInfoStructDeclaration* new_TypeInfoStructDeclaration(Type *tinfo);
TypeInfoClassDeclaration* new_TypeInfoClassDeclaration(Type *tinfo);
TypeInfoInterfaceDeclaration* new_TypeInfoInterfaceDeclaration(Type *tinfo);
TypeInfoPointerDeclaration* new_TypeInfoPointerDeclaration(Type *tinfo);
TypeInfoArrayDeclaration* new_TypeInfoArrayDeclaration(Type *tinfo);
TypeInfoStaticArrayDeclaration* new_TypeInfoStaticArrayDeclaration(Type *tinfo);
TypeInfoAssociativeArrayDeclaration* new_TypeInfoAssociativeArrayDeclaration(Type *tinfo);
TypeInfoEnumDeclaration* new_TypeInfoEnumDeclaration(Type *tinfo);
TypeInfoFunctionDeclaration* new_TypeInfoFunctionDeclaration(Type *tinfo);
TypeInfoDelegateDeclaration* new_TypeInfoDelegateDeclaration(Type *tinfo);
TypeInfoTupleDeclaration* new_TypeInfoTupleDeclaration(Type *tinfo);
TypeInfoConstDeclaration* new_TypeInfoConstDeclaration(Type *tinfo);
TypeInfoInvariantDeclaration* new_TypeInfoInvariantDeclaration(Type *tinfo);
TypeInfoSharedDeclaration* new_TypeInfoSharedDeclaration(Type *tinfo);
TypeInfoWildDeclaration* new_TypeInfoWildDeclaration(Type *tinfo);
TypeInfoVectorDeclaration* new_TypeInfoVectorDeclaration(Type *tinfo);
ThisDeclaration* new_ThisDeclaration(Loc loc, Type *t);
FuncDeclaration* new_FuncDeclaration(Loc loc, Loc endloc, Identifier *id, StorageClass storage_class, Type *type);
FuncAliasDeclaration* new_FuncAliasDeclaration(Identifier *ident, FuncDeclaration *funcalias, bool hasOverloads);
FuncLiteralDeclaration* new_FuncLiteralDeclaration(Loc loc, Loc endloc, Type *type, TOK tok, ForeachStatement *fes, Identifier *id);
CtorDeclaration* new_CtorDeclaration(Loc loc, Loc endloc, StorageClass stc, Type *type);
PostBlitDeclaration* new_PostBlitDeclaration(Loc loc, Loc endloc, StorageClass stc, Identifier *id);
DtorDeclaration* new_DtorDeclaration(Loc loc, Loc endloc);
DtorDeclaration* new_DtorDeclaration(Loc loc, Loc endloc, StorageClass stc, Identifier *id);
StaticCtorDeclaration* new_StaticCtorDeclaration(Loc loc, Loc endloc, StorageClass stc);
StaticCtorDeclaration* new_StaticCtorDeclaration(Loc loc, Loc endloc, const char *name, StorageClass stc);
SharedStaticCtorDeclaration* new_SharedStaticCtorDeclaration(Loc loc, Loc endloc, StorageClass stc);
StaticDtorDeclaration* new_StaticDtorDeclaration(Loc loc, Loc endloc, StorageClass stc);
StaticDtorDeclaration* new_StaticDtorDeclaration(Loc loc, Loc endloc, const char *name, StorageClass stc);
SharedStaticDtorDeclaration* new_SharedStaticDtorDeclaration(Loc loc, Loc endloc, StorageClass stc);
UnitTestDeclaration* new_UnitTestDeclaration(Loc loc, Loc endloc, StorageClass stc, char *codedoc);
NewDeclaration* new_NewDeclaration(Loc loc, Loc endloc, StorageClass stc, Parameters *arguments, int varargs);
DeleteDeclaration* new_DeleteDeclaration(Loc loc, Loc endloc, StorageClass stc, Parameters *arguments);
StructDeclaration* new_StructDeclaration(Loc loc, Identifier *id);
UnionDeclaration* new_UnionDeclaration(Loc loc, Identifier *id);
InterfaceDeclaration* new_InterfaceDeclaration(Loc loc, Identifier *id, BaseClasses *baseclasses);
DVCondition* new_DVCondition(Module *mod, unsigned int level, Identifier *ident);
DebugCondition* new_DebugCondition(Module *mod, unsigned int level, Identifier *ident);
VersionCondition* new_VersionCondition(Module *mod, unsigned int level, Identifier *ident);
StaticIfCondition* new_StaticIfCondition(Loc loc, Expression *exp);
EnumDeclaration* new_EnumDeclaration(Loc loc, Identifier *id, Type *memtype);
EnumMember* new_EnumMember(Loc loc, Identifier *id, Expression *value, Type *origType);
Import* new_Import(Loc loc, Identifiers *packages, Identifier *id, Identifier *aliasId, int isstatic);
VoidInitializer* new_VoidInitializer(Loc loc);
ErrorInitializer* new_ErrorInitializer();
StructInitializer* new_StructInitializer(Loc loc);
ArrayInitializer* new_ArrayInitializer(Loc loc);
ExpInitializer* new_ExpInitializer(Loc loc, Expression *exp);
Package* new_Package(Identifier *ident);
Module* new_Module(const char *arg, Identifier *ident, int doDocComment, int doHdrGen);
ErrorStatement* new_ErrorStatement();
PeelStatement* new_PeelStatement(Statement *s);
ExpStatement* new_ExpStatement(Loc loc, Expression *exp);
ExpStatement* new_ExpStatement(Loc loc, Dsymbol *s);
DtorExpStatement* new_DtorExpStatement(Loc loc, Expression *exp, VarDeclaration *v);
CompileStatement* new_CompileStatement(Loc loc, Expression *exp);
CompoundStatement* new_CompoundStatement(Loc loc, Statements *s);
CompoundStatement* new_CompoundStatement(Loc loc, Statement *s1);
CompoundStatement* new_CompoundStatement(Loc loc, Statement *s1, Statement *s2);
CompoundDeclarationStatement* new_CompoundDeclarationStatement(Loc loc, Statements *s);
UnrolledLoopStatement* new_UnrolledLoopStatement(Loc loc, Statements *statements);
WhileStatement* new_WhileStatement(Loc loc, Expression *c, Statement *b, Loc endloc);
ForStatement* new_ForStatement(Loc loc, Statement *init, Expression *condition, Expression *increment, Statement *_body, Loc endloc);
ForeachStatement* new_ForeachStatement(Loc loc, TOK op, Parameters *parameters, Expression *aggr, Statement *_body, Loc endloc);
ForeachRangeStatement* new_ForeachRangeStatement(Loc loc, TOK op, Parameter *prm, Expression *lwr, Expression *upr, Statement *_body, Loc endloc);
ConditionalStatement* new_ConditionalStatement(Loc loc, Condition *condition, Statement *ifbody, Statement *elsebody);
PragmaStatement* new_PragmaStatement(Loc loc, Identifier *ident, Expressions *args, Statement *_body);
StaticAssertStatement* new_StaticAssertStatement(StaticAssert *sa);
SwitchStatement* new_SwitchStatement(Loc loc, Expression *c, Statement *b, bool isFinal);
CaseStatement* new_CaseStatement(Loc loc, Expression *exp, Statement *s);
CaseRangeStatement* new_CaseRangeStatement(Loc loc, Expression *first, Expression *last, Statement *s);
DefaultStatement* new_DefaultStatement(Loc loc, Statement *s);
GotoDefaultStatement* new_GotoDefaultStatement(Loc loc);
GotoCaseStatement* new_GotoCaseStatement(Loc loc, Expression *exp);
SwitchErrorStatement* new_SwitchErrorStatement(Loc loc);
ReturnStatement* new_ReturnStatement(Loc loc, Expression *exp);
BreakStatement* new_BreakStatement(Loc loc, Identifier *ident);
ContinueStatement* new_ContinueStatement(Loc loc, Identifier *ident);
SynchronizedStatement* new_SynchronizedStatement(Loc loc, Expression *exp, Statement *_body);
TryCatchStatement* new_TryCatchStatement(Loc loc, Statement *_body, Catches *catches);
Catch* new_Catch(Loc loc, Type *t, Identifier *id, Statement *handler);
TryFinallyStatement* new_TryFinallyStatement(Loc loc, Statement *_body, Statement *finalbody);
OnScopeStatement* new_OnScopeStatement(Loc loc, TOK tok, Statement *statement);
ThrowStatement* new_ThrowStatement(Loc loc, Expression *exp);
DebugStatement* new_DebugStatement(Loc loc, Statement *statement);
GotoStatement* new_GotoStatement(Loc loc, Identifier *ident);
LabelStatement* new_LabelStatement(Loc loc, Identifier *ident, Statement *statement);
LabelDsymbol* new_LabelDsymbol(Identifier *ident);
AsmStatement* new_AsmStatement(Loc loc, Token *tokens);
CompoundAsmStatement* new_CompoundAsmStatement(Loc loc, Statements *s, StorageClass stc);
ImportStatement* new_ImportStatement(Loc loc, Dsymbols *imports);
StaticAssert* new_StaticAssert(Loc loc, Expression *exp, Expression *msg);
TemplateDeclaration* new_TemplateDeclaration(Loc loc, Identifier *id, TemplateParameters *parameters, Expression *constraint, Dsymbols *decldefs, bool ismixin = false, bool literal = false);
TemplateTypeParameter* new_TemplateTypeParameter(Loc loc, Identifier *ident, Type *specType, Type *defaultType);
TemplateThisParameter* new_TemplateThisParameter(Loc loc, Identifier *ident, Type *specType, Type *defaultType);
TemplateValueParameter* new_TemplateValueParameter(Loc loc, Identifier *ident, Type *valType, Expression *specValue, Expression *defaultValue);
TemplateAliasParameter* new_TemplateAliasParameter(Loc loc, Identifier *ident, Type *specType, RootObject *specAlias, RootObject *defaultAlias);
TemplateTupleParameter* new_TemplateTupleParameter(Loc loc, Identifier *ident);
TemplateInstance* new_TemplateInstance(Loc loc, Identifier *ident, Objects *tiargs);
TemplateInstance* new_TemplateInstance(Loc loc, TemplateDeclaration *td, Objects *tiargs);
TemplateMixin* new_TemplateMixin(Loc loc, Identifier *ident, TypeQualified *tqual, Objects *tiargs);
LinkDeclaration* new_LinkDeclaration(LINK p, Dsymbols *decl);

LangPlugins* new_LangPlugins();

void delete_Object(RootObject *o);
void delete_File(File* o);

void construct_TypeBasic(TypeBasic* _this, TY ty);
void construct_TypePointer(TypePointer* _this, Type* t);
void construct_TypeReference(TypeReference* _this, Type* t);
void construct_VarDeclaration(VarDeclaration *_this, Loc loc, Type *t, Identifier *id, Initializer *init);
void construct_FuncDeclaration(FuncDeclaration *_this, Loc loc, Loc endloc, Identifier *id, StorageClass storage_class, Type *type);
void construct_CtorDeclaration(CtorDeclaration *_this, Loc loc, Loc endloc, StorageClass stc, Type *type);
void construct_DtorDeclaration(DtorDeclaration *_this, Loc loc, Loc endloc, StorageClass stc, Identifier *id);
void construct_EnumDeclaration(EnumDeclaration *_this, Loc loc, Identifier *id, Type *memtype);
void construct_EnumMember(EnumMember *_this, Loc loc, Identifier *id, Expression *value, Type *origType);
void construct_AliasDeclaration(AliasDeclaration *_this, Loc loc, Identifier *ident, Type *type);
void construct_Import(Import *_this, Loc loc, Identifiers *packages, Identifier *id, Identifier *aliasId, int isstatic);
void construct_Modmap(Modmap *_this, Loc loc, StringExp *arg);
void construct_StructDeclaration(StructDeclaration *_this, Loc loc, Identifier *id);
void construct_UnionDeclaration(UnionDeclaration *_this, Loc loc, Identifier *id);
void construct_ClassDeclaration(ClassDeclaration *_this, Loc loc, Identifier *id, BaseClasses *baseclasses, Dsymbols* members, bool inObject = false);
void construct_AnonDeclaration(AnonDeclaration *_this, Loc loc, bool isunion, Dsymbols *decl);
void construct_Catch(Catch *_this, Loc loc, Type *t, Identifier *id, Statement *handler);
void construct_Module(Module *_this, const char *arg, Identifier *ident, int doDocComment, int doHdrGen);
void construct_TemplateDeclaration(TemplateDeclaration *_this, Loc loc, Identifier *id, TemplateParameters *parameters, Expression *constraint, Dsymbols *decldefs, bool ismixin = false, bool literal = false);
void construct_TemplateInstance(TemplateInstance *_this, Loc loc, Identifier *ident, Objects* tiargs);
void construct_TemplateInstance(TemplateInstance *_this, Loc loc, TemplateDeclaration *td, Objects *tiargs);
