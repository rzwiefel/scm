#include <string.h>

#include "error.h"

static void *make_str(char *str) {
  string_t *s = (string_t*) malloc(sizeof(string_t));

  s->str = strdup(str);
  s->length = strlen(s->str);

  return s;
}

object_t *make_error (char *str) {
  object_t *o = make(ERROR);
  o->data.ptr = make_str(str);
  return o;
}

predicate(error, ERROR)

