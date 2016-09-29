#include <stdio.h>

#include "types.h"
#include "eval.h"
#include "env.h"

#include "parser.h"
#include "lexer.h"

static object_t *read_internal(FILE *fp, object_t **env) {
  yyscan_t scanner;
  yylex_init(&scanner);
  yyset_in(fp, scanner);

  object_t *expr = NULL;
  yyparse(scanner, &expr);
  yylex_destroy(scanner);

  return expr;
}

object_t *scm_read(object_t *expr, object_t **env) {
  object_t *port = eval(car(cdr(expr)), env);
  if (port != NULL && port->type != PORT)
    return make_error("Provided argument is not port.");

  if (port == NULL) return read_internal(stdin, env);
  return read_internal(port_pointer(port), env);
}

void define_read(object_t *env) {
  def("read", scm_read)
}
