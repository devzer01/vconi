#all: lib bin tests
include_path = ${BASE}/src
GCC_FLAGS=-g3 -O0

lib: bitmap.c bitmap.h
	nasm -f elf64 -g -o bitcount.o bitcount.asm
	gcc -c $(GCC_FLAGS) -o bitmap.o bitmap.c

test: lib bitmap_test.c
	gcc -c $(GCC_FLAGS) -o test.o bitmap_test.c
	gcc -o test $(GCC_FLAGS) bitmap.o test.o bitcount.o

#bin: src/convert
#	./bin/convert data/test/test.txt

#debug:
#	cp scripts/gdb/debug.script ~/.gdbinit
#	gdb ./convert

