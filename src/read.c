#include <stdio.h>

#include "read.h"

static object_t *read_list(token_stream_t *ts) {
  token_t *t = token_stream_peek(ts); 

  if (t == NULL) {
    return make_error("got NULL token");
  }

  type_t type = token_type(t);

  if (type == ENDOFINPUT) {
    return make_error("unexpected end of input");
  }

  if (type == DOT) {
    token_stream_read(ts);
    object_t *o = reader(ts);
    t = token_stream_read(ts);
    if (t == NULL || token_type(t) != RBRACE) {
      return make_error("missing ) for pair");
    }
    return o;
  }

  if (type != RBRACE) {
    object_t *o = reader(ts);
    if (type == ERROR) return o;
    return cons(o, read_list(ts));
  }

  token_stream_read(ts);
  return NULL;
}

object_t *read_object(token_t *t) {
  char *str = token_str(t);
  switch (token_type(t)) {
    case FIXNUM: return make_fixnum(str);
    case FLONUM: return make_flonum(str);
    case STRING: return make_string(str);
    case CHARACTER: return make_char(str);
    case SYMBOL: return make_symbol(str);
    case TRUE:
    case FALSE: return make_boolean(str);
    default: return NULL;
  }
}

object_t *reader(token_stream_t *ts) {
  token_t *t = token_stream_read(ts);

  if (t == NULL) {
    return make_error("got NULL token");
  }

  type_t type = token_type(t);

  if (type == QUOTE) {
    return cons(make_symbol("quote"), cons(reader(ts), NULL));
  }

  if (type == ENDOFINPUT) {
    return make_error("unexpected end of input");
  }

  if (type == RBRACE) {
    return make_error("unbalanced )");
  }

  if (type == LBRACE) {
    return read_list(ts);
  }

  return read_object(t);
}
