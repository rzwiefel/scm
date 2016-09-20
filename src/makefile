cc=gcc
cflags=-std=c99 -g -O2 -Wall -pedantic
includes=../libs

src=$(shell find . -type f | grep .c$$ | grep -v lex.yy.c) lex.yy.c
obj=$(src:.c=.o)


all: makefile.dep $(obj)
	@echo done!

%.o: %.c
	$(cc) -c $(cflags) -I $(includes) $< -o $@

lex.yy.c: scheme.l
	flex -t $< > $@

test:
	@echo testing!

clean:
	rm -f $(obj) lex.yy.c makefile.dep

makefile.dep: $(src)
	$(cc) $(src) -MM -I $(includes) > makefile.dep

ifneq ($(MAKECMDGOALS),clean)
-include makefile.dep
endif
