#include <stdio.h>

#include "colors.h"
#include "print.h"
#include "vector.h"
#include "number.h"

#define INITIAL_CAPACITY 64
#define GROWTH_RATE 1.5

typedef struct {
  size_t length;
  size_t capacity;
  object_t **data;
} vector_t;

typedef char byte_t;
#define vector_data(a) (vector_t*)(((char*) a) + sizeof(object_t))

object_t *make_vector() {
  object_t *o = make(VECTOR, sizeof(vector_t));
  vector_t *vector = vector_data(o);
  vector->length = 0;
  vector->capacity = INITIAL_CAPACITY;
  vector->data = malloc(sizeof(object_t*) * INITIAL_CAPACITY);
  return o;
}

static void vector_resize(vector_t *vector) {
  vector->capacity = vector->capacity * GROWTH_RATE;
  vector->data = realloc(vector->data, sizeof(object_t*) * vector->capacity);
}

object_t *vector_push(object_t *o, object_t *el) {
  vector_t *vector = vector_data(o);

  if (vector->length == vector->capacity) {
    vector_resize(vector);
  }

  vector->data[vector->length++] = el;

  return o;
}

object_t *vector_length(object_t *o) {
  vector_t *vector = vector_data(o);
  return make_fixnum_int(vector->length);
}

/*object_t *vector_get(object_t *o, object_t *i) {
  vector_t *vector = vector_data(o);

  if (i >= vector->length) return NULL;

  return vector->data[i];
}*/

static object_t *vector_get_internal(vector_t *vector, size_t i) {
  if (i >= vector->length) return NULL;
  return vector->data[i];
}

void print_vector(object_t *o) {
  vector_t *vector = vector_data(o);
  printf("[");
  for (size_t i = 0; i < vector->length; i++) {
    print(vector_get_internal(vector, i));
    if (i + 1 < vector->length) {
      printf(" ");
    }
  }
  printf("]");
}
