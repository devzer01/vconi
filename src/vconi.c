//
// Created by nayana on 11/11/17.
//

#include "vconi.h"

/**
 *
 * @param buffer
 * @return int32_t codepoint
 */
int32_t utf82codepoint(unsigned char *buffer) {
    int32_t codepoint = (0b00111111 & buffer[2]);
    codepoint = codepoint + ((0b00111111 & buffer[1]) << 6);
    codepoint = codepoint + ((0b00001111 & buffer[0]) << 12);
    return codepoint;
}

short vconi_char_length(unsigned char val) {
    if (val < 128) {
        return 1;
    } else if (val < 224) {
        return 2;
    } else if (val < 240) {
        return 3;
    } else {
        return 4;
    }
}

/**
 *
 * @param number
 * @param ptr
 * @return
 */
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