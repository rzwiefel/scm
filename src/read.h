#ifndef READ_H
#define READ_H

#include "object.h"

object_t *scm_read(object_t *expr, object_t **env);

void define_read(object_t *env);

#endif
