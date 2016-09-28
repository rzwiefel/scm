#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdlib.h>

typedef enum {
  LBRACE = 1,
  RBRACE,
  FIXNUM,
  FLONUM,
  STRING,
  CHARACTER,
  SYMBOL,
  TRUE,
  FALSE,
  DOT,
  PAIR,
  VECTOR,
  QUOTE,
  PRIMITIVE,
  PROCEDURE,
  MACRO,
  IGNORE,
  ERROR,
  ENDOFINPUT
} type_t;

typedef struct object_t object_t;
typedef struct object_t *(*primitive)(struct object_t *expr, struct object_t **env);

struct object_t {
  unsigned char type;
  unsigned char trace;
  unsigned char marked;
  unsigned char padding;
  union {
    void *ptr;
    char c;
    int fix;
    float flo;
    primitive fn;
  } data;
};

extern object_t t;
extern object_t f;

object_t *make(type_t type);
void free_object(object_t *o);

#define predicate(fun,TYPE) \
  object_t *fun(object_t *o) { \
    if (o == NULL || o->type != TYPE) { \
      return &f; } \
    return &t; }

#endif
