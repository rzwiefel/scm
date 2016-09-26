#include <string.h>

#include "boolean.h"

object_t t = { BOOLEAN, { .c = 't' } };
object_t f = { BOOLEAN, { .c = 'f' } };

object_t *make_boolean(char *str) {
  if (strcmp(str, "#t") == 0) {
    return &t;
  } else {
    return &f;
  }
}

predicate(boolean, BOOLEAN)

