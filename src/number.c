#include "obj.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct number_t number_t;

struct number_t { iobj_t *vtable; long value; };

static int number_equal(obj_t *a, obj_t *b) {
  return 1;
}

static void number_write(obj_t *o) {
  number_t *num = (number_t*) o;
  printf("%ld", num->value);
}

static void number_mark(obj_t *o) {
}

static void number_free(obj_t *o) {
  free(o);
}

static obj_t *make_number(long value) {
  static iobj_t vtable = {
    0,
    number_equal,
    number_write,
    number_mark,
    number_free
  };

  number_t *num = malloc(sizeof(number_t));
  num->vtable = &vtable;
  num->value = value;

  return (obj_t*) num;
}

defn(add) {
  return make_number(0);
}

defn(subtract) {
  return make_number(0);
}

defn(multiply) {
  return make_number(0);
}

defn(divide) {
  return make_number(0);
}

defn(mod) {
  return make_number(0);
}

