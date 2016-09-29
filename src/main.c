#include "vm.h"
#include "types.h"
#include "print.h"
#include "eval.h"
#include "read.h"

#include "parser.h"
#include "lexer.h"

vm_t *vm = NULL;

int main (int argc, char** argv) {
  yyscan_t scanner;

  yylex_init(&scanner);
  yyset_in(stdin, scanner);

  vm = make_vm();

  object_t *env = make_frame(NULL);
  init(env);
  define_vector(env);
  define_port(env);
  define_read(env);
  vm_set_root_env(vm, env);
  object_t *expr = NULL;

  if (isatty(STDIN_FILENO)) {
    printf(">> ");
  }

  while (yyparse(scanner, &expr) == 0 && expr != &eof) {
    object_t *value = eval(expr, vm_root_env(vm));

    if (isatty(STDIN_FILENO)) {
      print(value);
      printf("\n>> ");
    }

    vm_gc(vm);
  }

  yylex_destroy(scanner);

  return 0;
}
