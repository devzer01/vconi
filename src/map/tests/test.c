//
// Created by nayana on 11/11/17.
//
#include "vconi.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdint.h>
#include "charmap.h"
#include "test_config.h"

int test_byte_array_to_struct() {
    const unsigned char *bytearray ="\x80\x9a\x00\x00";
    b8e_rec *ptr = (b8e_rec *) bytearray;
    if (ptr->value == 0x80 && ptr->codepoint == 0x9a) {
        printf("%c", ptr->codepoint);
        return 0;
    }
    else return 1;
}

int test_parse_config(){
    unsigned char item = 5;
    b8e_config *config = (b8e_config *) malloc(sizeof(b8e_config));
    b8e_map *map = map_init(config);
    map = map_load(config, L_SINHALA, map);
    const b8e_rec rec = map_item(map, item);
    printf("testing rec.value %#0x is == %#0x\n", rec.value, sinhala[item]);
    if (rec.value == sinhala[item]) {
        return 0;
    }
    return 1;
}

int test_lookup_value(){
    unsigned char item = 5;
    b8e_config *config = (b8e_config *) malloc(sizeof(b8e_config));
    b8e_map *map = map_init(config);
    map = map_load(config, L_SINHALA, map);
    const b8e_rec rec = codepoint2local(map, 0x0D85);
    printf("testing rec.value %#0x is == %#0x\n", rec.value, sinhala[item]);
    if (rec.value == sinhala[item]) {
        return 0;
    }
    return 1;
}

int main()
{
    printf("self test size of unsigned char %ld \n", sizeof(unsigned char));
    printf("self test size of int %ld \n", sizeof(int));
    printf("self test size of short %ld \n", sizeof(short));
    printf("self test size of int %ld \n", sizeof(unsigned int));
    if (test_lookup_value() == 0) {
        printf("success\n");
    }
}


