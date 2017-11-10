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
#include "tamil.h"
#include "bengali.h"
#include "devangari.h"
#include "sinhala.h"

unsigned char lang = 0x00;
extern int ucdn_get_general_category(uint32_t code);

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

int charindex(unsigned char ch) {
    for (int idx = 0 ; idx < 128; idx++) {
        switch (lang) {
            case 'd':
                if (deva[idx] == ch) return idx;
                break;
            case 'b':
                if (beng[idx] == ch) return idx;
                break;
            case 's':
                if (con[idx] == ch) return idx;
                break;
        }

    }
    return 0;
}

int forward(int fp, unsigned char **ob, long long allocsize)
{
    unsigned char ch = 0x0;
    unsigned char *ptch = &ch;
    unsigned int chars = 0;
    *ob = (unsigned char *) malloc(sizeof(unsigned char) * allocsize + (allocsize));

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
        if (ch == 0xe0) {
            read(fp, buf, bytes - 1);
            unsigned char idx = 0;
            unsigned char obx = 0x00;
            unsigned char *pt = &obx;
            switch (buf[0]) {
                case 0xb6:
                case 0xa6:
                case 0xa4:
                    idx = buf[1] - 0x80;
                    break;
                case 0xa5:
                case 0xa7:
                case 0xb7:
                    idx = buf[1] - 0x40;
                    break;
            }
            switch (buf[0]) {
                case 0xa4:
                case 0xa5:
                    obx = deva[idx];
                    break;
                case 0xa6:
                case 0xa7:
                    obx = beng[idx];
                    break;
                case 0xb6:
                case 0xb7:
                    obx = con[idx];
                    break;
            }
            
            if (obx != 0x00) {
                memcpy(*ob, pt, 1);
                (*ob)++;
                chars++;
            } else {
                dprintf(2, "error at char %d index %d from range %#02x %#02x %#02x \n", chars, idx, ch, buf[0], buf[1]);
                //write(2, errmsg, strlen(errmsg));
            }
        } else if (ch == 0xe2) {
            unsigned char *buf = (unsigned char *) malloc(sizeof(unsigned char) * bytes);
            read(fp, buf, bytes - 1);
            dprintf(2, "skip zwj at %d\n", chars);
        } else {
            dprintf(2, "char: %d out of range char %#02x\n", chars, ch);
        }
    }
    
    return chars;
}

int backward(int fp, unsigned char *ob)
{
    unsigned char ch = 0x0;
    unsigned int chars = 0;
    unsigned char buff[3] = {0x00, 0x00, 0x00};

    unsigned char b11 = 0x00;
    unsigned char b12 = 0x00;

    switch (lang) {
        case 'd':
            b11 = 0xa4;
            b12 = 0xa5;
            break;
        case 'b':
            b11 = 0xa6;
            b12 = 0xa7;
            break;
        case 's':
            b11 = 0xb6;
            b12 = 0xb7;
            break;
    }

    while(0 != read(fp, &ch, 1)) {
        
        if (ch < 0x80) {
            memcpy(ob++, &ch, 1);
            chars++;
            continue;
        }
        //dprintf(2, "%#02x ", ch);
        buff[0] = 0xe0;
        buff[1] = b11;
        buff[2] = charindex(ch);
        if (buff[2] > 0x3f) {
            buff[2] -= 0x40;
            buff[1] = b12;
        }
        buff[2] += 0x80;
        memcpy(ob, &buff, 3);
        ob += 3;
        chars += 3;
        int32_t codepoint = getCodePoint((unsigned  char *) &buff);
        int cl = ucdn_get_general_category(codepoint);
        if (cl == 10 || cl == 12) {
            unsigned char *line = (unsigned char *) malloc(sizeof(unsigned char) * 3);
            sprintf(line, "%c%c%c", 0xe2, 0x80, 0x8b); //0xE2 0x80 0x8B
            memcpy(ob,line, 3);
            ob += 3;
            chars += 3;

        }
    }
    
    return chars;
}

int usage()
{
    printf(" -l language -d direction -f input -t output \n");
    return 0;
}

int main(int argc, char **argv)
{
    int option = 0;
    unsigned char opt[4][2] = {"l:", "d:", "f:", "t:"};
    int optidx = 0;

    unsigned char direct = 0x00;
    unsigned char *sf = 0x00;
    unsigned char *of = 0x00;

    while(-1 != (option = getopt(argc, argv, opt[optidx]))) {
        switch (*opt[optidx]) {
            case 'l':
                lang = *optarg;
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

    int fp = open(sf, O_RDONLY);
    if (fp == -1) {
        dprintf(2, "unable to open %s \n", sf);
        exit(-1);
    }
    
    struct stat *statbuf = (struct stat *) malloc(sizeof(struct stat));
    fstat(fp, statbuf);
    long long allocsize = (statbuf->st_size);
    unsigned char *ob;
    int chars = 0;

    switch (direct){
        case 'f':
            allocsize = allocsize / 3 * 2.5;
            dprintf(2, "allocated %lld bytes for file %s \n", allocsize, sf);
            chars = forward(fp, &ob, allocsize);
            ob = (ob - chars);
            break;
        case 'b':
            allocsize = allocsize * 3;
            dprintf(2, "allocated %lld bytes for file %s \n", allocsize, sf);
            ob = (unsigned char *) malloc(sizeof(unsigned char ) * allocsize);
            chars = backward(fp, ob);
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
    
    return 0;
}