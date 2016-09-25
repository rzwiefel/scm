%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"

void yyerror(yyscan_t scanner, char const *msg);
%}

%define parse.error verbose
%define api.pure true
%lex-param {void *scanner}
%parse-param {void *scanner}

%union {
  char *str;
}

%token BOOLEAN_T FIXNUM_T FLONUM_T CHARACTER_T STRING_T SYMBOL_T

%%

exprs : %empty
      | exprs expr
      ;

expr : map
     | set
     | vec
     | list
     | quote
     | syntax_quote
     | syntax_unquote
     | atom
     ;

map : '{' pairs '}' { printf("map\n"); }
    ;

pairs : %empty
      | pairs pair
      ;

pair : expr expr
     ;

set : '#' '{' exprs '}' { printf("set\n"); }
    ;

vec : '[' exprs ']' { printf("vec\n"); }
    ;

list : '(' exprs ')' { printf("list\n"); }
     ;

quote : '\'' expr { printf("quote\n"); }
      ;

syntax_quote : '`' expr { printf("syntax quote\n"); }
             ;

syntax_unquote : ',' expr { printf("syntax unquote\n"); }
               ;

atom : BOOLEAN_T {printf("bool = %s\n", yylval.str);}
     | FIXNUM_T {printf("fixnum = %s\n", yylval.str);}
     | FLONUM_T { printf("flonum = %s\n", yylval.str); }
     | CHARACTER_T { printf("char = %s\n", yylval.str); }
     | STRING_T { printf("string = %s\n", yylval.str); }
     | SYMBOL_T { printf("symbol = %s\n", yylval.str); }
     ;

%%

void yyerror(yyscan_t scanner, const char *msg) {
  fprintf(stderr, "parse error: %s\n", msg);
}

