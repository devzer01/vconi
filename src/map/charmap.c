//
// Created by nayana on 11/11/17.
//

#include "charmap_gen.h"
#include "charmap.h"

#include "lang/odia.h"
#include "lang/assamese.h"
#include "lang/bengali.h"
#include "lang/devanagari.h"
#include "lang/gujarati.h"
#include "lang/gurmukhi.h"
#include "lang/tibetan.h"
#include "lang/brahmi.h"
#include "lang/telugu.h"
#include "lang/kannada.h"
#include "lang/sinhala.h"
#include "lang/malayalam.h"
#include "lang/tamil.h"
#include "lang/burmese.h"
#include "lang/khmer.h"
#include "lang/thai.h"
#include "lang/lao.h"
#include "lang/balinese.h"
#include "lang/javanese.h"
#include "lang/sundanese.h"
#include "lang/lontara.h"


void map_print()
{
    printf("0xF	Odia\n0x1 Assamese\n0x3	Bengali\n0x6 Devanagari\n0x7 Gujarati\n");
    printf("0x8	Gurmukhi\n0x16 Tibetan\n0x4	Brahmi\n0x14 Telugu\n0xA Kannada\n");
    printf("0x10 Sinhala\n0xE Malayalam\n0x13 Tamil\n0x5 Burmese\n0xB Khmer\n");
    printf("0x15 Thai\n0xC	Lao\n0x2 Balinese\n0x9	Javanese\n0x11 Sundanese\n0XD Lontara\n");
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

b8e_map *map_init(b8e_config *config) {
	b8e_map *map = (b8e_map *) malloc(sizeof(b8e_map));
	config->odia = (const unsigned char *) &odi_config;
	config->assamese = (const unsigned char *) &asm_config;
	config->bengali = (const unsigned char *) &ben_config;
	config->devanagari = (const unsigned char *) &dev_config;
	config->gujarati = (const unsigned char *) &guj_config;
	config->gurmukhi = (const unsigned char *) &gur_config;
	config->tibetan = (const unsigned char *) &tib_config;
	config->brahmi = (const unsigned char *) &bra_config;
	config->telugu = (const unsigned char *) &tlg_config;
	config->kannada = (const unsigned char *) &kan_config;
	config->sinhala = (const unsigned char *) &sin_config;
	config->malayalam = (const unsigned char *) &mal_config;
	config->tamil = (const unsigned char *) &tam_config;
	config->burmese = (const unsigned char *) &bur_config;
	config->khmer = (const unsigned char *) &khm_config;
	config->thai = (const unsigned char *) &thi_config;
	config->lao = (const unsigned char *) &lao_config;
	config->balinese = (const unsigned char *) &bal_config;
	config->javanese = (const unsigned char *) &jav_config;
	config->sundanese = (const unsigned char *) &sud_config;
	config->lontara = (const unsigned char *) &lon_config;
};

b8e_map *map_load(b8e_config *config, LANGUAGE lang, b8e_map *map) {
	switch (lang) {
		case L_BASE:
			break;
		case L_ODIA:
			map = map_parse(config->odia, map);
			break;
		case L_ASSAMESE:
			map = map_parse(config->assamese, map);
			break;
		case L_BENGALI:
			map = map_parse(config->bengali, map);
			break;
		case L_DEVANAGARI:
			map = map_parse(config->devanagari, map);
			break;
		case L_GUJARATI:
			map = map_parse(config->gujarati, map);
			break;
		case L_GURMUKHI:
			map = map_parse(config->gurmukhi, map);
			break;
		case L_TIBETAN:
			map = map_parse(config->tibetan, map);
			break;
		case L_BRAHMI:
			map = map_parse(config->brahmi, map);
			break;
		case L_TELUGU:
			map = map_parse(config->telugu, map);
			break;
		case L_KANNADA:
			map = map_parse(config->kannada, map);
			break;
		case L_SINHALA:
			map = map_parse(config->sinhala, map);
			break;
		case L_MALAYALAM:
			map = map_parse(config->malayalam, map);
			break;
		case L_TAMIL:
			map = map_parse(config->tamil, map);
			break;
		case L_BURMESE:
			map = map_parse(config->burmese, map);
			break;
		case L_KHMER:
			map = map_parse(config->khmer, map);
			break;
		case L_THAI:
			map = map_parse(config->thai, map);
			break;
		case L_LAO:
			map = map_parse(config->lao, map);
			break;
		case L_BALINESE:
			map = map_parse(config->balinese, map);
			break;
		case L_JAVANESE:
			map = map_parse(config->javanese, map);
			break;
		case L_SUNDANESE:
			map = map_parse(config->sundanese, map);
			break;
		case L_LONTARA:
			map = map_parse(config->lontara, map);
			break;
	}
	return map;
}