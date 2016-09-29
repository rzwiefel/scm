#ifndef VECTOR_H
#define VECTOR_H

#include "object.h"

object_t *make_vector();
void free_vector(object_t *vector);

object_t *vector_push(object_t *vector, object_t *el);
object_t *vector_length(object_t *vector);
object_t *vector_get(object_t *vector, object_t *i);

void print_vector(object_t *vector);

#endif
