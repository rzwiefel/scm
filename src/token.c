#include <string.h>

#include "vec.h"
#include "token.h"

struct token_t {
  type_t type;
  char *str;
};

struct token_stream_t {
  vec_t *tokens;
  size_t i;
  int balanced;
};

token_t *make_token(type_t type, char *str) {
  token_t *t = (token_t*) malloc(sizeof(token_t));
  t->type = type;
  if (str != NULL) {
    t->str = strdup(str);
  }
  return t;
}

void free_token(token_t *t) {
  free(t->str);
  free(t);
}

type_t token_type(token_t *t) {
  return t->type;
}

char *token_str(token_t *t) {
  return t->str;
}

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

extern token_t *yylex(void);

token_stream_t *make_token_stream(token_stream_t *ts, char *str) {

  if (ts == NULL) {
    ts = (token_stream_t*) malloc(sizeof(token_stream_t));
    ts->tokens = make_vec(sizeof(token_t));
    ts->i = 0;
    ts->balanced = 0;
  }

  YY_BUFFER_STATE buffer = yy_scan_string(str);

  while (1) {
    token_t *ret = yylex();
    type_t t = token_type(ret);

    if (ret == NULL || t == ENDOFINPUT) {
      if (ret != NULL) free_token(ret);
      break;
    }

    if (t == LBRACE) ts->balanced++;
    if (t == RBRACE) ts->balanced--;

    if (t != IGNORE) {
      vec_push(ts->tokens, ret);
      free(ret);
    } else {
      free_token(ret);
    }
  }

  yy_delete_buffer(buffer);

  return ts;
}

void free_token_strem(token_stream_t *ts) {
  if (ts != NULL) {
    vec_t *tokens = ts->tokens;
    size_t len = vec_length(tokens);

    for (size_t i = 0; i < len; i++) {
      token_t *t = (token_t*) vec_get(tokens, i);
      free(t->str);
    }

    free_vec(tokens);
    free(ts);
  }
}

int token_stream_balanced(token_stream_t *ts) {
  return ts->balanced == 0;
}

token_t *token_stream_read(token_stream_t *ts) {
  return vec_get(ts->tokens, ts->i++);
}

token_t *token_stream_peek(token_stream_t *ts) {
  return vec_get(ts->tokens, ts->i);
}
