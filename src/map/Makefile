#all: lib bin tests
include_path = ${BASE}/src

lib: charmap.c charmap.h
	gcc -c -g3 -O0 -o charmap.o charmap.c -I$(include_path)

test: lib tests/test.c
	gcc -g3 -O0 -o test tests/test.c ${BASE}/src/vconi.o charmap.o -I$(include_path) -I${BASE}/src/map

#bin: src/convert
#	./bin/convert data/test/test.txt

#debug:
#	cp scripts/gdb/debug.script ~/.gdbinit
#	gdb ./convert

