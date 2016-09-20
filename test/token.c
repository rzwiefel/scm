#include <stdio.h>
#include <string.h>

#include "test.h"

#include "../src/token.h"

static int token_stream_count(token_stream_t *ts) {
  int count = 0;
  while (token_stream_read(ts) != NULL) {
    count++;
  }
  return count;
}

static void type_match(type_t type, char *str) {
  begin("type_match");
   token_stream_t *ts = make_token_stream(str);
   assert(ts != NULL, "should create token stream");
   token_t *t =  token_stream_read(ts);
   assert(t != NULL, "should have at least one token");
   assert(token_type(t) == type, "should recognize type");
   free_token_strem(ts);
  end();
}

void test_make_token_stream() {

  begin("make_token_stream()");
   token_stream_t *ts = make_token_stream("");
   assert(ts != NULL, "can create ts from empty string");
   free_token_strem(ts);
  end();

  type_match(DOT, ".");

  type_match(LBRACE, "(");
  type_match(RBRACE, ")");

  type_match(QUOTE, "'");

  type_match(SYMBOL, "*");
  type_match(SYMBOL, "+");
  type_match(SYMBOL, "cons");
  type_match(SYMBOL, "eq?");
  type_match(SYMBOL, "pair?");
  type_match(SYMBOL, "make-vector");
  type_match(SYMBOL, "vector->pair");

  type_match(FLONUM, "0.0");
  type_match(FLONUM, "3.141592654");
  type_match(FLONUM, "2.718281828");

  type_match(FIXNUM, "0");
  type_match(FIXNUM, "1");
  type_match(FIXNUM, "10");
  type_match(FIXNUM, "100");
  type_match(FIXNUM, "1234567890");

  type_match(STRING, "\"hello, world!\"");
  type_match(STRING, "\"hello\"");

  type_match(CHARACTER, "#\\c");
  type_match(CHARACTER, "#\\space");
  type_match(CHARACTER, "#\\newline");

  begin("make_token_stream()");
   token_stream_t *ts = make_token_stream("(+ (+ 1 2 3) 2 3)");
   assert(token_stream_count(ts) == 11, "correct number of tokens");
   free_token_strem(ts);
  end();

}
