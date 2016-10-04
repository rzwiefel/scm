#include <string.h>

#include "symbol.h"

object_t *make_symbol(char *str) {
  size_t n = strlen(str) + 1;
  object_t *o = make(SYMBOL, n);
  memcpy(&object_data(o, char), str, n);
  return o;
}

object_t *symbol_eq(object_t *a, object_t *b) {
  if (a == NULL || b == NULL) return &f;
  if (a->type != b->type) return &f;
  if (a->type != SYMBOL && a->type != STRING && a->type != ERROR) return &f;
  if (strcmp(&object_data(a,char), &object_data(b,char)) != 0) return &f;
  return &t;
}

predicate(symbol, SYMBOL)
