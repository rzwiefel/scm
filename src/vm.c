#include "object.h"
#include "vm.h"

typedef struct alloc_t alloc_t;

struct alloc_t {
  object_t *o;
  alloc_t *next;
};

struct vm_t {
  alloc_t *root_alloc;
  void *root_env;
};

static alloc_t *make_alloc(size_t n) {
  alloc_t *alloc = (alloc_t*) malloc(sizeof(alloc_t));
  alloc->o = (object_t*) malloc(n);
  alloc->next = NULL;
  return alloc;
}

static void free_alloc(alloc_t *alloc) {
  if (alloc != NULL) {
    free_object(alloc->o);
    free(alloc);
  }
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
    case MACRO:
    case PROCEDURE:
      mark(o->data.ptr);
      break;
  }
}

static void sweep(alloc_t **root) {
  alloc_t **prev = root, *alloc = *root;
  while (alloc != NULL) {
    if (alloc->o == NULL || alloc->o->marked == 0) {
      free_object(alloc->o);
      *prev = alloc->next;
      alloc_t *tmp = alloc;
      alloc = alloc->next;
      free(tmp);
    } else {
      alloc->o->marked = 0;
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

void **vm_root_env(vm_t *vm) {
  return &vm->root_env;
}

void vm_set_root_env(vm_t *vm, void *env) {
  vm->root_env = env;
}

object_t *vm_alloc(vm_t *vm, size_t n) {
  alloc_t *alloc = make_alloc(n);
  alloc->next = vm->root_alloc;
  vm->root_alloc = alloc;
  return alloc->o;
}

