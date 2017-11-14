//
// Created by nayana on 11/11/17.
//

#include "vconi.h"

#ifndef VCONI_CHARMAP_H
#define VCONI_CHARMAP_H

typedef struct b8e_rec {
    unsigned char value;
    unsigned char codepoint;
    unsigned short attributes;
} b8e_rec;

typedef struct b8e_map {
    unsigned char start[2];
    unsigned char end[2];
    b8e_rec code[128];
} b8e_map;

typedef unsigned char LANGUAGE;

enum langs { L_BASE, L_BRAHMIN, L_GRANTHA, L_DEVANAGARI, L_BENGALI, L_SINHALA, L_TAMIL, L_MALAYALAM }; //set this based on order in history

const b8e_rec map_item(b8e_map *map, unsigned char index);

b8e_map *map_init(b8e_config *config);

b8e_map *map_load(b8e_config *config, LANGUAGE lang, b8e_map *map);

b8e_map *map_parse(const unsigned char *map_data, b8e_map *map);

const b8e_rec  codepoint2local(b8e_map *map, int32_t codepoint);
int32_t local2codepoint(b8e_map *map, unsigned char local);
#endif //VCONI_CHARMAP_H
