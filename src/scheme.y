%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
%}

%union {
  char *str;
}

%token BOOLEAN FIXNUM FLONUM CHARACTER STRING

%%

EXPR : ATOM
     | LIST
     ;

LIST : '(' ITEMS ')'

ITEMS : ITEMS LIST
      | ITEMS ATOM
      |
      ;

ATOM : BOOLEAN
     | FIXNUM
     | FLONUM
     | CHARACTER
     | STRING
     ;

%%

void yyerror(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(1);
}

int main() {
  yyparse();
}
