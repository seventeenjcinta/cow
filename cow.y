%{
#include <stdio.h>
#include "absyn.h"
#include "log.h"

struct Exp *absyn_root;
int yylex();

%}

%union {
    int pos;
    int ival;  
    char* sval;
    struct Symbol *symbol;
    struct Var *var;
    struct Exp *exp;
    struct Dec *dec;
    struct Ty *ty;
    struct Field *field;
    struct FieldList *fieldList;
    struct ExpList *expList;
    struct Fundec *fundec;
    struct FundecList *fundecList;
    struct DecList *decList;
    struct NameTy *nameTy;
    struct NameTyList *nameTyList;
    struct EField *eField;
    struct EFieldList *eFieldList;
}

%token <sval> ID STRING
%token <ival> INT
%token
    COMMA COLON SEMICOLON LPAREN RPAREN LBRACK RBRACK
    LBRACE RBRACE DOT
    ADD SUB MUL DIV EQ NEQ LT LT_EQ GT GT_EQ
    AND OR ASSIGN
    ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END OF
    BREAK NIL
    FUNCTION VAR TYPE
%type <exp> program main expr
%type <var> lvalue
%type <symbol> id
%type <expList> exprList exprListOpt exprSeq exprSeqOpt
%type <field> typeField
%type <fieldList> typeFieldList typeFieldListOpt
%type <dec> declaration functionDeclaration typeDeclaration variableDeclaration
%type <decList> declarationList
%type <ty> type
%type <eFieldList> fieldList fieldListOpt
%nonassoc LOW                               // 消除左值的歧义
%nonassoc THEN DO TYPE FUNCTION ID
%nonassoc ASSIGN LBRACK ELSE OF COMMA
%left OR
%left AND
%nonassoc EQ NEQ LT_EQ LT GT GT_EQ
%left ADD SUB
%left MUL DIV
%left USUB
%start program

%%

program : main  {absyn_root = $1;}
        ;

main    : /* empty */   {$$ = NULLL}
        | expr          {$$ = $1};
        ;

expr    : INT                                           {$$ = IntExp(LogTokenPos, $1);}
        | STRING                                        {$$ = StringExp(LogTokenPos, $1);}
        | NIL                                           {$$ = NilExp{LogTokenPos};}
        | lvalue                                        {$$ = VarExp(LogTokenPos, $1);}
        | SUB expr %prec USUB                           {$$ = OpExp(LogTokenPos, minus, $1, $3);}
        | expr MUL expr                                 {$$ = OpExp(LogTokenPos, times, $1, $3);}
        | expr DIV expr                                 {$$ = OpExp(LogTokenPos, divide, $1, $3);}
        | expr EQ expr                                  {$$ = OpExp(LogTokenPos, equal, $1, $3);}
        | expr NEQ expr                                 {$$ = OpExp(LogTokenPos, notequal, $1, $3);}
        | expr LT expr                                  {$$ = OpExp(LogTokenPos, lt, $1, $3);}
        | expr LT_EQ expr                               {$$ = OpExp(LogTokenPos, le, $1, $3);}
        | expr GT expr                                  {$$ = OpExp(LogTokenPos, gt, $1, $3);}
        | expr GT_EQ expr                               {$$ = OpExp(LogTokenPos, ge, $1, $3);}
        | expr AND expr                                 {$$ = IfExp(LogTokenPos, $1, $3, IntExp(LogTokenPos, 0));}
        | expr OR expr                                  {$$ = IfExp(LogTokenPos, $1, IntExp(LogTokenPos, 1), $3);}
        | lvalue ASSIGN expr                            {$$ = AssignExp(LogTokenPos, $1, $3);}
        | id LPAREN exprListOpt RPAREN                  {$$ = CallExp(LogTokenPos, $1, $3);}
        | LPAREN exprSeqOpt RPAREN                      {$$ = SeqExp(LogTokenPos, $2);}
        | id LBRACE fieldListOpt RBRACE                 {$$ = RecordExp(LogTokenPos, $1, $3);}
        | id LBRACK expr RBRACK OF expr                 {$$ = ArrayExp(LogTokenPos, $1, $3, $6);}
        | IF expr THEN expr                             {$$ = IfExp(LogTokenPos, $2, $4, NULL);}
        | IF expr THEN expr ELSE expr                   {$$ = IfExp(LogTokenPos, $2, $4, $6);}
        | WHILE expr DO expr                            {$$ = WhileExp(LogTokenPos, $2, $4);}
        | FOR id ASSIGN expr TO expr DO expr            {$$ = ForExp(LogTokenPos, $2, $4, $6, $8);}
        | BREAK                                         {$$ = BreakExp(LogTokenPos);}
        | LET declarationList IN exprSeqOpt END         {$$ = LetExp(LogTokenPos, $2, SeqExp(LogTokenPos, $4));}
        ;

lvalue  : id %prec LOW                                  {$$ = SimpleVar(LogTokenPos, $1);}
        | lvalue DOT id                                 {$$ = FieldVar(LogTokenPos, $1, $3);}
        | id LBRACK expr RBRACK                         {$$ = SubscriptVar(LogTokenPos, A_SimpleVar(LogTokenPos, $1), $3);}
        | lvalue LBRACK expr RBRACK                     {$$ = SubscriptVar(LogTokenPos, $1, $3);}
        ;

id      : ID  {$$ = NewSymbol($1);}
        ;

exprListOpt     : /* Empty */   {$$ = NULL;}
                | exprList      {$$ = $1;}
                ;

exprList        : expr                  {$$ = NewExpList($1, NULL);}
                | exprList COMMA expr   {$$ = NewExpList($3, $1);}
                ;

exprSeqOpt      : /* Empty */           {$$ = NULL;}
                | exprSeq               {$$ = $1;}
                ;

exprSeq         : expr                          {$$ = A_ExpList($1, NULL);}
                | exprSeq SEMICOLON expr        {$$ = A_ExpList($3, $1);}
                ;

fieldListOpt    : /* Empty */                   {$$ = NULL;}
                | fieldList                     {$$ = $1;}
                ;

fieldList       : id EQ expr                    {$$ = NewEfieldList(NewEfield($1, $3), NULL);}
                | fieldList COMMA id EQ expr    {$$ = NewEfieldList(NewEfield($3, $5), $1);}
                ;

declarationList : /* Empty */                   {$$ = NULL;}
                | declarationList declaration   {$$ = NewDecList($2, $1);}
                ;

declaration     : typeDeclaration       {$$ = $1;}
                | variableDeclaration   {$$ = $1;}
                | functionDeclaration   {$$ = $1;}
                ;

typeDeclaration : TYPE id EQ type {$$ = TypeDec(LogTokenPos, NewNametyList(A_Namety($2, $4), NULL));}
                ;

type    : id                                {$$ = NameTy(LogTokenPos, $1);}
        | LBRACE typeFieldListOpt RBRACE    {$$ = RecordTy(LogTokenPos, $2);}
        | ARRAY OF id                       {$$ = ArrayTy(LogTokenPos, $3);}
        ;

typeFieldListOpt    : /* Empty */   {$$ = NULL;}
                    | typeFieldList {$$ = $1;}
                    ;

typeFieldList   : typeField                     {$$ = NewFieldList($1, NULL);}
                | typeFieldList COMMA typeField {$$ = NewFieldList($3, $1);}
                ;

typeField       : id COLON id   {$$ = NewField(LogTokenPos, $1, $3);}
                ;

variableDeclaration     : VAR id ASSIGN expr            {$$ = VarDec(LogTokenPos, $2, NULL, $4);}
                        | VAR id COLON id ASSIGN expr   {$$ = VarDec(LogTokenPos, $2, $4, $6);}
                        ;

functionDeclaration     : FUNCTION id LPAREN typeFieldListOpt RPAREN EQ expr               {$$ = FunctionDec(LogTokenPos, FundecList(Fundec(LogTokenPos, $2, $4, NULL, $7), NULL));}
                        | FUNCTION id LPAREN typeFieldListOpt RPAREN COLON id EQ expr      {$$ = FunctionDec(LogTokenPos, FundecList(Fundec(LogTokenPos, $2, $4, $7, $9), NULL));}
                        ;

%%

int main()
{
    yyparse();

    return 0;
}