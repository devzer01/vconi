//
// Created by nayana on 11/9/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdint.h>
#include "vconi.h"

extern int ucdn_get_general_category(uint32_t code);

int main(int argc, char **argv)
{
    int option = 0;
    if (-1 == (option = getopt(argc, argv, "l:"))) {
        dprintf(2, "range start is required\n");
        exit(-1);
    }

    const unsigned char *lang = optarg;
    int number = (int)strtol(lang, NULL, 16);

    int consonant = 0x0;
    option = getopt(argc, argv, "c:");
    if (option != -1) {
        const unsigned char *chrconst = optarg;
        consonant = (int)strtol(chrconst, NULL, 16);
    }

    unsigned char *basechar = (unsigned char *) malloc(sizeof(unsigned char) * 4);
    basechar = getuchar(consonant, basechar);

    unsigned char *zwj = (unsigned char *) malloc(sizeof(unsigned char) * 4);
    sprintf(zwj, "%c%c%c", 0xe2, 0x80, 0x8b);

    unsigned char *buffer = (unsigned  char *) malloc(sizeof(unsigned char) * 3 * 0xFF);
    unsigned char *ptr = buffer;

    for (int i=number; i < (number + 0x80); i++) {
        int cl = ucdn_get_general_category(i);
        if (cl == 2 || cl == 13) continue;
        if (i <= 0x7f) {
            *buffer++ = i;
            continue;
        }

        unsigned char *uchar = (unsigned char *) malloc(sizeof(unsigned char) * 4);
        int32_t point = i;
        uchar = getuchar(point, uchar);

        if ((cl == 10 || cl == 12) && consonant != 0x00) {
            printf("%s%s", basechar, uchar);
        } else {
            printf("%s", uchar);
        }

        printf("%c", 0xa);
    }

    return 0;
}