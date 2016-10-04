%{
#include <stdio.h>
#include <stdlib.h>

#include "types.h"

#include "parser.h"
#include "lexer.h"

void yyerror(yyscan_t scanner, object_t **obj, char const *msg);
%}

%define parse.error verbose
%define api.pure full
%lex-param {void *scanner}
%parse-param {void *scanner} {object_t **obj}

%union {
  char *str;
  object_t *obj;
}

%token BOOLEAN_T FIXNUM_T FLONUM_T CHARACTER_T STRING_T SYMBOL_T

%type <obj> atom
%type <obj> list
%type <obj> exprs
%type <obj> expr
%type <obj> quote
%type <obj> vector

%%

form : %empty { *obj = &eof; YYACCEPT; }
     | expr { *obj = $1; YYACCEPT; }
     ;

expr : atom
     | list
     | quote
     | vector
     ;

list : '(' exprs ')' { $$ = $2; }
     | '(' ')' { $$ = NULL; }
     ;

vector : '[' exprs ']' { $$ = cons(make_symbol("vector"), $2); }
       | '[' ']' { $$ = cons(make_symbol("vector"), NULL); }
       ;

exprs : %empty { $$ = NULL; }
      | expr exprs { $$ = cons($1, $2); }
      ;

quote : '\'' expr { $$ = cons(make_symbol("quote"), cons($2, NULL)); }
      ;

atom : BOOLEAN_T    { $$ = make_boolean(yylval.str); }
     | FIXNUM_T     { $$ = make_fixnum(yylval.str);  }
     | FLONUM_T     { $$ = make_fixnum(yylval.str);  }
     | CHARACTER_T  { $$ = make_char(yylval.str);    }
     | STRING_T     { $$ = make_string(yylval.str);  }
     | SYMBOL_T     { $$ = make_symbol(yylval.str);  }
     ;

%%

void yyerror(yyscan_t scanner, object_t **obj, const char *msg) {
  fprintf(stderr, "parse error: %s\n", msg);
}

