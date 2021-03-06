GCC_FLAGS=-g3 -O0

all: base udb lib map src/convert src/compare generate
	gcc -g3 -O0 -o ./bin/convert ./src/convert/main.c  lib/ucdn/ucdn.o src/vconi.o src/map/charmap.o -Isrc/map/ -Isrc/ -fno-stack-protector
	gcc -g3 -O0 -o ./bin/compare ./src/compare/main.c -fno-stack-protector

udb: src/udb/main.c src/udb/udb.c src/udb/udb.h base
	gcc -c -O0 -g3 -o src/udb/udb.o src/udb/udb.c
	gcc -O0 -g3 -o src/udb/udb src/udb/main.c src/udb/udb.o src/vconi.o -Isrc/ -Isrc/map/
	#gcc -DDEBUG -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -o src/udb/udb src/udb/main.c -lasan

bitmap: src/bitmap/bitmap.c src/bitmap/bitmap.h src/bitmap/main.c
	nasm -f elf64 -g -o src/bitmap/bitcount.o src/bitmap/bitcount.asm
	gcc -c -O0 -g3 -o src/bitmap/bitmap.o src/bitmap/bitmap.c
	gcc -c -O0 -g3 -o src/bitmap/main.o src/bitmap/main.c
	gcc -O0 -g3 -o bin/bitmap src/bitmap/bitcount.o src/bitmap/bitmap.o src/bitmap/main.o
	# gcc -o bin/bitmap -O0 -g3 src/bitmap/main.c src/bitmap/bitmap.o

word: data/input/test.txt
	cd data && make word
	./src/udb/udb < data/input/test.txt > data/test/p1.txt
	./src/udb/udb < data/input/test_benga.txt > data/test/p2.txt
	./src/udb/udb < data/input/test_devan.txt > data/test/p3.txt
	cat data/input/test_burm.txt | ./src/udb/udb > data/test/p4.txt
	column -e -c data/test/p1.txt data/test/p2.txt data/test/p3.txt data/test/p4.txt

rbitmap: bitmap
	./bin/bitmap

bdebug: bitmap
	cp scripts/gdb/debug.script ~/.gdbinit
	gdb

base: src/vconi.c
	gcc -c -g3 -O0 -o src/vconi.o src/vconi.c -Isrc/map/

generate: src/generate/main.c udb
	gcc -g3 -O0 -o bin/generate src/generate/main.c lib/ucdn/ucdn.o src/vconi.o src/map/charmap.o src/udb/udb.o -Isrc/ -Isrc/map -Isrc/udb
	#gcc -o bin/generate src/generate/generate.o src/udb/udb.o

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
	rm bin/* 2> /dev/null; true
	find ./data/report -type f -exec rm {} \;
	find ./data/output -type f -exec rm {} \;

char: all
	./bin/convert -l 0x06 -d f -f test.txt -t pali.b8e
	./bin/convert -l 0x03 -d b -f pali.b8e -t pali_ban.txt
	./bin/convert -l 0x10 -d b -f pali.b8e -t pali.txt
	./src/udb/udb

debug: all
	# rm dv.txt.re.map dv.txt.re
	./bin/convert -l 0x03 -d f -f data/output/Bengali-0x03-alpha.txt -t dv.txt
	./bin/convert -l 0x03 -d b -f dv.txt -t dv.txt.re
	diff -w dv.txt.re data/output/Bengali-0x03-alpha.txt
	#cp scripts/gdb/debug.script ~/.gdbinit
	#gdb
utf8: src/utf8/main.c base
	gcc -O0 -g3 -o src/utf8/utf8 src/utf8/main.c src/vconi.o -Isrc/ -Isrc/map/

save:
	git commit -m "saving home work" .
	git push -u origin master

report:
	./scripts/alphabets.sh

textdebug:
	cat data/input/debug.txt | tr -d '\n' | xxd -c 9 -g 3
	./bin/convert -l 0x15 -d f -f data/input/debug.txt -t data/output/single-debug.txt && ./bin/convert -l 0x10 -d b -f data/output/single-debug.txt -t data/output/sinhala-debug.txt
	cat data/output/sinhala-debug.txt
