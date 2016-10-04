import functools
import itertools
import sys

py2 = True
if sys.version_info >= (3, 0):
    py2 = False

def first(ls):
    return ls[0]


def rest(ls):
    return ls[1:]


def tf(x, *funcs):
    res = x
    for func in funcs:
        res = func(res)
    return res


def compose2(f, g):
    return lambda *x, **y: f(g(*x, **y))


def compose(*funcs):
    return functools.reduce(compose2, funcs)


def get_data(x):
    if x is None:
        return 'nil'
    elif isinstance(x, tuple):
        if len(x) == 0:
            return 'nil'
        if len(x) == 1:
            return str(get_data(x[0]))
        return '(%s)' % ' '.join(map(str, map(get_data, x)))
    elif isinstance(x, list):
        return '[%s]' % ' '.join(map(str, map(get_data, x)))
    elif isinstance(x, bool):
        return '#t' if x else '#f'
    elif isinstance(x, str) and not isinstance(x, Char) and not isinstance(x, Symbol):
        return '"%s"' % x
    else:
        return str(x)

def noop(*x, **y):
    pass

class Symbol(str):
    pass


class Char(str):
    pass


class Pair(tuple):
    def __init__(self, x):
        if len(x) != 2:
            raise TypeError("Pair must have 2 arguments")
        if py2:
            super(Pair, self).__init__(x)
        else:
            super().__init__()


class PeekableGen(object):
    def __init__(self, gen):
        self.gen = iter(gen)

    def __iter__(self):
        return self

    def __next__(self):
        return next(self.gen)

    def peek(self):
        try:
            val = next(self.gen)
        except StopIteration as e:
            return None
        self.gen = itertools.chain(val, self.gen)
        return val

    # py2 compatibility
    next = __next__
