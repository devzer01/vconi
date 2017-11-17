all: src/convert src/compare generate map lib udb
	gcc -g3 -O0 -o ./bin/convert ./src/convert/main.c lib/ucdn/ucdn.c -Isrc/ src/vconi.o src/map/charmap.o -Isrc/map/ -fno-stack-protector
	gcc -g3 -O0 -o ./bin/compare ./src/compare/main.c -fno-stack-protector

udb: src/udb/main.c
	gcc -O0 -g3 -o src/udb/udb src/udb/main.c

base: src/vconi.c
	gcc -c -g3 -O0 -o src/vconi.o src/vconi.c -Isrc/map/

generate: src/generate/main.c
	gcc -g3 -O0 -c -o src/generate/generate.o  src/generate/main.c -Isrc/ -Isrc/map
	gcc -o bin/generate src/generate/generate.o lib/ucdn/ucdn.o src/vconi.o

lib: lib/ucdn/ucdn.o
	gcc -c -g3 -O0 -o lib/ucdn/ucdn.o lib/ucdn/ucdn.c

map: base src/map/charmap.c src/map/charmap.h
	export BASE=`pwd`; cd src/map && make all

tests:
	gcc -g3 -O0 -o ./test/bin/libs_test ./test/libs_test.c lib/ucdn/ucdn.o lib/vconi.o -fno-stack-protector -Ilib/

test: src/convert
	./bin/convert data/test/test.txt

headers: util/conf/map2.csv
	cd util/inc/; php all.php

clean:
	find ./ -name \*.o -exec rm {} \;
	cd data/report && rm *
	cd data/output && rm *
	rm bin/*
debug:
	cp scripts/gdb/debug.script ~/.gdbinit
	gdb ./convert

save:
	git commit -m "saving home work" .
	git push -u origin master

report:
	./scripts/alphabets.sh

textdebug:
	cat data/input/debug.txt | tr -d '\n' | xxd -c 9 -g 3
	./bin/convert -l 0x15 -d f -f data/input/debug.txt -t data/output/single-debug.txt && ./bin/convert -l 0x10 -d b -f data/output/single-debug.txt -t data/output/sinhala-debug.txt
	cat data/output/sinhala-debug.txt
