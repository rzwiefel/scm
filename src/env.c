#include "types.h"

object_t *make_frame(object_t *parent) {
  return cons(NULL, parent);
}

object_t *define(object_t *frame, object_t *sym, object_t *val) {
  set_car(frame, cons(cons(sym, val), car(frame)));
  return frame;
}

object_t *frame_search(object_t *frame, object_t *sym) {
  if (frame == NULL || sym == NULL) return make_error("cannot find symbol");
  object_t *pair = car(frame);
  if (true(symbol_eq(car(pair), sym))) return cdr(pair);
  return frame_search(cdr(frame), sym);
}

object_t *lookup(object_t *env, object_t *sym) {
  if (sym == NULL) return NULL;
  if (env == NULL) return make_error("cannot find symbol");
  object_t *find = frame_search(car(env), sym);
  if (find == NULL || false(error(find))) return find;
  return lookup(cdr(env), sym);
}

