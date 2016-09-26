#include <string.h>

#include "symbol.h"

static void *make_str(char *str) {
  string_t *s = (string_t*) malloc(sizeof(string_t));

  s->str = strdup(str);
  s->length = strlen(s->str);

  return s;
}

object_t *make_symbol(char *str) {
  object_t *o = make(SYMBOL);
  o->data.ptr = make_str(str);
  return o;
}

predicate(symbol, SYMBOL)
