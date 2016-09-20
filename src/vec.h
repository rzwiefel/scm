#ifndef VEC_H
#define VEC_H

#include <stdlib.h>

typedef struct vec_t vec_t;

vec_t *make_vec();
void free_vec(vec_t *vec);

void vec_push(vec_t *vec, void *ptr);
size_t vec_length(vec_t *vec);
void *vec_get(vec_t *vec, size_t i);

#endif
