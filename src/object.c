#include <string.h>
#include <stdio.h>

#include "vm.h"
#include "object.h"

char *type_to_str[] = {
  NULL,
  "LBRACE",
  "RBRACE",
  "FIXNUM",
  "FLONUM",
  "STRING",
  "CHARACTER",
  "SYMBOL",
  "BOOLEAN",
  "DOT",
  "PAIR",
  "VECTOR",
  "QUOTE",
  "PRIMITIVE",
  "PROCEDURE",
  "IGNORE",
  "ERROR",
  "ENDOFINPUT"
};


object_t t = { BOOLEAN, { .c = 't' } };
object_t f = { BOOLEAN, { .c = 'f' } };


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

object_t *make_fixnum(char *str) {
  object_t *o = make(FIXNUM);
  o->data.fix = atoi(str);
  return o;
}

object_t *make_fixnum_int(int fix) {
  object_t *o = make(FIXNUM);
  o->data.fix = fix;
  return o;
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

object_t *make_string(char *str) {
  object_t *o = make(STRING);
  o->data.ptr = make_str(str);
  return o;
}

object_t *make_char(char *str) {
  object_t *o = make(CHARACTER);
  o->data.c = *(str + 2);
  return o;
}

object_t *make_symbol(char *str) {
  object_t *o = make(SYMBOL);
  o->data.ptr = make_str(str);
  return o;
}


object_t *make_boolean(char *str) {
  if (strcmp(str, "#t") == 0) {
    return &t;
  } else {
    return &f;
  }
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

object_t *cons(object_t *car, object_t *cdr) {
  object_t *o = make(PAIR);
  pair_t *p = malloc(sizeof(pair_t));
  p->car = car;
  p->cdr = cdr;
  o->data.ptr = p;
  return o;
}

object_t *car(object_t *pair) {
  if (pair == NULL) return NULL;
  if (pair->type == ERROR) return pair;
  if (pair->type != PAIR) {
    return make_error("object not pair");
  }
  return ((pair_t*) pair->data.ptr)->car;
}

object_t *cdr(object_t *pair) {
  if (pair == NULL) return NULL;
  if (pair->type == ERROR) return pair;
  if (pair->type != PAIR) {
    return make_error("object not pair");
  }
  return ((pair_t*) pair->data.ptr)->cdr;
}

void set_car(object_t *pair, object_t *car) {
  ((pair_t*) pair->data.ptr)->car = car;
}

void set_cdr(object_t *pair, object_t *cdr) {
  ((pair_t*) pair->data.ptr)->cdr = cdr;
}

object_t *str_to_error(string_t *str) {
  object_t *o = make(ERROR);
  o->data.ptr = str;
  return o;
}

object_t *make_error (char *str) {
  object_t *o = make(ERROR);
  o->data.ptr = make_str(str);
  return o;
}

object_t *number(object_t *o) {
  if (o == NULL || (o->type != FIXNUM && o->type != FLONUM)) {
    return &f;
  }
  return &t;
}

object_t *null(object_t *o) {
  if (o == NULL) return &t;
  return &f;
}

predicate(boolean, BOOLEAN)
predicate(fixnum, FIXNUM)
predicate(flonum, FLONUM)
predicate(pair, PAIR)
predicate(character, CHARACTER)
predicate(string, STRING)
predicate(symbol, SYMBOL)
predicate(variable, SYMBOL)
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

