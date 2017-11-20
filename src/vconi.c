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

int32_t vconi_utf82codepoint(unsigned char *buffer, short length) {
    if (length == 1) {
        return (int32_t) 0b01111111 & buffer[0];
    } else {
        return utf82codepoint(buffer);
    }
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
    ptr = getcodeparams(codepoint, ptr);
    buf = malloc(sizeof(unsigned char) * ptr->bsize);
    int loop = ptr->bsize;
    while (0 <= --loop) {
        unsigned char ch = (ptr->mask & 0xff) + (codepoint & (ptr->ch & 0xff));
        memcpy((buf+loop), &ch, 1);
        codepoint = codepoint >> 6;
        ptr->mask = ptr->mask >> 8;
        ptr->ch = ptr->ch >> 8;
    }
    return buf;
}