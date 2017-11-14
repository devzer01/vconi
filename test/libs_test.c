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

int test_utf8_gen() {
    int32_t codepoint = 0xD85;
    unsigned char *buffer = (unsigned char *) malloc(sizeof(unsigned char ) * 4);
    const unsigned char *letter = getuchar(codepoint, buffer);
    printf("%s\n", letter);
    return 0;
}


int main()
{
    printf("self test size of unsigned char %ld \n", sizeof(unsigned char));
    printf("self test size of int %ld \n", sizeof(int));
    printf("self test size of short %ld \n", sizeof(short));
    printf("self test size of int %ld \n", sizeof(unsigned int));
    if (test_utf8_gen() == 0) {
        printf("success\n");
    }
}


