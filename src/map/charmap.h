//
// Created by nayana on 11/11/17.
//
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#ifndef VCONI_CHARMAP_H
#define VCONI_CHARMAP_H

typedef unsigned char LANGUAGE;

enum langs { L_BASE, L_ODIA,
                     L_ASSAMESE,
                     L_BENGALI,
                     L_DEVANAGARI,
                     L_GUJARATI,
                     L_GURMUKHI,
                     L_TIBETAN,
                     L_BRAHMI,
                     L_TELUGU,
                     L_KANNADA,
                     L_SINHALA,
                     L_MALAYALAM,
                     L_TAMIL,
                     L_BURMESE,
                     L_KHMER,
                     L_THAI,
                     L_LAO,
                     L_BALINESE,
                     L_JAVANESE,
                     L_SUNDANESE,
                     L_LONTARA
 }; //set this based on order in history

typedef struct b8e_config {
	const unsigned char *odia;
	const unsigned char *assamese;
	const unsigned char *bengali;
	const unsigned char *devanagari;
	const unsigned char *gujarati;
	const unsigned char *gurmukhi;
	const unsigned char *tibetan;
	const unsigned char *brahmi;
	const unsigned char *telugu;
	const unsigned char *kannada;
	const unsigned char *sinhala;
	const unsigned char *malayalam;
	const unsigned char *tamil;
	const unsigned char *burmese;
	const unsigned char *khmer;
	const unsigned char *thai;
	const unsigned char *lao;
	const unsigned char *balinese;
	const unsigned char *javanese;
	const unsigned char *sundanese;
	const unsigned char *lontara;
} b8e_config;

typedef struct b8e_rec {
    unsigned char value;
    unsigned char codepoint;
    unsigned short attributes;
} b8e_rec;

typedef struct b8e_map {
    unsigned char start[2];
    unsigned char size;
    unsigned char version;
    b8e_rec code[128];
} b8e_map;


b8e_map *map_parse(const unsigned char *map_data, b8e_map *map);

b8e_map *map_load(b8e_config *config, LANGUAGE lang, b8e_map *map);

b8e_map *map_init(b8e_config *config);

const b8e_rec map_item(b8e_map *map, unsigned char index);

const b8e_rec codepoint2local(b8e_map *map, int32_t codepoint);

int32_t local2codepoint(b8e_map *map, unsigned char local);

void map_print();
#endif
//VCONI_CHARMAP_H
