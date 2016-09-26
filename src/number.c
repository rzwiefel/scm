#include "number.h"

object_t *make_fixnum(char *str) {
  object_t *o = make(FIXNUM);
  o->data.fix = atoi(str);
  return o;
}

object_t *make_fixnum_int(int fix) {
  object_t *o = make(FIXNUM);
  o->data.fix = fix;
  return o;
}

object_t *make_flonum(char *str) {
  object_t *o = make(FLONUM);
  o->data.flo = atof(str);
  return o;
}

object_t *make_flonum_float(float flo) {
  object_t *o = make(FLONUM);
  o->data.flo = flo;
  return o;
}



object_t *number(object_t *o) {
  if (o == NULL || (o->type != FIXNUM && o->type != FLONUM)) {
    return &f;
  }
  return &t;
}

predicate(fixnum, FIXNUM)
predicate(flonum, FLONUM)

