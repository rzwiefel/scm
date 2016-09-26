#include "pair.h"

object_t *cons(object_t *car, object_t *cdr) {
  object_t *o = make(PAIR);
  pair_t *p = malloc(sizeof(pair_t));
  p->car = car;
  p->cdr = cdr;
  o->data.ptr = p;
  return o;
}

object_t *car(object_t *pair) {
  if (pair == NULL) return NULL;
  if (pair->type == ERROR) return pair;
  if (pair->type != PAIR) {
    return make_error("object not pair");
  }
  return ((pair_t*) pair->data.ptr)->car;
}

object_t *cdr(object_t *pair) {
  if (pair == NULL) return NULL;
  if (pair->type == ERROR) return pair;
  if (pair->type != PAIR) {
    return make_error("object not pair");
  }
  return ((pair_t*) pair->data.ptr)->cdr;
}

void set_car(object_t *pair, object_t *car) {
  ((pair_t*) pair->data.ptr)->car = car;
}

void set_cdr(object_t *pair, object_t *cdr) {
  ((pair_t*) pair->data.ptr)->cdr = cdr;
}

