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

int main() {
    int32_t codepoint = 0xD85;
    unsigned char *buffer = (unsigned char *) malloc(sizeof(unsigned char ) * 4);
    const unsigned char *letter = getuchar(codepoint, buffer);
    printf("%s\n", letter);
    return 0;
}
