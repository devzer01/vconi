//
// Created by nayana on 11/11/17.
//
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#ifndef VCONI_CHARMAP_H
#define VCONI_CHARMAP_H
 /**
  *
  */
 typedef struct range {
     unsigned char bsize;
     int32_t mask;
     int32_t ch;
 } range;

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
void map_print();
#endif
//VCONI_CHARMAP_H
