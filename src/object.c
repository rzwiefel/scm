#include <string.h>
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

static void *make_str(char *str) {
  string_t *s = (string_t*) malloc(sizeof(string_t));

  s->str = strdup(str);
  s->length = strlen(s->str);

  return s;
}

static void free_str(void *ptr) {
  string_t *s = (string_t*) ptr;
  free(s->str);
  free(s);
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

object_t *make_char(char *str) {
  object_t *o = make(CHARACTER);
  o->data.c = *(str + 2);
  return o;
}

object_t *make_primitive(primitive fn) {
  object_t *o = make(PRIMITIVE);
  o->data.fn = fn;
  return o;
}

object_t *make_procedure(object_t *env, object_t *params, object_t *body) {
  object_t *o = make(PROCEDURE);
  o->data.ptr = cons(env, cons(params, body));
  return o;
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

object_t *make_error (char *str) {
  object_t *o = make(ERROR);
  o->data.ptr = make_str(str);
  return o;
}

predicate(character, CHARACTER)
predicate(procedure, PROCEDURE)
predicate(error, ERROR)

object_t *symbol_eq(object_t *a, object_t *b) {
  if (a == NULL || b == NULL) return &f;
  if (a->type != b->type) return &f;
  if (a->type != SYMBOL && a->type != STRING && a->type != ERROR) return &f;
  string_t* str_a = (string_t*) a->data.ptr;
  string_t* str_b = (string_t*) b->data.ptr;
  if (str_a->length != str_b->length) return &f;
  if (strcmp(str_a->str, str_b->str) != 0) return &f;
  return &t;
}

