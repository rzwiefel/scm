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

object_t *symbol_eq(object_t *a, object_t *b) {
  if (a == NULL || b == NULL) return &f;
  if (a->type != b->type) return &f;
  if (a->type != SYMBOL && a->type != STRING && a->type != ERROR) return &f;
  string_t* str_a = (string_t*) a->data.ptr;
  string_t* str_b = (string_t*) b->data.ptr;
  if (str_a->length != str_b->length) return &f;
  if (strcmp(str_a->str, str_b->str) != 0) return &f;
  return &t;
}

predicate(symbol, SYMBOL)
