#all: lib bin tests
include_path = ${BASE}/src
GCC_FLAGS=-g3 -O0

lib: bitmap.c bitmap.h
	nasm -f elf64 -g -o bitcount.o bitcount.asm
	gcc -c $(GCC_FLAGS) -o stats.o stats.c
	gcc -c $(GCC_FLAGS) -o bitmap.o bitmap.c


test: lib bitmap_test.c
	gcc -c $(GCC_FLAGS) -o vconi.o ../vconi.c -I../map/
	gcc -c $(GCC_FLAGS) -o test.o bitmap_test.c -I../ -I../map/
	gcc -o test $(GCC_FLAGS) bitmap.o test.o bitcount.o stats.o vconi.o

debug: test
	#gdb -ex 'break bitmap.c:195' -ex 'dump buffer' -ex 'r' --args ./test test-data/256x256-1.bmp x
	gdb -ex 'break bmp_char_matrix_get if (cell->col.start == 8)' -ex 'break __bmp_col2mask' -ex 'r' --args ./test test-data/8x8-1.bmp x

#bin: src/convert
#	./bin/convert data/test/test.txt

#debug:
#	cp scripts/gdb/debug.script ~/.gdbinit
#	gdb ./convert

