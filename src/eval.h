#ifndef EVAL_H
#define EVAL_H

#include "types.h"
#include "env.h"

void init(object_t *env);
object_t *eval(object_t *expr, object_t **env);

#endif
