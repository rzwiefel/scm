#include <stdio.h>

#include "vm.h"
#include "object.h"

extern vm_t *vm;

object_t *make(type_t type, size_t n) {
  object_t *o = (object_t*) vm_alloc(vm, sizeof(object_t) + n);
  if (o == 0) {
    fprintf(stderr, "out of memory.");
    exit(1);
  }
  o->type = type;
  o->trace = 0;
  o->marked = 0;
  o->padding = 0;
  return o;
}

void free_object(object_t *o) {
  if (o == NULL) return;

  /*switch(o->type) {
    case PAIR: free(o->data.ptr); break;
    case SYMBOL:
    case ERROR:
    case STRING:
               free_str(o->data.ptr); break;
  }*/

  free(o);
}

object_t *object_eq(object_t *a, object_t *b) {
  if (a == b) return &t;
  if (a == NULL || b == NULL) return &f;
  if (a->type != b->type) return &t;

  switch(a->type) {
    case FIXNUM:
      return number_eq(a, b);
    case CHARACTER:
      return character_eq(a, b);
    case SYMBOL:
      return symbol_eq(a, b);
    case PAIR:
      return pair_eq(a, b);
  }

  return &f;
}

