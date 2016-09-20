#include <stdio.h>
#include <string.h>

#include "eval.h"
#include "print.h"

object_t *_if(object_t *predicate, object_t *consequent, object_t *alternative, object_t **env) {
  if (true(error(predicate))) return predicate;

  if (!false(predicate)) {
    return eval(consequent, env);
  } else {
    return eval(alternative, env);
  }
}

#define if_predicate(expr) car(expr)
#define if_consequent(expr) car(cdr(expr))
#define if_alternative(expr) car(cdr(cdr(expr)))

object_t *eval_if(object_t *expr, object_t **env) {

  object_t *body = cdr(expr);

  return _if(eval(if_predicate(body), env), if_consequent(body), if_alternative(body), env);
}

object_t *plus(object_t *a, object_t *b) {
  if (a == NULL) return plus(make_fixnum_int(0), b);
  if (b == NULL) return plus(a, make_fixnum_int(0));

  if (!true(number(a)) || !true(number(b)))
    return make_error("can't perform arithmetic on non numeric values");

  if (a->type == FLONUM || b->type == FLONUM) {
    if (a->type != FLONUM) return make_flonum_float(a->data.fix + b->data.flo);
    if (b->type != FLONUM) return make_flonum_float(a->data.flo + b->data.fix);
    return make_flonum_float(a->data.flo + b->data.flo);
  }

  return make_fixnum_int(a->data.fix + b->data.fix);
}


// (+ 1 2 3)
object_t *eval_plus(object_t *expr, object_t **env) {
  if (expr == NULL) return NULL;
  object_t *op = eval(car(cdr(expr)), env);
  if (true(error(op))) return op;
  return plus(op, eval_plus(cdr(expr), env));
}

/*
object_t *extend(object_t *args, object_t *params, object_t **env, object_t *closure, char trace) {
  if (args == NULL || params == NULL) return closure;
  object_t *sym = car(args);
  object_t *val = eval(car(params), env);

  if (trace) {
    print(sym);
    printf(" => ");
    print(val);
    printf("\n");
  }

  return define(extend(cdr(args), cdr(params), env, closure, trace), sym, val);
}*/

object_t *eval_args(object_t *frame, object_t *params, object_t *args, object_t **env) {
  if (args == NULL || params == NULL) return frame;

  object_t *sym = car(params);
  object_t *val = eval(car(args), env);

  return define(eval_args(frame, cdr(params), cdr(args), env), sym, val);
}

object_t *eval_procedure(object_t *procedure, object_t *args, object_t **env) {
  object_t *list = (object_t*) procedure->data.ptr;

  object_t *parent = car(list); // captured environment
  object_t *frame = make_frame(parent);
  object_t *params = car(cdr(list));
  object_t *extended_env = eval_args(frame, params, args, env);
  object_t *body = car(cdr(cdr(list)));

  return eval(body, &extended_env);
}

object_t *eval_pair(object_t *expr, object_t **env) {

  object_t *ret = NULL;
  object_t *procedure = eval(car(expr), env);

  if (procedure == NULL) return make_error("nil is not operator");

  if (procedure->trace == 1) {
    printf("calling: ");
    print(cons(procedure, cdr(expr)));
    printf("\n");
  }

  if (procedure->type == PRIMITIVE) {
    ret = procedure->data.fn(expr, env);
  } else if (procedure->type == PROCEDURE) {
    ret = eval_procedure(procedure, cdr(expr), env);
  } else if (procedure->type == ERROR) {
    return procedure;
  } else {
    return make_error("not a procedure");
  }

  if (procedure->trace == 1) {
    printf("returning: ");
    print(ret);
    printf("\n");
  }

  return ret;
}

object_t *eval_quote(object_t *expr, object_t **env) {
  return car(cdr(expr));
}

object_t *eval(object_t *expr, object_t **env) {

  if (expr == NULL) return NULL;

  switch (expr->type) {
    case FIXNUM:
    case FLONUM:
    case CHARACTER:
    case STRING:
    case BOOLEAN:
    case ERROR:
    case PRIMITIVE:
    case PROCEDURE:
      return expr;

    case SYMBOL: {
      return lookup(*env, expr);;
    }

    case PAIR:
      return eval_pair(expr, env);
  }

  return make_error("unknown expression type");
}

object_t *eval_define(object_t *expr, object_t **env) {
  object_t *sym = car(cdr(expr));
  object_t *val = eval(car(cdr(cdr(expr))), env);
  define(*env, sym, val);
  return val;
}

object_t *eval_error(object_t *expr, object_t **env) {
  object_t *msg = eval(car(cdr(expr)), env);
  if (msg->type != STRING) return make_error("whaaat!!!");
  return str_to_error(msg->data.ptr);
}

#define eval_predicate(fn,p) \
  object_t *fn(object_t *expr, object_t **env) { \
    object_t *o = eval(car(cdr(expr)), env); \
    if (true(error(o))) return o; \
    return p(o); \
  }

eval_predicate(nullp, null)
eval_predicate(numberp, number)
eval_predicate(booleanp, boolean)
eval_predicate(errorp, error)
eval_predicate(stringp, string)
eval_predicate(characterp, character)
eval_predicate(symbolp, symbol)
eval_predicate(pairp, pair)

object_t *eval_lambda(object_t *expr, object_t **env) {
  object_t *args = car(cdr(expr));
  object_t *body = cdr(cdr(expr));
  return make_procedure(*env, args, body);
}

object_t *trace(object_t *op) {
  op->trace = 1;
  return op;
}

// (trace operator)
object_t *eval_trace(object_t *expr, object_t **env) {
  object_t *op = eval(car(cdr(expr)), env);
  return trace(op);
}

object_t *eval_eval(object_t *expr, object_t **env) {
  return eval(eval(car(cdr(expr)), env), env);
}

object_t *eval_cons(object_t *expr, object_t **env) {
  object_t *a = eval(car(cdr(expr)), env);
  object_t *b = eval(car(cdr(cdr(expr))), env);
  return cons(a, b);
}

object_t *eval_car(object_t *expr, object_t **env) {
  object_t *p = eval(car(cdr(expr)), env);
  return car(p);
}

object_t *eval_cdr(object_t *expr, object_t **env) {
  object_t *p = eval(car(cdr(expr)), env);
  return cdr(p);
}

object_t *eval_env(object_t *expr, object_t **env) {
  return *env;
}

object_t *eval_begin(object_t *expr, object_t **env) {
  object_t *val = eval(car(expr), env);
  object_t *next = cdr(expr);

  if (next == NULL) {
    return val;
  } else {
    return eval_begin(next, env);
  }
}

object_t *eval_print(object_t *expr, object_t **env) {
  object_t *o = eval(car(cdr(expr)), env);
  print(o);
  printf("\n");
  return o;
}

#define def(sym,fun) \
  define(env, make_symbol(sym), make_primitive(fun));

object_t *init() {
  object_t *env = make_frame(NULL);

  def("+", eval_plus)
  def("if", eval_if)
  def("quote", eval_quote)
  def("define", eval_define)
  def("error", eval_error)

  def("number?", numberp)
  def("boolean?", booleanp)
  def("error?", errorp)
  def("string?", stringp)
  def("char?", characterp)
  def("symbol?", symbolp)
  def("pair?", pairp)
  def("null?", nullp)

  def("eval", eval_eval)
  def("lambda", eval_lambda)
  def("trace", eval_trace)

  def("cons", eval_cons)
  def("car", eval_car)
  def("cdr", eval_cdr)
  def("begin", eval_begin)

  def("print", eval_print)
  def("env", eval_env)

  return env;
}

