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

    const unsigned char *lang = *optarg;
    int number = (int)strtol(lang, NULL, 16);

    /**
     * 1	7	U+0000	U+007F	0xxxxxxx
2	11	U+0080	U+07FF	110xxxxx	10xxxxxx
3	16	U+0800	U+FFFF	1110xxxx	10xxxxxx	10xxxxxx
4	21	U+10000	U+10FFFF	11110xxx	10xxxxxx	10xxxxxx	10xxxxxx
     */


    unsigned char *buffer = (unsigned  char *) malloc(sizeof(unsigned char) * (bytes * 3) * 0x80);
    unsigned char *ptr = buffer;

    for (int i=number; i < (number + 0x80); i++) {
        int cl = ucdn_get_general_category(i);
        if (cl == 2 || cl == 13) continue;
        if (bytes == 1) {
            *buffer++ = i;
            continue;
        }

        for (int p=bytes - 1; p >= 0; p--) {
            result[p] = 0;
        }

        int izwj = 0;
        unsigned char *uchar = (unsigned char *) malloc(sizeof(unsigned char) * 3);
        unsigned char *ptr = uchar;
        *uchar++ = b0;
        *uchar++ = b1;
        b2 = (i + 0x80 + constant);
        *uchar = b2;


        if (i == 0x3f) {
            b1++;
            constant = -0x40;
        }



        unsigned char *line = (unsigned char *) malloc(sizeof(unsigned char) * 10);
        sprintf(line, "(%d) 0x%04x ", i, codepoint);
        if (cl == 10 || cl == 12) {
            izwj = 1;
            sprintf(line, "%s%c%c%c", line, 0xe0, 0xa6, vconsonant);
        }

        if (izwj == 1) {
            sprintf(line, "%s%c%c%c", line, 0xe2, 0x80, 0x8b); //0xE2 0x80 0x8B
            izwj = 0;
        }
        sprintf(line, "%s%s", line, ptr);

        printf("%s%c", line, 0xa);

    }

    return 0;
}