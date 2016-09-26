#include "character.h"

object_t *make_char(char *str) {
  object_t *o = make(CHARACTER);
  o->data.c = *(str + 2);
  return o;
}

predicate(character, CHARACTER)

