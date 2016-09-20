CC=gcc
MAIN=runner.c
OUT=runner

SOURCES=$(filter-out $(MAIN), $(shell ls *.c))
ODIR=../obj
OBJS=$(addprefix $(ODIR)/, $(shell ls $(ODIR) | grep -v main.o))

.PHONY: clean

all: runner

runner: $(OBJS) $(MAIN) $(SOURCES) test.h
	$(CC) $(OBJS) $(SOURCES) $(MAIN) -o $(OUT)

runner.c: Makefile $(SOURCES) $(OBJS)
	@echo '// generated test runner' > $(MAIN)
	@grep -r --include=\*.{c,h} --exclude=runner.c 'void test_' . \
		| sed -E 's/.*(test_.*) .*/void \1;/' >> $(MAIN)
	@echo 'int main () {' >> $(MAIN)
	@grep -r --include=\*.{c,h} --exclude=runner.c 'void test_' . \
		| sed -E 's/.*(test_.*) .*/\1;/' >> $(MAIN)
	@echo 'return 0; }' >> $(MAIN)

clean:
	rm -rf $(MAIN) $(OUT)
