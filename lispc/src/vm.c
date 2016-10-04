#include "vm.h"

typedef struct alloc_t alloc_t;

struct alloc_t {
  alloc_t *next;
};

#define alloc_data(a) (object_t*)(((char*) a) + sizeof(alloc_t))

struct vm_t {
  alloc_t *root_alloc;
  object_t *root_env;
};

static alloc_t *make_alloc(size_t n) {
  alloc_t *alloc = (alloc_t*) malloc(sizeof(alloc_t) + n);
  alloc->next = NULL;
  return alloc;
}

vm_t *make_vm() {
  vm_t *vm = malloc(sizeof(vm_t));
  vm->root_alloc = NULL;
  vm->root_env = NULL;
  return vm;
}

static void mark(object_t *o) {
  if (o == NULL || o->marked) return;

  o->marked = 1;

  switch (o->type) {
    case PAIR:
      mark(car(o));
      mark(cdr(o));
      break;
    case ERROR:
    case PROCEDURE:
      //mark(object_data(o, object_t));
      break;
  }
}

static void sweep(alloc_t **root) {
  alloc_t **prev = root, *alloc = *root;
  while (alloc != NULL) {
    object_t *o = alloc_data(alloc);
    if (o == NULL || o->marked == 0) {
      *prev = alloc->next;
      alloc_t *tmp = alloc;
      alloc = alloc->next;
      free(tmp);
    } else {
      o->marked = 0;
      if (alloc->next != NULL) {
        prev = &alloc->next;
      }
      alloc = alloc->next;
    }
  }
}

void vm_gc(vm_t *vm) {
  if (vm != NULL) {
    mark(vm->root_env);
    sweep(&vm->root_alloc);
  }
}

void free_vm(vm_t *vm) {
  if (vm != NULL) {
    sweep(&vm->root_alloc);
    free(vm);
  }
}

object_t **vm_root_env(vm_t *vm) {
  return &vm->root_env;
}

void vm_set_root_env(vm_t *vm, object_t *env) {
  vm->root_env = env;
}

object_t *vm_alloc(vm_t *vm, size_t n) {
  alloc_t *alloc = make_alloc(n);
  alloc->next = vm->root_alloc;
  return alloc_data(alloc);
}

