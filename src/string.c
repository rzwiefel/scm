#include <string.h>

#include "string.h"

object_t *make_string(char *str) {
  size_t n = strlen(str) + 1;
  object_t *o = make(STRING, n);
  memcpy(&object_data(o, char), str, n);
  return o;
}

predicate(string, STRING)

