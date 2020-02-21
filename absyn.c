#include <stdlib.h>
#include <stdio.h>
// #include "symbol.h" /* symbol table data structures */
#include "absyn.h"  /* abstract syntax data structures */

struct Var *SimpleVar(int pos, struct Symbol *sym)
{
    struct Var *result;

    result = malloc(sizeof(struct Var));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = SimpleVar;
    result -> pos = pos;
    result -> uni.symbol = sym;

    return result;
}

struct Var *FieldVar(int pos, struct Var *var, struct Symbol *sym)
{
    struct Var *result;

    result = malloc(sizeof(struct Var));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = FieldVar;
    result -> pos = pos;
    result -> uni.field.var = var;
    result -> uni.field.sym = sym;

    return result;
}

struct Var *SubscripVar(int pos, struct Var *var, struct Exp *exp)
{
    struct Var *result;

    result = malloc(sizeof(struct Var));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = SubscripVar;
    result -> pos = pos;
    result -> uni.subscript.var = var;
    result -> uni.subscript.exp = exp;

    return result;
}

struct Exp *VarExp(int pos, struct Var *var)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = VarExp;
    result -> pos = pos;
    result -> uni.var = var;

    return result;
}

struct Exp *NilExp(int pos)
{
    struct Exp *result; 

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = NilExp;
    result -> pos = pos;

    return result;
}

struct Exp *IntExp(int pos, int i)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = IntExp;
    result -> pos = pos;
    result -> uni.intager = i;

    return result;
}

struct Exp *StringExp(int pos, char *str)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = StringExp;
    result -> pos = pos;
    result -> uni.string = str;

    return result;
}

struct Exp *CallExp(int pos,struct Symbol *func, struct ExpList *args)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = CallExp;
    result -> pos = pos;
    result -> uni.call.func = func;
    result -> uni.call.args = args;

    return result;
}

struct Exp *OpExp(int pos, Oper oper, struct Exp *left, struct Exp *right)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = OpExp;
    result -> pos = pos;
    result -> uni.op.oper = oper;
    result -> uni.op.left = left;
    result -> uni.op.right = right;

    return result;
}


struct Exp *RecordExp(int pos, struct Symbol *type, struct EFieldList *fields)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = RecordExp;
    result -> pos = pos;
    result -> uni.record.type = type;
    result -> uni.record.fields = fields;

    return result;
}

struct Exp *SeqExp(int pos, struct ExpList *seq)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = SeqExp;
    result -> pos = pos;
    result -> uni.seq = seq;

    return result;
}

struct Exp *AssignExp(int pos, struct Var *var, struct Exp *exp)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = AssignExp;
    result -> pos = pos;
    result -> uni.assign.var = var;
    result -> uni.assign.exp = exp;

    return result;
}

struct Exp *IfExp(int pos, struct Exp *optionalTest, struct Exp *optionalThen, struct Exp *optionalElse)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = IfExp;
    result -> pos = pos;
    result -> uni.optionalIf.optionaltest = optionalTest;
    result -> uni.optionalIf.optionalthen = optionalThen;
    result -> uni.optionalIf.optionalElse = optionalElse;

    return result;
}

struct Exp *WhileExp(int pos, struct Exp *optionalTest, struct Exp *body)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = WhileExp;
    result -> pos = pos;
    result -> uni.optioinalWhile.optionaltest = optionalTest;
    result -> uni.optioinalWhile.body = body;

    return result;
}

struct Exp *ForExp(int pos, struct Symbol *var, struct Exp *low, struct Exp *high, struct Exp *body)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = ForExp;
    result -> pos = pos;
    result -> uni.optionalFor.high = high;
    result -> uni.optionalFor.low = low;
    result -> uni.optionalFor.body = body;
    result -> uni.optionalFor.escape = 1;

    return result;
}

struct Exp *BreakExp(int pos)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = BreakExp;
    result -> pos = pos;

    return result;
}

struct Exp *LetExp(int pos, struct DecList *decs, struct Exp *body)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = LetExp;
    result -> pos = pos;
    result -> uni.let.decs = decs;
    result -> uni.let.body = body;

    return result;
}

struct Exp *ArrayExp(int pos, struct Symbol *type, struct Exp *size, struct Exp *init)
{
    struct Exp *result;

    result = malloc(sizeof(struct Exp));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = ArrayExp;
    result -> pos = pos;
    result -> uni.array.type = type;
    result -> uni.array.init = init;

    return result;
}

struct Dec *FunctionDec(int pos, struct FunDecList *function)
{
    struct Dec *result;

    result = malloc(sizeof(struct Dec));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = FunctionDec;
    result -> pos = pos;
    result -> uni.function = function;

    return result;
}

struct Dec *VarDec(int pos, struct Symbol *var, struct Symbol *type, struct Exp *init)
{
    struct Dec *result;

    result = malloc(sizeof(struct Dec));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = VarDec;
    result -> pos = pos;
    result -> uni.var.var = var;
    result -> uni.var.type = type;
    result -> uni.var.init = init;
    result -> uni.var.escape = 1;

    return result;
}

struct Dec *TypeDec(int pos, struct NameTyList *type)
{
    struct Dec *result;

    result = malloc(sizeof(struct Dec));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = TypeDec;
    result -> pos = pos;
    result -> uni.type = type;

    return result;
}

struct Ty *NameTy(int pos, struct Symbol *name)
{
    struct Ty *result;

    result = malloc(sizeof(struct Ty));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = nameTy;
    result -> pos = pos;
    result -> uni.name = name;

    return result;
}

struct Ty *RecordTy(int pos, struct FieldList *record)
{
    struct Ty *result;

    result = malloc(sizeof(struct Ty));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = recordTy;
    result -> pos = pos;
    result -> uni.record = record;

    return result;
}

struct Ty *ArrayTy(int pos, struct Symbol *array)
{
    struct Ty *result;

    result = malloc(sizeof(struct Ty));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> kind = arrayTy;
    result -> pos = pos;
    result -> uni.array = array;

    return result;
}

struct Field *NewField(int pos, struct Symbol *name, struct Symbol *type)
{
    struct Field *result;

    result = malloc(sizeof(struct Field));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> pos = pos;
    result -> name = name;
    result -> type = type;
    result -> escape = 1;

    return result;
}

struct FieldList *NewFieldList(struct Field *head, struct FieldList *tail)
{
    struct FieldList *result;

    result = malloc(sizeof(struct FieldList));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> head = head;
    result -> tail = tail;

    return result;
}

struct ExpList *NewExpList(struct Exp *head, struct ExpList *tail)
{
    struct ExpList *result;

    result = malloc(sizeof(struct ExpList));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> head = head;
    result -> tail = tail;

    return result;
}

struct FunDec *NewFunDec(int pos, struct Symbol *name, struct FieldList *params, struct Symbol *result, struct Exp *body)
{
    struct FunDec *res;

    res = malloc(sizeof(struct FunDec));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    res -> pos = pos;
    res -> name = name;
    res -> params = params;
    res -> result = result;
    res -> body = body;

    return res;
}

struct FunDecList *NewFunDecList(struct FunDec *head, struct FunDecList *tail)
{
    struct FunDecList *result;

    result = malloc(sizeof(struct FunDecList));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> head = head;
    result -> tail = tail;

    return result;
}

struct DecList *NewDecList(struct Dec *head, struct DecList *tail)
{
    struct DecList *result;

    result = malloc(sizeof(struct DecList));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> head = head;
    result -> tail = tail;

    return result;
}

struct NameTy *NewNameTy(struct Symbol *name, struct Ty *ty)
{
    struct NameTy *result;

    result = malloc(sizeof(struct NameTy));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> name = name;
    result -> ty = ty;

    return result;
}

struct DecList *NewNameTyList(struct NameTy *head, struct NameTyList *tail)
{
    struct NameTyList *result;

    result = malloc(sizeof(struct NameTyList));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> head = head;
    result -> tail = tail;

    return result;
}

struct EField *NewEField(struct Symbol *name, struct Exp *exp)
{
    struct EField *result;

    result = malloc(sizeof(struct EField));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> name = name;
    result -> exp = exp;

    return result;
}

struct EFieldList *NewEFieldList(struct EField *head, struct EFieldList *tail)
{
    struct EFieldList *result;

    result = malloc(sizeof(struct EFieldList));
    if(result == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    result -> head = head;
    result -> tail = tail;

    return result;
}
