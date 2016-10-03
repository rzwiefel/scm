from __future__ import print_function, division, unicode_literals, with_statement, absolute_import, nested_scopes, \
    generators

import sys
import traceback

from leval import leval
from parse import parse
from util import get_data

exec(r'''if 'raw_input' in vars(__builtins__):
    input = raw_input
    range = xrange''')

istty = sys.stdin.isatty()


def repl():
    try:
        while True:
            try:
                val = leval(parse(str(input('-> ') if istty else input())))
                print(get_data(val)) if istty else ''
                # print('type:', type(val))
            except SyntaxError:
                traceback.print_exc()
                print()
            except LookupError:
                traceback.print_exc()
                print()
            except EOFError:
                sys.exit(0)
    except KeyboardInterrupt:
        print("\nExiting")


if __name__ == '__main__':
    repl()
