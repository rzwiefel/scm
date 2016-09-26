#include "procedure.h"
#include "pair.h"

object_t *make_procedure(object_t *env, object_t *params, object_t *body) {
  object_t *o = make(PROCEDURE);
  o->data.ptr = cons(env, cons(params, body));
  return o;
}

object_t *make_primitive(primitive fn) {
  object_t *o = make(PRIMITIVE);
  o->data.fn = fn;
  return o;
}

predicate(procedure, PROCEDURE)

