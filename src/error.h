#ifndef ERROR_H
#define ERROR_H

#include "object.h"
#include "string.h"

object_t *make_error(char *str);

object_t *error(object_t *o);

#endif
