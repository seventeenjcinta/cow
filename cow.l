%{
#include <stdio.h>
#include <stdlib.h>
// #include "cow.tab.h"

#define VOID 		1 	// void
#define CHAR 		2 	// char
#define INT 		3 	// int
#define FLOAT 		4 	// float
#define DOUBLE 		5 	// double
#define SHORT 		6 	// short
#define LONG 		7 	// long
#define SINGED 		8 	// singed
#define UNSINGED 	9 	// unsigned
#define STRUCT 		10 	// struct 
#define UNION 		11 	// union
#define ENUM 		12 	// enum
#define TYPEDF 		13 	// typedef
#define SIZEOF 		14 	// sizeof 
#define AUTO 		15 	// auto
#define STATIC 		16 	// static
#define REGISTER 	17 	// register
#define EXTERN 		18 	// extern
#define CONST 		19 	// const
#define VOLATILE 	20 	// volatile
#define RETURN 		21 	// return 
#define CONTINUE 	22 	// continue
#define BREAK 		23 	// break 
#define GOTO 		24 	// goto
#define IF 			25 	// if  
#define ELSE 		26 	// else
#define SWITCH 		27 	// switch 
#define CASE 		28 	// case 
#define DEFAULT 	29 	// default
#define FOR 		30 	// for 
#define DO 			31 	// do
#define WHILE 		32 	// while 
#define SCANF 		33 	// scanf
#define PRINTF 		34 	// printf
#define LC 			35 	// {
#define RC 			36 	//}
#define LB 			37 	// [
#define RB 			38 	// ] 
#define LP 			39 	// ( 
#define RP 			40 	// ) 
#define DOT 		41 	// .
#define STRUCTOP 	42 	// ->
#define LOGRE 		43 	// ~
#define INPLUS 		44 	// ++ 
#define INMINUS 	45 	// -- 
#define LOCRE 		46 	// ! 
#define AND 		47 	// &
#define STAR 		48 	// *
#define DIVOP 		49 	// /
#define COMOP 		50 	// %
#define PLUS 		51 	// + 
#define MINUS 		52 	// -
#define SHIFTR 		53 	// >>
#define SHIFTL 		54 	// <<
#define RELG 		55 	// > 
#define RELGEQ 		56 	// >= 
#define RELL 		57 	// < 
#define RELLEQ 		58 	// <=
#define EQUOP 		59 	// = = 
#define UEQUOP 		60 	// ! =
#define XOR 		61 	// ^ 
#define OR 			62 	// | 
#define ANDAND 		63  // &&
#define OROR 		64 	// ||
#define QUEST 		65  // ?
#define EQUAL 		66 	// = 
#define ASSIGNDIV 	67 	// / =
#define ASSIGNSTAR 	68 	// * =
#define ASSIGNCOM 	69 	// % =
#define ASSIGNPLUS 	70 	// + =
#define ASSIGNMINUS 71 	// - =
#define ASSIGNAND 	72 	// & =
#define ASSIGNXOR 	73 	// ^ =
#define ASSIGNOR 	74 	// | =
#define COMMA 		75 	// , 
#define SHA 		76 	// # 
#define SEMI 		77 	// ; 
#define COLON 		78	// : 
#define ID 			79 	// 标识符
#define NUMBER 		80 	// 数字
#define STRING      81  // 字符串
#define ERRORCHAR   82	// 非法
%}
delim   			[\\n\\t\\r" ""]
ws   				{delim}+
digit 				[0-9]
letter 				[A-Za-z]
id 					({letter}|_)({letter}|{digit}|_)*
number				{digit}+(\.{digit}+)?(E[+-]?{digit}+)?					
string				\"(\\.|[^"\\\n])*\"
%%
{ws} 				{;}
void                {return VOID;}
char 				{return CHAR;}
int 				{return INT;}
float 				{return FLOAT;}
double				{return DOUBLE;}
short 				{return SHORT;}
long 				{return LONG;}
singed 				{return SINGED;}
unsigned 			{return UNSINGED;}
struct 				{return STRUCT;}
union				{return UNION;}
enum 				{return ENUM;}
typedef 			{return TYPEDF;}
sizeof  			{return SIZEOF;}
auto 				{return AUTO;}
static              {return STATIC;}
register 			{return REGISTER;}
extern 				{return EXTERN;}
const 				{return CONST;}
volatile 			{return VOLATILE;}
return  			{return RETURN;}
continue 			{return CONTINUE;}
break  				{return BREAK;}
goto 				{return GOTO;}
if 				 	{return IF;}
else 				{return ELSE;}
switch 				{return SWITCH;}
case  				{return CASE;}
default 			{return DEFAULT;}
for  				{return FOR;}
do 					{return DO;}
while  				{return WHILE;}
scanf 				{return SCANF;}
printf 				{return PRINTF;}
"/*"[^}\n]*"*/"     {;}	// 删除注释
"//"[^}\n]*   		{;}	// 删除注释
{id} 				{return ID;}
{number}  			{return NUMBER;}
{string}			{return STRING;}
"{"  				{return LC;}
"}"  				{return RC;}
"["  				{return LB;}
"]"  				{return RB;}
"("  				{return LP;}
")"  				{return RP;}
"."  				{return DOT;}
"->"  				{return STRUCTOP;}
"~"  				{return LOGRE;}
"++"  				{return INPLUS;}
"--"  				{return INMINUS;}
"!"  				{return LOCRE;}
"&"  				{return AND;}
"*"  				{return STAR;}
"/"  				{return DIVOP;}
"%"  				{return COMOP;}
"+"  				{return PLUS;}
"-"  				{return MINUS;}
">>"  				{return SHIFTR;}
"<<"  				{return SHIFTL;}
">"  				{return RELG;}
">="  				{return RELGEQ;}
"<"  				{return RELL;}
"<="  				{return RELLEQ;}
"=="  				{return EQUOP;}
"!="  				{return UEQUOP;}
"^"  				{return XOR;}
"|"  				{return OR;}
"&&"  				{return ANDAND;}
"||" 				{return OROR;}
"?"  				{return QUEST;}
"="  				{return EQUAL;}
"/="  				{return ASSIGNDIV;}
"*="  				{return ASSIGNSTAR;}
"%="  				{return ASSIGNCOM;}
"+="  				{return ASSIGNPLUS;}
"-="  				{return ASSIGNMINUS;}
"&="  				{return ASSIGNAND;}
"^="  				{return ASSIGNXOR;}
"|="  				{return ASSIGNOR;}
","  				{return COMMA;}
"#"  				{return SHA;}
";"  				{return SEMI;}
":"  				{return COLON;}
.			 		{return ERRORCHAR;}

%%

void writeFile(int number)
{
	switch(number) {
		case VOID: 				fprintf(yyout, "(%d, %s)\n", VOID, yytext); break;
		case CHAR: 				fprintf(yyout, "(%d, %s)\n", CHAR, yytext); break;
		case INT: 				fprintf(yyout, "(%d, %s)\n", INT, yytext); break;
		case FLOAT: 			fprintf(yyout, "(%d, %s)\n", FLOAT, yytext); break;
		case DOUBLE: 			fprintf(yyout, "(%d, %s)\n", DOUBLE, yytext); break;
		case SHORT: 			fprintf(yyout, "(%d, %s)\n", SHORT, yytext); break;
		case LONG: 				fprintf(yyout, "(%d, %s)\n", LONG, yytext); break;
		case SINGED: 			fprintf(yyout, "(%d, %s)\n", SINGED, yytext); break;
		case UNSINGED: 			fprintf(yyout, "(%d, %s)\n", UNSINGED, yytext); break;
		case STRUCT: 			fprintf(yyout, "(%d, %s)\n", STRUCT, yytext); break;
		case UNION: 			fprintf(yyout, "(%d, %s)\n", UNION, yytext); break;
		case ENUM: 				fprintf(yyout, "(%d, %s)\n", ENUM, yytext); break;
		case TYPEDF: 			fprintf(yyout, "(%d, %s)\n", TYPEDF, yytext); break;
		case SIZEOF: 			fprintf(yyout, "(%d, %s)\n", SIZEOF, yytext); break;
		case AUTO: 				fprintf(yyout, "(%d, %s)\n", AUTO, yytext); break;
		case STATIC: 			fprintf(yyout, "(%d, %s)\n", STATIC, yytext); break;
		case REGISTER: 			fprintf(yyout, "(%d, %s)\n", REGISTER, yytext); break;
		case EXTERN: 			fprintf(yyout, "(%d, %s)\n", EXTERN, yytext); break;
		case CONST: 			fprintf(yyout, "(%d, %s)\n", CONST, yytext); break;
		case VOLATILE: 			fprintf(yyout, "(%d, %s)\n", VOLATILE, yytext); break;
		case RETURN: 			fprintf(yyout, "(%d, %s)\n", RETURN, yytext); break;
		case CONTINUE: 			fprintf(yyout, "(%d, %s)\n", CONTINUE, yytext); break;
		case BREAK: 			fprintf(yyout, "(%d, %s)\n", BREAK, yytext); break;
		case GOTO: 				fprintf(yyout, "(%d, %s)\n", GOTO, yytext); break;
		case IF: 				fprintf(yyout, "(%d, %s)\n", IF, yytext); break;
		case ELSE: 				fprintf(yyout, "(%d, %s)\n", ELSE, yytext); break;
		case SWITCH: 			fprintf(yyout, "(%d, %s)\n", SWITCH, yytext); break;
		case CASE: 				fprintf(yyout, "(%d, %s)\n", CASE, yytext); break;
		case DEFAULT: 			fprintf(yyout, "(%d, %s)\n", DEFAULT, yytext); break;
		case FOR: 				fprintf(yyout, "(%d, %s)\n", FOR, yytext); break;
		case DO: 				fprintf(yyout, "(%d, %s)\n", DO, yytext); break;
		case WHILE: 			fprintf(yyout, "(%d, %s)\n", WHILE, yytext); break;
		case SCANF: 			fprintf(yyout, "(%d, %s)\n", SCANF, yytext); break;
		case PRINTF: 			fprintf(yyout, "(%d, %s)\n", PRINTF, yytext); break;
		case ID: 				fprintf(yyout, "(%d, %s)\n", ID, yytext); break;
		case NUMBER: 			fprintf(yyout, "(%d, %s)\n", NUMBER, yytext); break;
		case STRING: 			fprintf(yyout, "(%d, %s)\n", STRING, yytext); break;
		case LC: 				fprintf(yyout, "(%d, %s)\n", LC, yytext); break;
		case RC: 				fprintf(yyout, "(%d, %s)\n", RC, yytext); break;
		case LB: 				fprintf(yyout, "(%d, %s)\n", LB, yytext); break;
		case RB: 				fprintf(yyout, "(%d, %s)\n", RB, yytext); break;
		case LP: 				fprintf(yyout, "(%d, %s)\n", LP, yytext); break;
		case RP: 				fprintf(yyout, "(%d, %s)\n", RP, yytext); break;
		case DOT: 				fprintf(yyout, "(%d, %s)\n", DOT, yytext); break;
		case STRUCTOP: 			fprintf(yyout, "(%d, %s)\n", STRUCTOP, yytext); break;
		case LOGRE: 			fprintf(yyout, "(%d, %s)\n", LOGRE, yytext); break;
		case INPLUS: 			fprintf(yyout, "(%d, %s)\n", INPLUS, yytext); break;
		case INMINUS: 			fprintf(yyout, "(%d, %s)\n", INMINUS, yytext); break;
		case LOCRE: 			fprintf(yyout, "(%d, %s)\n", LOCRE, yytext); break;
		case AND: 				fprintf(yyout, "(%d, %s)\n", AND, yytext); break;
		case STAR: 				fprintf(yyout, "(%d, %s)\n", STAR, yytext); break;
		case DIVOP: 			fprintf(yyout, "(%d, %s)\n", DIVOP, yytext); break;
		case COMOP: 			fprintf(yyout, "(%d, %s)\n", COMOP, yytext); break;
		case PLUS: 				fprintf(yyout, "(%d, %s)\n", PLUS, yytext); break;
		case MINUS: 			fprintf(yyout, "(%d, %s)\n", MINUS, yytext); break;
		case SHIFTR: 			fprintf(yyout, "(%d, %s)\n", SHIFTR, yytext); break;
		case SHIFTL: 			fprintf(yyout, "(%d, %s)\n", SHIFTL, yytext); break;
		case RELG: 				fprintf(yyout, "(%d, %s)\n", RELG, yytext); break;
		case RELGEQ: 			fprintf(yyout, "(%d, %s)\n", RELGEQ, yytext); break;
		case RELL: 				fprintf(yyout, "(%d, %s)\n", RELL, yytext); break;
		case RELLEQ: 			fprintf(yyout, "(%d, %s)\n", RELLEQ, yytext); break;
		case EQUOP: 			fprintf(yyout, "(%d, %s)\n", EQUOP, yytext); break;
		case UEQUOP: 			fprintf(yyout, "(%d, %s)\n", UEQUOP, yytext); break;
		case XOR: 				fprintf(yyout, "(%d, %s)\n", XOR, yytext); break;
		case OR: 				fprintf(yyout, "(%d, %s)\n", OR, yytext); break;
		case ANDAND: 			fprintf(yyout, "(%d, %s)\n", ANDAND, yytext); break;
		case OROR: 				fprintf(yyout, "(%d, %s)\n", OROR, yytext); break;
		case QUEST: 			fprintf(yyout, "(%d, %s)\n", QUEST, yytext); break;
		case EQUAL: 			fprintf(yyout, "(%d, %s)\n", EQUAL, yytext); break;
		case ASSIGNDIV: 		fprintf(yyout, "(%d, %s)\n", ASSIGNDIV, yytext); break;
		case ASSIGNSTAR: 		fprintf(yyout, "(%d, %s)\n", ASSIGNSTAR, yytext); break;
		case ASSIGNCOM: 		fprintf(yyout, "(%d, %s)\n", ASSIGNCOM, yytext); break;
		case ASSIGNPLUS: 		fprintf(yyout, "(%d, %s)\n", ASSIGNPLUS, yytext); break;
		case ASSIGNMINUS: 		fprintf(yyout, "(%d, %s)\n", ASSIGNMINUS, yytext); break;
		case ASSIGNAND: 		fprintf(yyout, "(%d, %s)\n", ASSIGNAND, yytext); break;
		case ASSIGNXOR: 		fprintf(yyout, "(%d, %s)\n", ASSIGNXOR, yytext); break;
		case ASSIGNOR: 			fprintf(yyout, "(%d, %s)\n", ASSIGNOR, yytext); break;
		case COMMA: 			fprintf(yyout, "(%d, %s)\n", COMMA, yytext); break;
		case SHA: 				fprintf(yyout, "(%d, %s)\n", SHA, yytext); break;
		case SEMI: 				fprintf(yyout, "(%d, %s)\n", SEMI, yytext); break;
		case COLON: 			fprintf(yyout, "(%d, %s)\n", COLON, yytext); break;
		default:				break;
	}
	
}


int main()
{ 
	int number;

	yyin = fopen("input", "r");
	yyout = fopen("output", "w");
	if(yyin != NULL) {
		while(number = yylex()) {
			writeFile(number);
		}
	}

	return 0;
}
