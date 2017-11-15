all: src/convert src/compare src/generate map
	gcc -g3 -O0 -o ./bin/generate ./src/generate/main.c lib/ucdn/ucdn.o src/vconi.o -Isrc/ -Isrc/map
	gcc -g3 -O0 -o ./bin/convert ./src/convert/main.c lib/ucdn/ucdn.c -Isrc/ src/vconi.o src/map/charmap.o -Isrc/map/ -fno-stack-protector
	gcc -g3 -O0 -o ./bin/compare ./src/compare/main.c -fno-stack-protector

base: src/vconi.c
	gcc -c -g3 -O0 -o src/vconi.o src/vconi.c -Isrc/map/

generate: src/generate/main.c
	cd src/generate && make all && make test

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

debug:
	cp scripts/gdb/debug.script ~/.gdbinit
	gdb ./convert

save:
	git commit -m "saving home work" .
	git push -u origin master

report:
	./scripts/alphabets.sh