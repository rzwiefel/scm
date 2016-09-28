#include "number.h"
#include "error.h"

object_t *make_fixnum(char *str) {
  object_t *o = make(FIXNUM, sizeof(int));
  object_data(o, int) = atoi(str);
  return o;
}

object_t *make_fixnum_int(int fix) {
  object_t *o = make(FIXNUM, sizeof(int));
  object_data(o, int) = fix;
  return o;
}

object_t *make_flonum(char *str) {
  object_t *o = make(FLONUM, sizeof(float));
  object_data(o, float) = atof(str);
  return o;
}

object_t *make_flonum_float(float flo) {
  object_t *o = make(FLONUM, sizeof(float));
  object_data(o, float) = flo;
  return o;
}

object_t *number(object_t *o) {
  if (o == NULL || (o->type != FIXNUM && o->type != FLONUM)) {
    return &f;
  }
  return &t;
}

object_t *plus(object_t *a, object_t *b) {
  if (a == NULL) return plus(make_fixnum_int(0), b);
  if (b == NULL) return plus(a, make_fixnum_int(0));

  if (!true(number(a)) || !true(number(b)))
    return make_error("can't perform arithmetic on non numeric values");

  if (a->type == FLONUM || b->type == FLONUM) {
    if (a->type != FLONUM) return make_flonum_float(object_data(a, int) + object_data(b, float));
    if (b->type != FLONUM) return make_flonum_float(object_data(a, float) + object_data(b, int));
    return make_flonum_float(object_data(a, float) + object_data(b, float));
  }

  return make_fixnum_int(object_data(a, int) + object_data(b, int));
}

predicate(fixnum, FIXNUM)
predicate(flonum, FLONUM)

object_t *number_eq(object_t *a, object_t *b) {
  if (a == NULL || b == NULL) return &f;
  if (a->type != FIXNUM || b->type != FIXNUM) return &f;
  return (object_data(a, int) == object_data(b, int)) ? &t : &f;
}

