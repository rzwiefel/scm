#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "object.h"

object_t *make_procedure(object_t *env, object_t *args, object_t *body);

object_t *procedure(object_t *o);

object_t *proc_apply(object_t *procedure, object_t *args, object_t **env);

#endif

