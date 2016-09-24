%{
#include "token.h"
#define YY_DECL token_t *yylex(void)

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

%option noyywrap
%option nounput
%option noinput

%%

;.*               ret_token(IGNORE)
("\n"|"\t"|" ")+  ret_token(IGNORE)

\'                ret_token(QUOTE)

{FIXNUM}          ret_token(FIXNUM)
{FLONUM}          ret_token(FLONUM)
{STRING}          ret_token(STRING)
{SYMBOL}          ret_token(SYMBOL)
{CHARACTER}       ret_token(CHARACTER)
{BOOLEAN}         ret_token(BOOLEAN)

{LBRACE}          ret_token(LBRACE)
{RBRACE}          ret_token(RBRACE)

\.                ret_token(DOT)

<<EOF>>           ret_token(ENDOFINPUT)

%%
