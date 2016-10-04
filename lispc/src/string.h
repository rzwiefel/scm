#ifndef STRING_H
#define STRING_H

#include "object.h"

typedef struct {
  char *str;
  int length;
} string_t;

object_t *make_string(char *str);
char *string_cstr(object_t *o);
object_t *str_to_error(string_t *str);

object_t *string(object_t *o);

#endif
