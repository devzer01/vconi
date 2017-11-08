all: src/convert.c convert/convert.h src/compare.c
	gcc -g3 -O0 -o ./bin/convert ./convert/main.c
	gcc -g3 -O0 -o ./bin/compare ./compare/main.c -fno-stack-protector

test: convert
	./convert test/test.txt

debug:
	cp debug.script ~/.gdbinit
	gdb ./convert
