%define parse.error verbose
%define api.pure true
%locations
%token-table
%glr-parser
%lex-param {void *scanner}
%parse-param {void *scanner}

%{
#include <stdio.h>
#include <stdlib.h>
%}

%union {
  char *str;
}

%token BOOLEAN_T FIXNUM_T FLONUM_T CHARACTER_T STRING_T SYMBOL_T

%%

EXPR : ATOM
     | LIST
     ;

LIST : '(' ITEM ')' { printf("list\n"); }
     ;

ITEM : ITEM LIST
     | ITEM ATOM
     | %empty
     ;

ATOM : BOOLEAN_T {printf("bool = %s\n", yylval.str);}
     | FIXNUM_T {printf("fixnum = %s\n", yylval.str);}
     | FLONUM_T { printf("flonum = %s\n", yylval.str); }
     | CHARACTER_T { printf("char = %s\n", yylval.str); }
     | STRING_T { printf("string = %s\n", yylval.str); }
     | SYMBOL_T { printf("symbol = %s\n", yylval.str); }
     ;

%%

int
yyerror(YYLTYPE *locp, char *msg) {
  if (locp) {
    fprintf(stderr, "parse error: %s (:%d.%d -> :%d.%d)\n",
                    msg,
                    locp->first_line, locp->first_column,
                    locp->last_line,  locp->last_column
    );
    /* todo: add some fancy ^^^^^ error handling here */
  } else {
    fprintf(stderr, "parse error: %s\n", msg);
  }
  return (0);
}

int main (int argc, char** argv) {
  /*int result;
  yyscan_t scanner;
  yylex_init(&scanner);
  result = (yyparse(scanner));
  yylex_destroy(scanner);
  return (result);*/
}
