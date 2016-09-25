#include "parser.h"
#include "lexer.h"

int main (int argc, char** argv) {
  yyscan_t scanner;

  yylex_init(&scanner);
  yyset_in(stdin, scanner);

  yyparse(scanner);

  yylex_destroy(scanner);

  return 0;
}
