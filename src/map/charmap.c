//
// Created by nayana on 11/11/17.
//

#include "charmap.h"
#include "vconi.h"

b8e_map *map_init(b8e_config *config) {
    b8e_map *map = (b8e_map *) malloc(sizeof(b8e_map));
    config->sinhala = (const unsigned char *) &si_config;
    config->devanagari = (const unsigned char *) &dv_config;
    config->bengali = (const unsigned char *) &bn_config;
    config->tamil = (const unsigned char *) &tm_config;
    config->malayalam = (const unsigned char *) &ml_config;
}

b8e_map *map_load(b8e_config *config, LANGUAGE lang, b8e_map *map) {

    switch (lang) {
        case L_BASE:
            break;
        case L_SINHALA:
            map = map_parse(config->sinhala, map);
            break;
        case L_TAMIL:
            map = map_parse(config->tamil, map);
            break;
        case L_DEVANAGARI:
            map = map_parse(config->devanagari, map);
            break;
        case L_BENGALI:
            map = map_parse(config->bengali, map);
            break;
        case L_MALAYALAM:
            map = map_parse(config->malayalam, map);
            break;
    }
    return map;
}

const b8e_rec map_item(b8e_map *map, unsigned char index) {
    const b8e_rec rec = map->code[index];
    return rec;
}

const b8e_rec codepoint2local(b8e_map *map, int32_t codepoint) {
    unsigned char index = codepoint & 0x00FF;
    int i = 0;
    for (i = 0; i < 128; i++) {
        if (map->code[i].codepoint == index) {
            break;
        }
    }
    const b8e_rec rec = map->code[i];
    return rec;
}

int32_t local2codepoint(b8e_map *map, unsigned char local) {
    int i = 0;
    for (i = 0; i < 128; i++) {
        if (map->code[i].value == local) {
            break;
        }
    }
    const b8e_rec rec = map->code[i];
    return (int32_t) (map->start[0] << 8) + rec.codepoint;
}

b8e_map *map_parse(const unsigned char *map_data, b8e_map *map)
{
    map = (b8e_map *) map_data;
    return map;
}