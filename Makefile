all: convert/main.c compare/main.c generate/main.c
	gcc -g3 -O0 -o ./bin/generate ./generate/main.c lib/ucdn/ucdn.c -Ilib/
	gcc -g3 -O0 -o ./bin/convert ./convert/main.c lib/ucdn/ucdn.c -Ilib/  -fno-stack-protector
	gcc -g3 -O0 -o ./bin/compare ./compare/main.c -fno-stack-protector

test: convert
	./convert test/test.txt

debug:
	cp debug.script ~/.gdbinit
	gdb ./convert
