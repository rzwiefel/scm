#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "token.h"

#include "read.h"
#include "eval.h"
#include "print.h"

#include "vm.h"

char *concat(char *a, char *b) {

  if (a == NULL) return b;

  size_t len_a = strlen(a);
  size_t len = len_a + strlen(b) + 2; //<a>\n<b>\0

  a = realloc(a, len);
  *(a + len_a) = '\n'; // '\0' -> '\n'

  strcpy(a + len_a + 1, b);
  free(b);

  return a;
}

token_stream_t *prompt_validate(char *str, char *history, token_stream_t *prev) {

  char *buff = readline(str);

  if (buff == NULL) return NULL;

  token_stream_t *ts = make_token_stream(prev, buff);

  history = concat(history, buff);

  if (!token_stream_balanced(ts)) {
    return prompt_validate(".. ", history, ts);
  }

  add_history(history);
  free(history);

  return ts;
}

token_stream_t *prompt(char *str) {
  return prompt_validate(str, NULL, NULL);
}

vm_t *vm = NULL;

int main (int argc, char** argv) {

  vm = make_vm();

  vm_set_root_env(vm, init());
  token_stream_t *ts = NULL;

  while ((ts = prompt(">> ")) != NULL) {
    while (token_stream_peek(ts) != NULL) {
      print(eval(reader(ts), vm_root_env(vm)));
      printf("\n");
    }
    free_token_strem(ts);
    vm_gc(vm);
  }

  free_vm(vm);

  return 0;
}
