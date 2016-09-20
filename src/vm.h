#ifndef VM_H
#define VM_H

#include <stdlib.h>

#include "object.h"

typedef struct vm_t vm_t;

vm_t *make_vm();
void free_vm(vm_t *vm);

object_t *vm_alloc(vm_t *vm, size_t s);

void vm_set_root_env(vm_t *vm, void *env);
void **vm_root_env(vm_t *vm);

void vm_gc(vm_t *vm);

#endif
