#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "object.h"

#define true(o) ((o) == &t)
#define false(o) ((o) == &f)

object_t *make_boolean(char *str);

object_t *boolean(object_t *o);

#endif
