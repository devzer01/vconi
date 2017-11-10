//
// Created by nayana on 11/10/17.
//

#ifndef VCONI_VCONI_H
#define VCONI_VCONI_H
//https://stackoverflow.com/questions/1675351/typedef-struct-vs-struct-definitions
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
typedef struct range {           //bukebukeka:sexyorio
    unsigned char bsize;
    int32_t mask;
    int32_t ch;
} range;

#endif //VCONI_VCONI_H

int32_t getCodePoint(unsigned char *buffer) {
    int32_t codepoint = (0b00111111 & buffer[2]);
    codepoint = codepoint + ((0b00111111 & buffer[1]) << 6);
    codepoint = codepoint + ((0b00001111 & buffer[0]) << 12);
    return codepoint;
}



#define CONSEQ_CHAR 0b10000000
#define NCONSEQ_CHAR 0b00111111

range *getcodeparams(int32_t number, range *ptr)
{

    if (number >= 0x80 && number <= 0x7ff) {
        ptr->bsize = 2;
        ptr->mask = (0b11000000 << 8) + CONSEQ_CHAR;
        ptr->ch =   (0b00011111 << 8) + NCONSEQ_CHAR;
    } else if (number >= 0x800 && number <= 0xffff) {
        ptr->bsize = 3;
        ptr->mask = (0b11100000 << 16) + (CONSEQ_CHAR << 8) + CONSEQ_CHAR;
        ptr->ch =   (0b00001111 << 16) + (NCONSEQ_CHAR << 8) + NCONSEQ_CHAR;
    } else if (number >= 0x10000 && number <= 0x10ffff) {
        ptr->bsize = 4;
        ptr->mask = (0b11110000 << 24) + (0b10000000 << 16) + (0b10000000 << 8) + 0b10000000;
    } else {
        ptr->bsize = 1;
    }

    return ptr;
}

/**
 * code point to utf8
 *
 * @param codepoint
 * @param buf
 * @return
 */
unsigned char *getuchar(int32_t codepoint, unsigned char *buf)
{
    range *ptr = (range *) malloc(sizeof(range));
    int32_t chr = 0;
    int32_t needle = 0xff;
    int shft = 1;
    ptr = getcodeparams(codepoint, ptr);
    int loop = ptr->bsize;
    while (loop-- >= 0) {
        chr += codepoint & (ptr->ch & needle);
        codepoint = (codepoint | (ptr->ch & needle)) << 2;
        needle = needle << 8 * shft++;
    }
    chr += ptr->mask;
    unsigned char *cptr = (unsigned  char *) &chr;
    loop = ptr->bsize;
    while (loop-- >= 0) {
        memcpy(buf+loop, cptr++, 1);
    }
    return buf;
}



