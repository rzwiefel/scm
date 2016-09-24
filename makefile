BIN=scm
CC=gcc
CFLAGS=-std=gnu99 -g -O2 -Wall -pedantic
LDFLAGS=-lreadline
ODIR=obj
SDIR=src

# find all source files
SOURCES=$(shell cd $(SDIR) && ls *.c | grep -v lex.yy.c)  lex.yy.c
OBJS=$(addprefix $(ODIR)/, $(SOURCES:.c=.o))

.PHONY: clean test

all: $(BIN)

# build interpreter
$(BIN): $(ODIR) $(OBJS)
	$(CC) $(OBJS) -o $(BIN)  $(LDFLAGS)

# build object files from sources
$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(SDIR)/lex.yy.c: $(SDIR)/scheme.l
	flex -t $< > $@

# make obj directory
$(ODIR):
	mkdir -p $(ODIR)

# clean up
clean:
	rm -rf $(ODIR)/*.o $(BIN) $(SDIR)/lex.yy.c

# code navigation tags
tags: $(addprefix $(SDIR)/, $(SOURCES))
	ctags -R

# build and run tests
test: $(BIN)
	./test/runner.sh ./$(BIN) ./test/suite
