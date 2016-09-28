#ifndef PAIR_H
#define PAIR_H

#include "object.h"

object_t *cons(object_t *car, object_t *cdr);
object_t *car(object_t *pair);
object_t *cdr(object_t *pair);
void set_car(object_t *pair, object_t *car);
void set_cdr(object_t *pair, object_t *cdr);

object_t *null(object_t *o);
object_t *pair(object_t *o);

object_t *pair_eq(object_t *a, object_t *b);

#endif
