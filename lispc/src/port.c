#include <stdio.h>

#include "types.h"
#include "colors.h"
#include "env.h"
#include "eval.h"

object_t eof = { ENDOFINPUT };

typedef struct {
  object_t *path;
  FILE *fp;
} port_t;

object_t *make_port() {
  return make(PORT, sizeof(port_t));
}

FILE *port_pointer(object_t *port) {
  return object_data(port, port_t).fp;
}

void print_port(object_t *port) {
  printf(__yellow("#<port:%s>"), string_cstr(object_data(port, port_t).path));
}

defn(eval_open) {
  object_t *str = eval(car(cdr(expr)), env);
  if (false(string(str)))
    return make_error("First argument is not a string.");

  char *path = string_cstr(str);
  FILE *fp = fopen(path, "r");

  if (fp == NULL) {
    return make_error("Can't open input file.");
  }

  object_t *port = make_port();
  object_data(port, port_t).path = str;
  object_data(port, port_t).fp = fp;
  return port;
}

void define_port(object_t *env) {
  def("open", eval_open)
}

