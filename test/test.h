#ifndef TEST_H
#define TEST_H

#include <string.h>

#define GDOT "\033[0;32m*\033[0;0m" // green dot
#define RDOT "\033[0;31m*\033[0;0m" // red dot

typedef struct {
  int status;
  int line;
  char description [80];
} result;

typedef struct {
  int count;
  int line;
  char file[80];
  char title[80];
  result asserts[1024];
} test;

// define the begging of a test
#define begin(_title) { test _t; _t.line = __LINE__; \
  strcpy(_t.title, _title); \
  _t.count = 0; \
  strcpy(_t.file, __FILE__);


// end of begin (don't remove '}', not typo)
#define end() reporter(&_t); }

// custom assert macro
#define assert(_status, _description) { result *res = &_t.asserts[_t.count]; res->line = __LINE__; \
  _t.count++; \
  strcpy(res->description, _description); \
  res->status = _status; }

void reporter(test *t) {

  int i;

  // print header
  printf("\033[0;34m%s\033[0;0m (%d)\n>> ", t->title, t->count);

  for (i = 0; i < t->count; i++) {
    if (t->asserts[i].status == 1) {
      printf(GDOT);
    } else {
      printf(RDOT);
    }
  }

  printf("\n");

  for (i = 0; i < t->count; i++) {
    result *res = &t->asserts[i];
    if (res->status == 0) {
      printf("\033[0;31m%d:\033[0;0m %s\n", res->line, res->description);
    }
  }

}

#endif
