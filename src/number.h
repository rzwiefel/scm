#ifndef NUMBER_H
#define NUMBER_H

#include "object.h"

object_t *make_fixnum(char *str);
object_t *make_fixnum_int(int fix);
object_t *make_flonum(char *str);
object_t *make_flonum_float(float flo);

object_t *fixnum(object_t *o);
object_t *flonum(object_t *o);
object_t *number(object_t *o);

#endif
