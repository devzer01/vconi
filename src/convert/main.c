//
//  convert.c
//  compare
//
//  Created by Hettiarachchi, Nayana (Agoda) on 11/7/17.
//
//

#include "convert.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "vconi.h"
#include <stdint.h>
#include "charmap.h"

extern int ucdn_get_general_category(uint32_t code);
unsigned char lang = 0x00;
b8e_config *config;
b8e_map *map;
struct b8e_remap *remap;

int numberOfBytesInChar(unsigned char val) {
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

int forward(int fp, unsigned char **ob, long long allocsize)
{
    unsigned char ch = 0x0;
    unsigned char *ptch = &ch;
    unsigned int chars = 0;
    *ob = (unsigned char *) malloc(sizeof(unsigned char) * allocsize + (allocsize));
    remap = malloc(sizeof(struct b8e_remap));
    struct b8e_map_node *map_node = malloc(sizeof(struct b8e_map_node));
    while(0 != read(fp, ptch, 1)) {

        if (chars >= allocsize * 2.5) {
            dprintf(2, "out of memory\n");
            exit(-1);
        }

        int bytes = numberOfBytesInChar(ch);

        if (bytes == 1) {
            memcpy(*ob, &ch, 1);
            (*ob)++;
            chars++;
            continue;
        }
        unsigned char *buf = (unsigned char *) malloc(sizeof(unsigned char) * 3);
        *buf = ch;
        read(fp, buf+1, bytes - 1);
        int32_t codepoint = utf82codepoint(buf);
        const b8e_rec rec = codepoint2local(map, codepoint);
#if DEBUG
        dprintf(2, "%d - %d \n", rec.attributes, codepoint);
#endif
        if (rec.attributes != 0) {
            //add to map position and original code point index

            map_node->block = (chars / 64);
            map_node->offset = (chars % 64);
            map_node->b8e_char = rec.value;
            map_node->codepoint = codepoint;
            remap->node = map_node;
            remap->next = malloc(sizeof(struct b8e_map));
            remap->next->prev = (remap);
            (remap) = remap->next;
            map_node = malloc(sizeof(struct b8e_map_node));
        }
        if (rec.value != 0x00 && rec.value != 0xFF) {
            memcpy(*ob, &rec.value, 1);
            (*ob)++;
            chars++;
        } else {

        }
    }

    return chars;
}

int backward(int fp, unsigned char **ob, long long allocsize)
{
    unsigned char ch = 0x0;
    unsigned int chars = 0;
    unsigned char zwj[3] = {0xe2, 0x80, 0x8b};
    unsigned char *pzwj = (unsigned char *) &zwj;

    *ob = (unsigned char *) malloc(sizeof(unsigned char) * allocsize + (allocsize));
    if (remap != 0x0 && remap->node != 0x0) {
        dprintf(2, "found remap hash %d", remap->node->block);
    }
    int bchars = 0;
    while(0 != read(fp, &ch, 1)) {
        
        if (ch < 0x80 && ch != 0x2E) {
            memcpy((*ob), &ch, 1);
            (*ob)++;
            chars++;
            bchars++;
            continue;
        }

        if (ch == 0xFF) {
            continue;
        }

        int32_t codepoint = local2codepoint(map, ch);
        if (remap != 0x00 && remap->node->block == (bchars / 64) && remap->node->offset == (bchars % 64)) {
            codepoint = remap->node->codepoint;
            (remap) = remap->prev;
        }

        unsigned char *buff = (unsigned char *) malloc(sizeof(unsigned char) * 4);
        const unsigned char *key = (const unsigned  char *) getuchar(codepoint, buff);

        memcpy((*ob), key, 3);
        (*ob) += 3;
        chars += 3;
        bchars++;
        /*int cl = ucdn_get_general_category(codepoint);
        if (cl == 10 || cl == 12) {
            memcpy(*ob, pzwj, 3);
            *ob += 3;
            chars += 3;
        }*/
    }
    //remap->prev = 0x0;
    return chars;
}

int usage()
{
    printf(" -l language -d direction -f input -t output \n");
    return 0;
}

int get_language(unsigned char lang) {
    switch (lang) {
        case 0xF:
           return L_ODIA;
           break;
        case 0x1:
            return L_ASSAMESE;
            break;
        case 0x3:
            return L_BENGALI;
            break;
        case 0x6:
            return L_DEVANAGARI;
            break;
        case 0x7:
            return L_GUJARATI;
            break;
        case 0x8:
            return L_GURMUKHI;
            break;
        case 0x16:
            return L_TIBETAN;
            break;
        case 0x4:
            return L_BRAHMI;
            break;
        case 0x14:
            return L_TELUGU;
            break;
        case 0xA:
            return L_KANNADA;
            break;
        case 0x10:
            return L_SINHALA;
            break;
        case 0xE:
            return L_MALAYALAM;
            break;
        case 0x13:
            return L_TAMIL;
            break;
        case 0x5:
            return L_BURMESE;
            break;
        case 0xB:
            return L_KHMER;
            break;
        case 0x15:
           return L_THAI;
           break;
        case 0xC:
          return L_LAO;
          break;
        case 0x2:
            return L_BALINESE;
            break;
        case 0x9:
            return L_JAVANESE;
            break;
        case 0x11:
            return L_SUNDANESE;
            break;
        case 0xD:
            return L_LONTARA;
            break;
        default:
            map_print();
            exit(-1);
            break;
    }
    return -1;
}

int main(int argc, char **argv)
{
    int option = 0;
    unsigned char opt[4][2] = {"l:", "d:", "f:", "t:"};
    int optidx = 0;

    unsigned char direct = 0x00;
    unsigned char *sf = 0x00;
    unsigned char *of = 0x00;
    unsigned char number;

    while(-1 != (option = getopt(argc, argv, opt[optidx]))) {
        switch (*opt[optidx]) {
            case 'l':
                number = (unsigned char)strtol(optarg, NULL, 16);
                lang = get_language(number);
                break;
            case 'd':
                direct = *optarg;
                break;
            case 'f':
                sf = (unsigned char *) malloc(sizeof(unsigned char) * strlen(optarg));
                strcpy(sf, optarg);
                break;
            case 't':
                of = (unsigned char *) malloc(sizeof(unsigned char) * strlen(optarg));
                strcpy(of, optarg);
                break;
        }
        optidx++;
    }

    if (lang == 0x00 || sf == 0x00 || of == 0x00 || direct == 0x00 ) {
        dprintf(2, "required params l f t\n");
        exit(-1);
    }

    if (lang == -1) {
        dprintf(2, "language not supported yet\n");
        exit(-1);
    }

    int fp = open(sf, O_RDONLY);
    if (fp == -1) {
        dprintf(2, "unable to open %s \n", sf);
        exit(-1);
    }

    config = (b8e_config *) malloc(sizeof(b8e_config));
    map = map_init(config);
    map = map_load(config, lang, map);
    
    struct stat *statbuf = (struct stat *) malloc(sizeof(struct stat));
    fstat(fp, statbuf);
    long long allocsize = (statbuf->st_size);
    unsigned char *ob;
    int chars = 0;
    unsigned char *mapf;
    struct b8e_map_node *node;
    unsigned char *xbuf = malloc(sizeof(unsigned char) * 20);
    switch (direct){
        case 'f':
            allocsize = allocsize / 3 * 2.5;
            dprintf(2, "allocated %lld bytes for file %s \n", allocsize, sf);
            chars = forward(fp, &ob, allocsize);
            ob = (ob - chars);
            break;
        case 'b':
            mapf = malloc(sizeof(unsigned char *) * (strlen(sf) + 6));
            sprintf(mapf, "%s.map", sf);
            int mfp = open(mapf, O_RDONLY);
            if (mfp != -1) {
                dprintf(2, "found map file %d \n", sizeof(struct b8e_map_node));
                struct b8e_remap_header *hdxr = malloc(sizeof(struct b8e_remap_header));
                read(mfp, xbuf, sizeof(struct b8e_remap_header));
                memcpy(hdxr, xbuf, sizeof(struct b8e_remap_header));
                if (hdxr->lang == lang) {
                    node = malloc(sizeof(struct b8e_map_node));
                    remap = malloc(sizeof(struct b8e_remap));
                    struct b8e_remap *r = remap;
                    while (0 < read(mfp, xbuf, 16)) {
                        memcpy(node, xbuf, 16);
                        r->node = node;
                        r->next = malloc(sizeof(struct b8e_map));
                        r->next->prev = r;
                        (r) = r->next;
                        node = malloc(sizeof(struct b8e_map_node));
                    }
                    (remap) = r->prev;
                }
                //free(node); //the last allocation;
            }

            allocsize = allocsize * 6;
            dprintf(2, "allocated %lld bytes for file %s \n", allocsize, sf);
            chars = backward(fp, &ob, allocsize);
            dprintf(2, "%d bytes was written to buffer \n", chars);
            ob = (ob - chars);
            break;
    }

    close(fp);

    fp = open(of, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fp == -1) {
        dprintf(2, "error creating output file %s\n", of);
        exit(-1);
    }
    write(fp, ob, chars);
    close(fp);

    if (direct == 'f') {
        if (remap->prev != 0x00) {
            unsigned char *mapf = malloc(sizeof(unsigned char *) * strlen(of) + 6);
            sprintf(mapf, "%s.map", of);
            fp = open(mapf, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        }
        struct b8e_remap_header hdr;
        hdr.size=chars;
        hdr.lang=lang;
        write(fp, &hdr, sizeof(struct b8e_remap_header));
        while (remap->prev != 0x0) {
            (remap) = remap->prev;
            struct b8e_map_node n = *remap->node;
            write(fp, &n, sizeof(struct b8e_map_node));
        }
        if (fp != 0x0) {
            close(fp);
        }
    }
    
    return 0;
}