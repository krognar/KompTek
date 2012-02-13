%{
#include "parser.h"
#include "tree.h"

#ifdef DUMP_TOKENS
    #define RETURN(t) do {                                          \
        fprintf ( stderr, "TOKEN ( %d,\t'%s' )\n", t, yytext );     \
        return t;                                                   \
    } while ( 0 )
#else
    #define RETURN(t) return t
#endif
%}

%option array
%option noyywrap
%option yylineno


letter      [a-zA-Z_]
%%
"//".*\n                /*Comments*/
[\ \t\n]+               /*Whitespace*/
\"(\\\"|[^\"\n])*\"     { RETURN( STRING ); }
[0-9]+      { yylval=atoi(yytext); return( NUMBER );}
":="        { RETURN( ASSIGN ); }
"FUNC"      { RETURN( FUNC ); }
"PRINT"     { RETURN( PRINT ); }
"RETURN"    { RETURN( RETURN ); }
"CONTINUE"  { RETURN( CONTINUE ); }
"IF"        { RETURN( IF ); }
"THEN"      { RETURN( THEN ); }
"ELSE"      { RETURN( ELSE ); }
"FI"        { RETURN( FI ); }
"WHILE"     { RETURN( WHILE ); }
"DO"        { RETURN( DO ); }
"DONE"      { RETURN( DONE ); }
"VAR"       { RETURN( VAR ); }
{letter}({letter}1[0-9])*   { RETURN( IDENTIFIER ); }
"+"         { RETURN PLUS; }
"-"         { RETURN MINUS; }
"**"        { RETURN POWER; }
"*"         { RETURN MULT; }
"/"         { RETURN DIV; }
.           { RETURN( yytext[0] ); }
%%
