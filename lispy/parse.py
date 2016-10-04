import ast

from util import PeekableGen, Symbol, Char

START_DELIM = ('(', '[')
END_DELIM = (')', ']')
WHITE = (' ', '\n', '\t')
DELIM = (None,) + WHITE + END_DELIM

def parse(s):
    return tokenize(PeekableGen(s.strip()))


def tokenize(stream):
    if stream.peek() in START_DELIM:
        return read_list(stream)
    else:
        return read_symbol(stream)


def read_list(stream):
    l = []
    first = next(stream)
    peek = stream.peek()
    while peek not in END_DELIM:
        if peek in START_DELIM:
            l.append(read_list(stream))
        elif peek == ' ':
            next(stream)
        else:
            l.append(read_symbol(stream))
        peek = stream.peek()
    last = next(stream)

    if first == '(':
        assert last == ')'
        return tuple(l)
    if first == '[':
        assert last == ']'
        return l



def read_symbol(stream, delim=DELIM):
    cont = True
    symbol = str(next(stream))
    peek = stream.peek()
    escape_check = lambda: True
    if symbol[0] == '\'':
        return ('quote', tokenize(stream))

    if symbol[0] == '"':
        delim = ('"',)
        escape_check = lambda: symbol[-1] != '\\'

    while peek not in delim and escape_check() and cont:
        symbol += next(stream)
        peek = stream.peek()
        if symbol[0] == '"' and escape_check() and peek == '"':
            cont = False
            symbol += next(stream)
    return atom(symbol)


def consume_whitespace(stream):
    while stream.peek() in WHITE:
        next(stream)


def atom(token):
    if token == '#t':
        return True
    if token == '#f':
        return False

    if token.startswith('#\\'):
        return Char(token) # TODO (RCZ) - Should I cut off the #\ ?

    try:
        return ast.literal_eval(token)
    except ValueError:
        pass
    except SyntaxError:
        pass

    return Symbol(token)
