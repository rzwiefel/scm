#include <stdio.h>

#include "print.h"
#include "colors.h"

static char *get_str(object_t *o) {
  return ((string_t*) o->data.ptr)->str;
}

static void print_object(object_t *o);

static void print_pair(object_t *o) {
  printf("(");

  object_t *temp = o, *next;
  while (temp != NULL) {
    print_object(car(temp));
    next = cdr(temp);
    if (next == NULL || next->type != PAIR) break;
    printf(" ");
    temp = next;
  }

  if (temp != NULL) {
    if (next != NULL) {
      printf(" . ");
      print_object(next);
    }
  }

  printf(")");
}

static void print_object(object_t *o) {
  if (o == NULL) {
    printf(__green("nil"));
  } else {
    switch (o->type) {
      case FIXNUM:
        printf(__green("%d"), o->data.fix);
        break;
      case FLONUM:
        printf(__green("%f"), o->data.flo);
        break;
      case CHARACTER:
        printf(__yellow("#\\%c"), o->data.c);
        break;
      case STRING:
        printf(__yellow("%s"), get_str(o));
        break;
      case BOOLEAN:
        printf(__green("#%c"), o->data.c);
        break;
      case PAIR:
        print_pair(o);
        break;
      case SYMBOL:
        printf(__blue("%s"), get_str(o));
        break;
      case PROCEDURE:
      case PRIMITIVE:
        printf(__purple("#<PROCEDURE@%p>"), o);
        break;
      case ERROR:
        printf(__red("%s"), get_str(o));
        break;
      default:
        printf("cannot write unknown type");
    }
  }
}

void print(object_t *o) {
  print_object(o);
}

