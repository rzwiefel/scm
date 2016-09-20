#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdlib.h>

extern char *type_to_str[];

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

typedef struct {
  object_t *car;
  object_t *cdr;
} pair_t;

typedef struct {
  char *str;
  int length;
} string_t;

extern object_t t;
extern object_t f;

#define true(o) ((o) == &t)
#define false(o) ((o) == &f)

object_t *make(type_t type);

object_t *make_fixnum(char *str);
object_t *make_fixnum_int(int fix);
object_t *make_flonum(char *str);
object_t *make_flonum_float(float flo);
object_t *make_string(char *str);
object_t *make_char(char *str);
object_t *make_symbol(char *str);
object_t *make_boolean(char *str);
object_t *make_error(char *str);
object_t *make_primitive(primitive fn);
object_t *make_procedure(object_t *env, object_t *args, object_t *body);

void free_object(object_t *o);

object_t *str_to_error(string_t *str);

object_t *cons(object_t *car, object_t *cdr);
object_t *car(object_t *pair);
object_t *cdr(object_t *pair);
void set_car(object_t *pair, object_t *car);
void set_cdr(object_t *pair, object_t *cdr);

#define predicate(fun,TYPE) \
  object_t *fun(object_t *o) { \
    if (o == NULL || o->type != TYPE) { \
      return &f; } \
    return &t; }

object_t *null(object_t *o);
object_t *boolean(object_t *o);
object_t *fixnum(object_t *o);
object_t *flonum(object_t *o);
object_t *pair(object_t *o);
object_t *number(object_t *o);
object_t *symbol(object_t *o);
object_t *variable(object_t *o);
object_t *character(object_t *o);
object_t *string(object_t *o);
object_t *procedure(object_t *o);
object_t *error(object_t *o);

object_t *symbol_eq(object_t *a, object_t *b);

#endif
