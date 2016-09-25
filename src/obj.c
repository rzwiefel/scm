#include "obj.h"

obj_t *obj_eval(obj_t *expr, obj_t **env) {
  fn_eval eval = expr->vtable->eval;
  if (eval) return eval(expr, env); 
  // fallback to self-evaluation
  return expr;
}

int obj_equal(obj_t *a, obj_t *b) {
  fn_equal equal = a->vtable->equal;
  if (equal) return equal(a, b);
  // fallback to reference equality
  return a == b;
}

void obj_write(obj_t *o) {
  o->vtable->write(o);
}

void obj_mark(obj_t *o) {
  o->vtable->mark(o);
}

void obj_free(obj_t *o) {
  o->vtable->free(o);
}
