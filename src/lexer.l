%{
#include "token.h"
#include "parser.h"
%}

%option reentrant bison-bridge
%option warn noyywrap nodefault
%option nounput
%option noinput

FIXNUM 0|[1-9]{DIGIT}*
FLONUM {FIXNUM}\.{DIGIT}+

LETTER [a-zA-Z]
SPECIAL_INITIAL [!$%&*/:<=>?\^_~]
SPECIAL_SUBSEQUENT [+-.@]
DIGIT [0-9]
PECULIAR_IDENTIFIER (\+|\-|\.\.\.)
INITIAL {LETTER}|{SPECIAL_INITIAL}
SUBSEQUENT {INITIAL}|{DIGIT}|{SPECIAL_SUBSEQUENT}
SYMBOL {INITIAL}{SUBSEQUENT}*|{PECULIAR_IDENTIFIER}

CHARACTER_NAME (?i:space|newline)

CHARACTER #\\({CHARACTER_NAME}|.)

STRING \"{STRING_ELEMENT}*\"
STRING_ELEMENT \\\\|\\\"|[^"\\]

LBRACE \(
RBRACE \)

BOOLEAN #t|#f

%%

;.*
("\n"|"\t"|" ")+

{FIXNUM}          { yylval->str = yytext; return FIXNUM_T; }
{FLONUM}          { yylval->str = yytext; return FLONUM_T; }
{STRING}          { yylval->str = yytext; return STRING_T; }
{SYMBOL}          { yylval->str = yytext; return SYMBOL_T; }
{CHARACTER}       { yylval->str = yytext; return CHARACTER_T; }
{BOOLEAN}         { yylval->str = yytext; return BOOLEAN_T; }

. { printf("token = %s\n", yytext); return *yytext; }

%%
