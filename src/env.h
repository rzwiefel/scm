#ifndef ENV_H
#define ENV_H

#include "object.h"

extern object_t *globals;

object_t *make_frame(object_t *parent);

object_t *define(object_t *env, object_t *sym, object_t *val);
object_t *lookup(object_t *env, object_t *sym);

#endif
