#ifndef TOKEN_H
#define TOKEN_H

#include "object.h"

typedef struct token_t token_t;
token_t *make_token(type_t type, char *str);
type_t token_type(token_t *t);
char *token_str(token_t *t);

typedef struct token_stream_t token_stream_t;
token_stream_t *make_token_stream(token_stream_t *ts, char *str);
void free_token_strem(token_stream_t *ts);
int token_stream_balanced(token_stream_t *ts);

token_t *token_stream_read(token_stream_t *ts);
token_t *token_stream_peek(token_stream_t *ts);

#endif
