#include "primitive.h"

object_t *make_primitive(primitive fn) {
  object_t *o = make(PRIMITIVE, sizeof(primitive));
  object_data(o, primitive) = fn;
  return o;
}

object_t *prim_apply(object_t *prim, object_t *args, object_t **env) {
  return (object_data(prim, primitive))(args, env);
}
