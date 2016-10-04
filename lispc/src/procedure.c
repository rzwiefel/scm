#include "procedure.h"
#include "pair.h"
#include "env.h"
#include "eval.h"

#include "print.h"

typedef struct {
  object_t *body;
  object_t *params;
  object_t *env;
} proc_t;

object_t *make_procedure(object_t *env, object_t *params, object_t *body) {
  object_t *o = make(PROCEDURE, sizeof(proc_t));
  object_data(o, proc_t).body = body;
  object_data(o, proc_t).params = params;
  object_data(o, proc_t).env = env;
  return o;
}

predicate(procedure, PROCEDURE)

object_t *eval_args(object_t *frame, object_t *params, object_t *args, object_t **env) {
  if (args == NULL || params == NULL) return frame;

  object_t *sym = car(params);
  object_t *val = eval(car(args), env);

  return define(eval_args(frame, cdr(params), cdr(args), env), sym, val);
}

object_t *proc_apply(object_t *procedure, object_t *args, object_t **env) {
  object_t *parent = object_data(procedure, proc_t).env; // captured environment
  object_t *frame = make_frame(parent);
  object_t *params = object_data(procedure, proc_t).params;
  object_t *extended_env = eval_args(frame, params, args, env);
  object_t *body = car(object_data(procedure, proc_t).body);

  return eval(body, &extended_env);
}
