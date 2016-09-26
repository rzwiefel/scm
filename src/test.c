#include "vm.h"
#include "types.h"
#include "print.h"
#include "eval.h"

#include "parser.h"
#include "lexer.h"

vm_t *vm = NULL;

int main (int argc, char** argv) {
  yyscan_t scanner;

  yylex_init(&scanner);
  yyset_in(stdin, scanner);

  vm = make_vm();
  vm_set_root_env(vm, init());
  object_t *expr = NULL;

  while (yyparse(scanner, &expr) == 0 && expr != -1) {
    object_t *value = eval(expr, vm_root_env(vm));

    if (isatty(STDIN_FILENO)) {
      printf(";=> ");
      print(value);
      printf("\n");
    }

    vm_gc(vm);
  }



  yylex_destroy(scanner);

  return 0;
}
