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
    unsigned char opt[4][2] = {"l:"};
    int optidx = 0;

    unsigned char lang = 0x00;
    while(-1 != (option = getopt(argc, argv, opt[optidx]))) {
        switch (*opt[optidx]) {
            case 'l':
                lang = *optarg;
                break;
        }
        optidx++;
    }

    if (lang == 0x00) {
        dprintf(2, "required params l[ang]\n");
        exit(-1);
    }

    unsigned char d_vovwel[35] = { //33
            0x80, 0x81, 0x82, 0x83, //4
            0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, //6
            0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, //16
            0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, //7
            0xe2, 0xe3 //2
    };

    unsigned char b_vovwel[33] = { //18
            0x80, 0x81, 0x82, 0x83, //4
            0xbc, 0xbe, 0xbf, //3
            0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc7, 0xc8, 0xcb, 0xcc, 0xcd,  //8
            0xd7, //1
            0xe2, 0xe3 //2
    };

    unsigned char s_vovwel[22] = { //22
            0x82, 0x83,
            0xca, 0xcf,
            0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
            0xf2, 0xf3
    };

    const unsigned char b0 = 0xe0;
    unsigned char consonant = 0x95;
    unsigned char b1 = 0x00;
    unsigned char b2 = 0x80;
    unsigned char vovwel[35];
    int max_elm = 0;
    unsigned char u0 = 0x00;
    switch (lang) {
        case 'd':
            b1 = 0xa4;
            memcpy(&vovwel, &d_vovwel, 35);
            max_elm = 35;
            break;
        case 'b':
            b1 = 0xa6;
            memcpy(&vovwel, &b_vovwel, 33);
            max_elm = 33;
            break;
        case 's':
            b1 = 0xb6;
            memcpy(&vovwel, &s_vovwel, 22);
            consonant = 0x9A;
            max_elm = 22;
            u0 = 0x0d;
            break;
    }

    signed int constant = 0;

    for (int i=0; i<0x80; i++) {
        int izwj = 0;
        unsigned char *uchar = (unsigned char *) malloc(sizeof(unsigned char) * 3);
        unsigned char *ptr = uchar;
        *uchar++ = b0;
        *uchar++ = b1;
        b2 = (i + 0x80 + constant);
        *uchar = b2;
        int32_t codepoint = getCodePoint(ptr);

        if (i == 0x3f) {
            b1++;
            constant = -0x40;
        }

        int cl = ucdn_get_general_category(codepoint);
        if (cl == 2 || cl == 13) continue;
        unsigned char *line = (unsigned char *) malloc(sizeof(unsigned char) * 10);
        sprintf(line, "(%d) 0x%04x ", i, codepoint);
        if (cl == 10 || cl == 12) {
            izwj = 1;
            sprintf(line, "%s%c%c%c", line, 0xe0, 0xa6, 0x95);
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