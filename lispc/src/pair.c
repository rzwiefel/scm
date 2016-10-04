#include "pair.h"
#include "error.h"
#include "boolean.h"
#include "eval.h"

typedef struct {
  object_t *car;
  object_t *cdr;
} pair_t;

object_t *cons(object_t *car, object_t *cdr) {
  object_t *o = make(PAIR, sizeof(pair_t));
  object_data(o, pair_t).car = car;
  object_data(o, pair_t).cdr = cdr;
  return o;
}

object_t *car(object_t *pair) {
  if (pair == NULL) return NULL;
  if (pair->type == ERROR) return pair;
  if (pair->type != PAIR) {
    return make_error("object not pair");
  }
  return object_data(pair, pair_t).car;
}

object_t *cdr(object_t *pair) {
  if (pair == NULL) return NULL;
  if (pair->type == ERROR) return pair;
  if (pair->type != PAIR) {
    return make_error("object not pair");
  }
  return object_data(pair, pair_t).cdr;
}

void set_car(object_t *pair, object_t *car) {
  object_data(pair, pair_t).car = car;
}

void set_cdr(object_t *pair, object_t *cdr) {
  object_data(pair, pair_t).cdr = cdr;
}

object_t *null(object_t *o) {
  if (o == NULL) return &t;
  return &f;
}

predicate(pair, PAIR)

object_t *pair_eq(object_t *a, object_t *b) {
  return false(object_eq(car(a), car(b))) ? &f : object_eq(cdr(a), cdr(b));
}

