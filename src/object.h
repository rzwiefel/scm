#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdlib.h>

typedef enum {
  FIXNUM = 1,
  FLONUM,
  STRING,
  CHARACTER,
  SYMBOL,
  TRUE,
  FALSE,
  PAIR,
  VECTOR,
  QUOTE,
  PRIMITIVE,
  PROCEDURE,
  ERROR,
  PORT,
  ENDOFINPUT
} type_t;

typedef struct object_t object_t;

extern object_t t;
extern object_t f;

#define true(o) ((o) == &t)
#define false(o) ((o) == &f)

struct object_t {
  unsigned char type;
  unsigned char trace;
  unsigned char marked;
  unsigned char padding;
};

object_t *make(type_t type, size_t n);
object_t *object_eq(object_t *a, object_t *b);
void free_object(object_t *o);

#define object_data(o,type) (*((type*)(((char*)o) + sizeof(object_t))))

#define predicate(fun,TYPE) \
  object_t *fun(object_t *o) { \
    if (o == NULL || o->type != TYPE) { \
      return &f; } \
    return &t; }

#endif
