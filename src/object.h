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
  BOOLEAN,
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
  char type;
  union {
    void *ptr;
    char c;
    int fix;
    float flo;
    primitive fn;
  } data;
  unsigned char trace;
  unsigned char marked;
};

extern object_t t;
extern object_t f;

object_t *make(type_t type);

object_t *make_char(char *str);
object_t *make_error(char *str);
object_t *make_primitive(primitive fn);
object_t *make_procedure(object_t *env, object_t *args, object_t *body);

void free_object(object_t *o);

#define predicate(fun,TYPE) \
  object_t *fun(object_t *o) { \
    if (o == NULL || o->type != TYPE) { \
      return &f; } \
    return &t; }

object_t *character(object_t *o);
object_t *procedure(object_t *o);
object_t *error(object_t *o);

object_t *symbol_eq(object_t *a, object_t *b);

#endif
