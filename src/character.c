#include "character.h"

object_t *make_char(char *str) {
  object_t *o = make(CHARACTER, sizeof(char));
  object_data(o, char) = *(str + 2);
  return o;
}

predicate(character, CHARACTER)

object_t *character_eq(object_t *a, object_t *b) {
  return &f;
}
