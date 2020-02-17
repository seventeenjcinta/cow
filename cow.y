%{
#include <stdio.h>

int yylex();

%}

%union {
    int pos;
    int ival;  
    char* sval;
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
%type