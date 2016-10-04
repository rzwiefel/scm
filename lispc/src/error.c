#include <string.h>

#include "error.h"

object_t *make_error (char *str) {
  size_t n = strlen(str) + 1;
  object_t *o = make(ERROR, n);
  memcpy(&object_data(o, char), str, n);
  return o;
}

predicate(error, ERROR)

