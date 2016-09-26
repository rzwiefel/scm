#include <stdio.h>

#include "vm.h"
#include "object.h"

extern vm_t *vm;

object_t *make(type_t type) {
  object_t *o = (object_t*) vm_alloc(vm, sizeof(object_t));
  if (o == 0) {
    fprintf(stderr, "out of memory.");
    exit(1);
  }
  o->type = type;
  o->trace = 0;
  o->marked = 0;
  return o;
}

static void free_str(void *ptr) {
  string_t *s = (string_t*) ptr;
  free(s->str);
  free(s);
}

void free_object(object_t *o) {
  if (o == NULL) return;

  switch(o->type) {
    case PAIR: free(o->data.ptr); break;
    case SYMBOL:
    case ERROR:
    case STRING:
               free_str(o->data.ptr); break;
  }

  free(o);
}

