/*  Abstract Syntax */
#include "symbol.h"

// 运算符
typedef enum {
    plus,           // + 
    minus,          // -
    times,          // *
    divide,         // /
    equal,          // =
    notEqual,       // !=
    lt,             // less than <
    le,             // less than or equal <=
    gt,             // >
    ge              // >=
} Oper;

struct ExpList
{
    struct Exp *head;
    struct ExpList *tail;
};

struct Field
{
    int pos;
    struct Symbol *name;
    struct Symbol *type;
    int /* bool */ escape;
};

struct FieldList
{
    struct Field* head;
    struct FieldList *tail;
};

struct EField
{
    struct Symbol *name;
    struct Exp *exp;
};

struct EFieldList
{
    struct EField *head;
    struct EFieldList *tail; 
};

struct DecList
{
    struct Dec *head;
    struct DecList *tail;
};

struct FunDec
{
    int pos;
    struct Symbol *name;
    struct FieldList *params;
    struct Symbol *result;
    struct Exp* body;
};

struct FunDecList
{
    struct FunDec *head;
    struct FunDecList *tail;
};

struct NameTy
{
    struct Symbol *name;
    struct Ty* ty;
};

struct NameTyList
{
    struct NameTy *head;
    struct NameTyList *tail;
};

struct Exp {
    int pos;
    enum {
        varExp,
        nilExp,
        intExp, 
        stringExp, 
        callExp,
	    opExp, 
        recordExp, 
        seqExp,
        assignExp, 
        ifExp,
	    whileExp, 
        forExp, 
        breakExp, 
        letExp,
        arrayExp
    } kind;
    union 
    {
        struct Var *var;
        int intager;
        char *string;
        struct ExpList *seq;
        struct 
        {
            struct Symbol *func;
            struct ExpList *args;
        } call;
        struct 
        {
            Oper oper;
            struct Exp *left;
            struct Exp *right;
        } op;
        struct 
        {
            struct Symbol *type;
            struct EFieldList *fields;         
        } record;
        struct
        {
            struct Var *var;
            struct Exp *exp;
        } assign;
        struct
        {
            struct Exp *optionaltest;
            struct Exp *optionalthen;
            struct Exp *optionalElse;
        } optionalIf;
        struct
        {
            struct Exp *optionaltest;
            struct Exp *body;
        } optioinalWhile;
        struct
        {
            struct Symbol *var;
            struct Exp *low;
            struct Exp *high;
            struct Exp *body;
            int /* bool */ escape;
        } optionalFor;
	    /* breakk; - need only the pos */
        struct
        {
            struct DecList *decs;
            struct Exp *body;
        } let;
	    struct
        {
            struct Symbol *type;
            struct Exp *size;
            struct Exp *init;
        } array;
    } uni;
};

struct ExpList
{
    struct Exp *head;
    struct ExpList *tail;
};

struct Var {
    int pos;
    enum {
        simpleVar,
        fieldVar,
        subscriptVar
    } kind;
    union {
        struct Symbol *symbol;
        struct {
            struct Var *var;
            struct Symbol *sym;
        } field;
        struct {
            struct Var *var;
            struct Exp *exp;
        } subscript;
    } uni;
};


struct Dec
{
    int pos;
    enum {
        functionDec,
        varDec,
        typeDec
    } kind;
    union 
    {
        struct FunDecList *function;
        struct 
        {
            struct Symbol *var;
            struct Symbol *type;
            struct Exp *init;
            int /* bool */ escape;
        } var;
        struct NameTyList *type;
    } uni;
    
};

struct Ty
{
    int pos;
    enum {
        nameTy,
        recordTy,
        arrayTy
    } kind;
    union 
    {
        struct Symbol *name;
        struct FieldList *record;
        struct Symbol *array;
    } uni;
};


struct Var *SimpleVar(int pos, struct Symbol *sym);
struct Var *FieldVar(int pos, struct Var *var, struct Symbol *sym);
struct Var *SubscriptVar(int pos, struct Var *var, struct Exp *exp);
struct Exp *VarExp(int pos, struct Var *var);
struct Exp *NilExp(int pos);
struct Exp *IntExp(int pos, int i);
struct Exp *StringExp(int pos, char *s);
struct Exp *CallExp(int pos, struct Symbol *func, struct ExpList *args);
struct Exp *OpExp(int pos, Oper oper, struct Exp *left, struct Exp *right);
struct Exp *RecordExp(int pos, struct Symbol *type, struct EFieldList *fields);
struct Exp *SeqExp(int pos, struct ExpList *seq);
struct Exp *AssignExp(int pos, struct Var *var, struct Exp *exp);
struct Exp *IfExp(int pos, struct Exp *optionalTest, struct Exp *optionalThen, struct Exp *optionalElse);
struct Exp *WhileExp(int pos, struct Exp *optionalTest, struct Exp *body);
struct Exp *ForExp(int pos, struct Symbol *var, struct Exp *low, struct Exp *high, struct Exp *body);
struct Exp *BreakExp(int pos);
struct Exp *LetExp(int pos, struct DecList *decs, struct Exp *body);
struct Exp *ArrayExp(int pos, struct Symbol *type, struct Exp *size, struct Exp *init);
struct Dec *FunctionDec(int pos, struct FunDecList *function);
struct Dec *VarDec(int pos, struct Symbol *var, struct Symbol *type, struct Exp *init);
struct Dec *TypeDec(int pos, struct NameTyList *type);
struct Ty *NameTy(int pos, struct Symbol *name);
struct Ty *RecordTy(int pos, struct FieldList *record);
struct Ty *ArrayTy(int pos, struct Symbol *array);
struct Field *NewField(int pos, struct Symbol *name, struct Symbol *type);
struct FieldList *NewFieldList(struct Field *head, struct FieldList *tail);
struct ExpList *NewExpList(struct Exp *head, struct ExpList *tail);
struct FunDec *NewFunDec(int pos, struct Symbol *name, struct FieldList *params, struct Symbol *result, struct Exp *body);
struct FunDecList *NewFunDecList(struct FunDec *head, struct FunDecList *tail);
struct DecList *NewDecList(struct Dec *head, struct DecList *tail);
struct NameTy *NewNameTy(struct Symbol *name, struct Ty *ty);
struct DecList *NewNameTyList(struct NameTy *head, struct NameTyList *tail);
struct EField *NewEField(struct Symbol *name, struct Exp *exp);
struct EFieldList *NewEFieldList(struct EField *head, struct EFieldList *tail);