from __future__ import print_function, division, unicode_literals, with_statement, absolute_import, nested_scopes, \
    generators

import functools
import math
import operator as op
from pprint import pprint

from env import Env
from util import Symbol, get_data, Char, Pair, noop


class Procedure(object):
    def __init__(self, params, body, env):
        self.params, self.body, self.env = params, body, env

    def __call__(self, *args, **kwargs):
        if kwargs is not None and len(kwargs) > 0:
            print("[WARN] Procedure call got kwargs and is not implemented to do anything with them yet")
        return leval(self.body, Env(zip(self.params, args), self.env))


class ops(object):
    @staticmethod
    def add(*x):
        return sum(x)

    @staticmethod
    def func(op, *x):
        return functools.reduce(op, x)


def standard_env():
    """An environment with some Scheme standard procedures."""
    env = Env()
    env.update(vars(math))  # sin, cos, sqrt, pi, ...
    env.update({
        '*': lambda *x: ops.func(op.mul, *x),
        '+': lambda *x: ops.func(op.add, *x),
        '-': lambda *x: ops.func(op.sub, *x),
        '/': lambda *x: ops.func(op.truediv, *x),
        '<': lambda *x: ops.func(op.lt, *x),
        '<=': lambda *x: ops.func(op.le, *x),
        '=': lambda *x: ops.func(op.eq, *x),
        '>': lambda *x: ops.func(op.gt, *x),
        '>=': lambda *x: ops.func(op.ge, *x),
        'abs': abs,
        'append': op.add,
        'apply': lambda x, y: x(*y),
        'begin': lambda *x: x[-1],
        'boolean?': lambda x: isinstance(x, bool),
        'car': lambda x: x[0],
        'cdr': lambda x: x[1:],
        'char?': lambda x: isinstance(x, Char),
        'cons': lambda *x: Pair(x),
        'env': lambda: env.env(),
        'eq?': op.is_,
        'equal?': op.eq,
        'eval': lambda *x, **y: leval(*x, **y),
        'first': lambda *x: env.get('car')(*x),
        'length': len,
        'list': lambda *x: list(x),
        'list?': lambda x: isinstance(x, list),
        'map': map,
        'max': max,
        'min': min,
        'not': op.not_,
        'null?': lambda x: len(x) == 0,
        'number?': lambda x: isinstance(x, int),  # TODO (RCZ) - not right yet
        'open': open,
        'read-file': lambda x: x.read(),
        'pair?': lambda x: isinstance(x, Pair),
        'pprint': pprint,
        'print': lambda *x: print(get_data(*x)),
        'procedure?': callable,
        'rest': lambda *x: env.get('cdr')(*x),
        'round': round,
        'string?': lambda x: isinstance(x, str),
        'sum': lambda *x: sum(x),
        'symbol?': lambda x: isinstance(x, Symbol),
        'type': type,
        'tuple': lambda x: tuple(x),
        'vector': lambda *x: list(x),
        'vector?': lambda x: env.get('list?')(x),
        'write': lambda *x: env.get('print')(*x)
    })
    return env


global_environment = standard_env()


def leval(x, env=global_environment):
    if isinstance(x, Symbol):
        res = env.find(x)
        return res[x] if res is not None else None
    if isinstance(x, str):
        return x
    elif isinstance(x, list):
        return [leval(exp, env) for exp in x]
    elif not isinstance(x, tuple):
        return x
    elif x[0] == 'quote':
        (_, exp) = x
        return exp
    elif x[0] == 'if':  # (if test conseq alt)
        if len(x) == 3:
            x += (noop,)  # todo (rcz) - this could be faster
        (_, test, conseq, alt) = x
        exp = (conseq if leval(test, env) else alt)
        return leval(exp, env)
    elif x[0] == 'define':  # (define var exp)
        (_, var, exp) = x
        env[var] = leval(exp, env)
    elif x[0] == 'set!':  # (set! var exp)
        (_, var, exp) = x
        env.find(var)[var] = leval(exp, env)
    elif x[0] == 'lambda':  # (lambda (var...) body)
        (_, parms, body) = x
        return Procedure(parms, body, env)
    else:  # (proc arg...)
        proc = leval(x[0], env)
        args = [leval(exp, env) for exp in x[1:]]
        return proc(*args)
