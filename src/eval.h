#ifndef EVAL_H
#define EVAL_H

#include "types.h"
#include "env.h"

object_t *init();
object_t *eval(object_t *expr, object_t **env);

#endif
