#ifndef PAIR_H
#define PAIR_H

#include "object.h"

object_t *cons(object_t *car, object_t *cdr);
object_t *car(object_t *pair);
object_t *cdr(object_t *pair);
void set_car(object_t *pair, object_t *car);
void set_cdr(object_t *pair, object_t *cdr);

#endif
