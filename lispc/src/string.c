#include <string.h>

#include "string.h"

object_t *make_string(char *str) {
  size_t n = strlen(str) + 1 - 2;
  object_t *o = make(STRING, n);
  memcpy(&object_data(o, char), str + 1, n);
  *(&object_data(o, char) + n - 1) = '\0';
  return o;
}

char *string_cstr(object_t *o) {
  return &object_data(o, char);
}

predicate(string, STRING)

