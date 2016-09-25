BIN=scm
CC=gcc
CFLAGS=-std=gnu99 -g -O2 -Wall -pedantic
LDFLAGS=-lreadline
ODIR=obj
SDIR=src

# find all source files
SOURCES=$(shell cd $(SDIR) && ls *.c | egrep -v "lexer.c|parser.c") lexer.c parser.c
OBJS=$(addprefix $(ODIR)/, $(SOURCES:.c=.o))

.PHONY: clean test

all: $(BIN)

makefile.dep: $(addprefix $(SDIR)/, $(SOURCES))
	$(CC) $^ -MM > $@

# build interpreter
$(BIN): $(ODIR) $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(LDFLAGS)

# build object files from sources
$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(SDIR)/lexer.h $(SDIR)/lexer.c: $(SDIR)/lexer.l
	flex --header-file=$(SDIR)/lexer.h --outfile=$(SDIR)/lexer.c $<

$(SDIR)/parser.h $(SDIR)/parser.c: $(SDIR)/parser.y
	bison --output-file=$(SDIR)/parser.c --defines=$(SDIR)/parser.h --warnings=all --feature=all $<

# make obj directory
$(ODIR):
	mkdir -p $(ODIR)

# clean up
clean:
	rm -rf $(ODIR)/*.o $(BIN) $(SDIR)/lexer.h $(SDIR)/lexer.c $(SDIR)/parser.h $(SDIR)/parser.c

# code navigation tags
tags: $(addprefix $(SDIR)/, $(SOURCES))
	ctags -R

# build and run tests
test: $(BIN)
	./test/runner.sh ./$(BIN) ./test/suite

ifneq ($(MAKECMDGOALS),clean)
-include makefile.dep
endif
