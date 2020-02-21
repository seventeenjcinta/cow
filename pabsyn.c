/* local function prototypes */
#include <stdio.h>
#include "util.h"
#include "symbol.h" // symbol table data structures 
#include "absyn.h"  // abstract syntax data structures
#include "pabsyn.h"

static char opers[][12] = { "PLUS", 
                            "MINUS", 
                            "TIMES", 
                            "DIVIDE",
                            "EQUAL", 
                            "NOTEQUAL", 
                            "LESSTHAN", 
                            "LESSEQ", 
                            "GREAT", 
                            "GREATEQ"
                            };

static void pVar(FILE *fileOut, struct Var * v, int d);
static void pDec(FILE *fileOut, struct Dec *v, int d);
static void pTy(FILE *fileOut, struct Ty *v, int d);
static void pField(FILE *fileOut, struct Field *v, int d);
static void pFieldList(FILE *fileOut, struct FieldList *v, int d);
static void pExpList(FILE *fileOut, struct ExpList *v, int d);
static void pFunDec(FILE *fileOut, struct FunDec *v, int d);
static void pFunDecList(FILE *fileOut, struct FunDecList *v, int d);
static void pDecList(FILE *fileOut, struct DecList *v, int d);
static void pNameTy(FILE *fileOut, struct NameTy *v, int d);
static void pNameTyList(FILE *fileOut, struct NameTyList *v, int d);
static void pEField(FILE *fileOut, struct EField *v, int d);
static void pEFieldList(FILE *fileOut, struct EFieldList *v, int d);

// 打印缩进
static void pIndent(FILE *fileOut, int indentNum)
{
    for(int i = 0; i < indentNum; i ++) {
        fprintf(fileOut, " ");
    }
}

static void pOper(FILE *fileOut, Oper index) 
{
    fprintf(fileOut, "%s", opers[index]);
}

/* Print struct Var * types. Indent d spaces. */
static void pVar(FILE *fileOut, struct Var *v, int indentNum)
{
    pIndent(fileOut, indentNum);
    switch(v -> kind) {
    case simpleVar:
        fprintf(fileOut, "simpleBar(%s)", SymbolGetName(v -> uni.symbol));
        break;
    case fieldVar:
        fprintf(fileOut, "%s\n", "fieldVar(");
        pVar(fileOut, v -> uni.field.var, indentNum + 1);
        fprintf(fileOut, "%s\n", "%s\n", ",");
        pIndent(fileOut, indentNum + 1);
        fprintf(fileOut, "%s)", SymbolGetName(v -> uni.field.sym));
        break;
    case subscriptVar:
        fprintf(fileOut, "%s\n", "subscriptVar(");
        pVar(fileOut, v -> uni.field.var, indentNum + 1);
        fprintf(fileOut, "%s\n", ",");
        pExp(fileOut, v -> uni.subscript.exp, indentNum + 1);
        fprintf(fileOut, "%s\n", ")");
        break;
    default:
        fprintf(fileOut, "%s\n", "error");
        break;
    }
}

/* Print struct Exp * types. Indent d spaces. */
void pExp(FILE *fileOut, struct Exp *e, int indentNum) {
    pIndent(fileOut, indentNum);
    switch(e -> kind) {
    case varExp:
        fprintf(fileOut, "varExp(\n");
        pVar(fileOut, e -> uni.var, indentNum + 1);
        fprintf(fileOut, "%s", ")");
        break;
    case nilExp:
        fprintf(fileOut, "nilExp()");
        break;
    case intExp:
        fprintf(fileOut, "intExp(%d)", e -> uni.intager);
        break;
    case stringExp:
        fprintf(fileOut, "stringExp(%s)", e -> uni.string);
        break;
    case callExp:
        fprintf(fileOut, "callExp(%s,\n", SymbolGetName(e -> uni.call.func));
        pExpList(fileOut, e -> uni.call.args, indentNum + 1);
        fprintf(fileOut, ")");
        break;
    case opExp:
        fprintf(fileOut, "opExp(\n");
        indent(fileOut, indentNum + 1);
        pOper(fileOut, e -> uni.op.oper); 
        fprintf(fileOut, ",\n");
        pExp(fileOut, e -> uni.op.left, indentNum + 1); 
        fprintf(fileOut, ",\n");
        pExp(fileOut, e -> uni.op.right, indentNum + 1); 
        fprintf(fileOut, ")");
        break;
    case recordExp:
        fprintf(fileOut, "recordExp(%s,\n", SymbolGetName(e -> uni.record.type));
        peFieldList(fileOut, e -> uni.record.fields, indentNum + 1); 
        fprintf(fileOut, ")");
        break;
    case seqExp:
        fprintf(fileOut, "seqExp(\n");
        pExpList(fileOut, e -> uni.seq, indentNum + 1); 
        fprintf(fileOut, ")");
        break;
    case assignExp:
        fprintf(fileOut, "assignExp(\n");
        pVar(fileOut, e->uni.assign.var, indentNum + 1); 
        fprintf(fileOut, ",\n");
        pExp(fileOut, e->uni.assign.exp, indentNum + 1); 
        fprintf(fileOut, ")");
        break;
    case ifExp:
        fprintf(fileOut, "iffExp(\n");
        pExp(fileOut, e->uni.optionalIf.optionaltest, indentNum + 1); 
        fprintf(fileOut, ",\n");
        pExp(fileOut, e->uni.optionalIf.optionalthen, indentNum + 1);
        if (e -> uni.optionalIf.optionalElse) { /* else is optional */
            fprintf(fileOut, ",\n");
            pExp(fileOut, e -> uni.optionalIf.optionalElse, indentNum + 1);
        }
        fprintf(fileOut, ")");
        break;
    case whileExp:
        fprintf(fileOut, "whileExp(\n");
        pExp(fileOut, e -> uni.optioinalWhile.optionaltest, indentNum + 1); fprintf(fileOut, ",\n");
        pExp(fileOut, e -> uni.optioinalWhile.body, indentNum + 1); fprintf(fileOut, ")\n");
        break;
    case forExp:
        fprintf(fileOut, "forExp(%s,\n", SymbolGetName(e -> uni.optionalFor.var));
        pExp(fileOut, e -> uni.optionalFor.low, indentNum + 1); 
        fprintf(fileOut, ",\n");
        pExp(fileOut, e -> uni.optionalFor.high, indentNum + 1); 
        fprintf(fileOut, "%s\n", ",");
        pExp(fileOut, e -> uni.optionalFor.body, indentNum + 1); 
        fprintf(fileOut, ",\n");
        indent(fileOut, indentNum + 1); 
        fprintf(fileOut, "%s", e -> uni.optionalFor.escape ? "TRUE)" : "FALSE)");
        break;
    case breakExp:
        fprintf(fileOut, "breakExp()");
        break;
    case letExp:
        fprintf(fileOut, "letExp(\n");
        pEecList(fileOut, e -> uni.let.decs, indentNum + 1); 
        fprintf(fileOut, ",\n");
        pExp(fileOut, e -> uni.let.body, indentNum + 1); 
        fprintf(fileOut, ")");
        break;
    case arrayExp:
        fprintf(fileOut, "arrayExp(%s,\n", SymbolGetName(e -> uni.array.type));
        pExp(fileOut, e -> uni.array.size, indentNum + 1); 
        fprintf(fileOut, ",\n");
        pExp(fileOut, e -> uni.array.init, indentNum + 1); 
        fprintf(fileOut, ")");
        break;
    default:
        assert(0);
    }
}

static void pDec(FILE *fileOut, struct Dec *d, int indentNum) {
    pIndent(fileOut, d);
    switch(d -> kind) {
    case functionDec:
        fprintf(fileOut, "functionDec(\n");
        pFunDecList(fileOut, d -> uni.function, indentNum + 1);
        fprintf(fileOut, ")");
        break;
    case varDec:
        fprintf(fileOut, "varDec(%s,\n", SymbolGetName(d -> uni.var.var));
        if (d -> uni.var.type) {
            indent(fileOut, indentNum + 1); 
            fprintf(fileOut, "%s,\n", SymbolGetName(d -> uni.var.type));
        }
        pExp(fileOut, d -> uni.var.init, indentNum + 1); 
        fprintf(fileOut, ",\n");
        indent(fileOut, indentNum + 1); fprintf(fileOut, "%s", d -> uni.var.escape ? "TRUE)" : "FALSE)");
        break;
    case typeDec:
        fprintf(fileOut, "typeDec(\n");
        pNameTyList(fileOut, d -> uni.type, indentNum + 1); 
        fprintf(fileOut, ")");
        break;
    default:
        assert(0);
    }
}

static void pTy(FILE *fileOut, struct Ty *t, int indentNum) {
    indent(fileOut, indentNum);
    switch(t -> kind) {
    case nameTy:
        fprintf(fileOut, "nameTy(%s)", SymbolGetName(t -> uni.name));
        break;
    case recordTy:
        fprintf(fileOut, "recordTy(\n");
        pFieldList(fileOut, t -> uni.record, indentNum + 1);
        fprintf(fileOut, ")");
        break;
    case arrayTy:
        fprintf(fileOut, "arrayTy(%s)", SymbolGetName(t -> uni.array));
        break;
    default:
        assert(0);
    }
}

static void pfield(FILE *fileOut, struct Field *f, int indentNum) {
    indent(fileOut, indentNum);
    fprintf(fileOut, "field(%s,\n", SymbolGetName(f -> name));
    indent(fileOut, indentNum + 1); 
    fprintf(fileOut, "%s,\n", SymbolGetName(f -> type));
    indent(fileOut, indentNum + 1); 
    fprintf(fileOut, "%s", f -> escape ? "TRUE)" : "FALSE)");
}

static void pFieldList(FILE *fileOut, struct FieldList *f, int indentNum) {
    indent(fileOut, indentNum);
    if(f) {
        fprintf(fileOut, "fieldList(\n");
        pField(fileOut, f -> head, indentNum + 1);
        fprintf(fileOut, ",\n");
        pFieldList(fileOut, f -> tail, indentNum + 1); 
        fprintf(fileOut, ")");
    } else {
        fprintf(fileOut, "fieldList()");
    }
}

static void pExpList(FILE *fileOut, struct ExpList *e, int indentNum) {
    indent(fileOut, indentNum);
    if(e) {
        fprintf(fileOut, "expList(\n");
        pExp(fileOut, e -> head, indentNum + 1);
        fprintf(fileOut, ",\n");
        pExpList(fileOut, e -> tail, indentNum + 1);
        fprintf(fileOut, ")");
    } else {
        fprintf(fileOut, "expList()");
    }
}

static void pfunDec(FILE *fileOut, struct FunDec *f, int indentNum) {
    indent(fileOut, indentNum);
    fprintf(fileOut, "funDec(%s,\n", SymbolGetName(f -> name));
    pFieldList(fileOut, f -> params, indentNum + 1);
    fprintf(fileOut, ",\n");
    if(f -> result) {
        indent(fileOut, indentNum + 1); 
        fprintf(fileOut, "%s,\n", SymbolGetName(f -> result));
    }
    pExp(fileOut, f -> body, indentNum + 1);
    fprintf(fileOut, ")");
}

static void pfunDecList(FILE *fileOut, struct FunDecList *f, int indentNum) {
    indent(fileOut, indentNum);
    if(f) {
        fprintf(fileOut, "funDecList(\n");
        pFunDec(fileOut, f -> head, indentNum + 1);
        fprintf(fileOut, ",\n");
        pFunDecList(fileOut, f -> tail, indentNum + 1);
        fprintf(fileOut, ")");
    } else {
        fprintf(fileOut, "funDecList()");
    }
}

static void pDecList(FILE *fileOut, struct DecList *d, int indentNum) {
    indent(fileOut, indentNum);
    if(d) {
        fprintf(fileOut, "decList(\n");
        pDec(fileOut, d -> head, indentNum + 1); 
        fprintf(fileOut, ",\n");
        pDecList(fileOut, d -> tail, indentNum + 1);
        fprintf(fileOut, ")");
    }
    else {
        fprintf(fileOut, "decList()");
    }
}

static void pNameTy(FILE *fileOut, struct NameTy *n, int indentNum) {
    indent(fileOut, indentNum);
    fprintf(fileOut, "nameTy(%s,\n", SymbolGetName(n -> name));
    pty(fileOut, n -> ty, indentNum + 1); 
    fprintf(fileOut, ")");
}

static void pNameTyList(FILE *fileOut, struct NameTyList *n, int indentNum) {
    indent(fileOut, n);
    if(n) {
        fprintf(fileOut, "nameTyList(\n");
        pnameTy(fileOut, n -> head, indentNum + 1); 
        fprintf(fileOut, ",\n");
        pnameTyList(fileOut, n -> tail, indentNum + 1); 
        fprintf(fileOut, ")");
    } else {
        fprintf(fileOut, "nameTyList()");
    }
}

static void pEField(FILE *fileOut, struct EField *e, int indentNum) {
    indent(fileOut, indentNum);
    if(e) {
        fprintf(fileOut, "eField(%s,\n", SymbolGetName(e -> name));
        pExp(fileOut, e -> exp, indentNum + 1);
        fprintf(fileOut, ")");
    } else {
        fprintf(fileOut, "eField()");
    }
}

static void pEFieldList(FILE *fileOut, struct EFieldList *e, int indentNum) {
    indent(fileOut, indentNum);
    if(e) {
        fprintf(fileOut, "eFieldList(\n");
        pEField(fileOut, e -> head, indentNum + 1); 
        fprintf(fileOut, ",\n");
        pEFieldList(fileOut, e -> tail, indentNum + 1); 
        fprintf(fileOut, ")");
    }
    else {
        fprintf(fileOut, "eFieldList()");
    }
}