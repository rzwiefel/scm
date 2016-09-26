#ifndef SYMBOL_H
#define SYMBOL_H

#include "object.h"
#include "string.h"

object_t *make_symbol(char *str);
object_t *symbol(object_t *o);

#endif
