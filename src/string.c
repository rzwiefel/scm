#include <string.h>

#include "string.h"

static void *make_str(char *str) {
  string_t *s = (string_t*) malloc(sizeof(string_t));

  s->str = strdup(str);
  s->length = strlen(s->str);

  return s;
}

object_t *str_to_error(string_t *str) {
  object_t *o = make(ERROR);
  o->data.ptr = make_str(str->str);
  return o;
}

object_t *make_string(char *str) {
  object_t *o = make(STRING);
  o->data.ptr = make_str(str);
  return o;
}

predicate(string, STRING)

