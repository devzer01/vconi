all: src/convert src/compare src/generate
	gcc -g3 -O0 -o ./bin/generate ./src/generate/main.c lib/ucdn/ucdn.c -Ilib/
	gcc -g3 -O0 -o ./bin/convert ./src/convert/main.c lib/ucdn/ucdn.c -Ilib/  -fno-stack-protector
	gcc -g3 -O0 -o ./bin/compare ./src/compare/main.c -fno-stack-protector

tests: test/libs_test.c
	gcc -g3 -O0 -o ./test/bin/libs_test ./test/libs_test.c -fno-stack-protector -Ilib/

test: src/convert
	./bin/convert data/test/test.txt

debug:
	cp scripts/gdb/debug.script ~/.gdbinit
	gdb ./convert
