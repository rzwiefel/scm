#include <string.h>

#include "vec.h"

#define VEC_INITIAL_CAPACITY 64
#define VEC_GROWTH_RATE 1.5

typedef char byte_t;

struct vec_t {
  void *data;
  size_t unit;
  size_t length;
  size_t capacity;
};

vec_t *make_vec(size_t unit) {
  vec_t *vec = (vec_t*) malloc(sizeof(vec_t));

  vec->unit = unit;
  vec->data = malloc(unit * VEC_INITIAL_CAPACITY);
  vec->length = 0;
  vec-> capacity = VEC_INITIAL_CAPACITY;

  return vec;
}

void free_vec(vec_t *vec) {
  free(vec->data);
  free(vec);
}

static void vec_resize(vec_t *vec) {
  vec->capacity = vec->capacity * VEC_GROWTH_RATE;
  vec->data = realloc(vec->data, vec->unit * vec->capacity);
}

void vec_push(vec_t *vec, void *ptr) {
  if (vec->length == vec->capacity) {
    vec_resize(vec);
  }

  memcpy((byte_t*)vec->data + (vec->unit * vec->length), ptr, vec->unit);
  vec->length++;
}


size_t vec_length(vec_t *vec) {
  return vec->length;
}

void *vec_get(vec_t *vec, size_t i) {
  if (i >= vec->length) return NULL;

  return (byte_t*)vec->data + (vec->unit * i);
}
