#all: lib bin tests
include_path = ${BASE}/src

lib: charmap.c charmap.h
	gcc -c -g3 -O0 -o charmap.o charmap.c

test: lib test.c
	gcc -c -g3 -O0 -o test.o test.c

all: test lib
	gcc -o test test.o charmap.o
#bin: src/convert
#	./bin/convert data/test/test.txt

#debug:
#	cp scripts/gdb/debug.script ~/.gdbinit
#	gdb ./convert

