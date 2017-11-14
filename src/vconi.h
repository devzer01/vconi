//
// Created by nayana on 11/10/17.
// //https://stackoverflow.com/questions/1675351/typedef-struct-vs-struct-definitions
//
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "lang/sinhala.h"
#include "lang/devanagari.h"
#include "lang/bengali.h"
#include "lang/tamil.h"
#include "lang/malayalam.h"

#ifndef VCONI_VCONI_H
#define VCONI_VCONI_H

/**
 *
 */
typedef struct range {
    unsigned char bsize;
    int32_t mask;
    int32_t ch;
} range;

typedef struct b8e_config {
    const unsigned char *sinhala;
    const unsigned char *devanagari;
    const unsigned char *bengali;
    const unsigned char *tamil;
    const unsigned char *malayalam;
} b8e_config;


#define CONSEQ_CHAR  0b10000000
#define NCONSEQ_CHAR 0b00111111

/**
 *
 * @param buffer
 * @return
 */
int32_t utf82codepoint(unsigned char *buffer);

/**
 *
 * @param number
 * @param ptr
 * @return
 */
range *getcodeparams(int32_t number, range *ptr);

/**
 *
 * @param codepoint
 * @param buf
 * @return
 */
unsigned char *getuchar(int32_t codepoint, unsigned char *buf);






#endif //VCONI_VCONI_H