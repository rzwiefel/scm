#include <string.h>

#include "boolean.h"

object_t t = { TRUE };
object_t f = { FALSE };

object_t *make_boolean(char *str) {
  if (strcmp(str, "#t") == 0) {
    return &t;
  } else {
    return &f;
  }
}

object_t *boolean(object_t *o) {
  if (o == &t || o == &f) return &t;
  return &f;
}

