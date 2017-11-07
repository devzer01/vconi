all: convert.c convert.h compare.c
	gcc -g3 -O0 -o convert convert.c
	gcc -g3 -O0 -o compare compare.c -L/usr/lib/debug

test: convert
	./convert test/test.txt

debug:
	cp debug.script ~/.gdbinit
	gdb ./convert
