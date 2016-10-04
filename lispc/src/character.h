#ifndef CHARACTER_H
#define CHARACTER_H

#include "object.h"

object_t *make_char(char *str);

object_t *character(object_t *o);
object_t *character_eq(object_t *a, object_t *b);

#endif
