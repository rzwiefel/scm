#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "object.h"

typedef struct object_t *(*primitive)(object_t *expr, object_t **env);

object_t *make_primitive(primitive fn);

object_t *prim_apply(object_t *prim, object_t *args, object_t **env);

#endif
