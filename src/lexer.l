%option bison-bridge
%option bison-locations
%option ecs
%option nodefault
%option noyywrap
%option reentrant
%option stack
%option warn
%option yylineno


%{
#include "token.h"
#include "parser.h"

#define YY_DECL int yylex(void)
#define ret_token(type) return make_token(type,yytext);
%}

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

{FIXNUM}          { return FIXNUM_T; }
{FLONUM}          { return FLONUM_T; }
{STRING}          { return STRING_T; }
{SYMBOL}          { return SYMBOL_T; }
{CHARACTER}       { return CHARACTER_T; }
{BOOLEAN}         { return BOOLEAN_T; }

. { printf("token = %s\n", yytext); return *yytext; }

%%
