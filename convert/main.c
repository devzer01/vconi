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

unsigned char lang = 0x00;

static const unsigned char beng[128] = {
    0x00,
    0xf0,
    0xf1,
    0xf2,
    0x00,
    0x80,
    0x88,
    0x82,
    0x8a,
    0x83,
    0x8b,
    0x84,
    0x85,
    0x00,
    0x00,
    0x86,
    0x8e,
    0x00,
    0x00,
    0x87,
    0x8f,
    0xb0,
    0xc0,
    0xb1,
    0xc1,
    0xbd,
    0xb2,
    0xc2,
    0xb3,
    0xc3,
    0xcd,
    0xb4,
    0xc4,
    0xb5,
    0xc5,
    0xc6,
    0xb7,
    0xc7,
    0xb8,
    0xc8,
    0xb6,
    0x00,
    0xb9,
    0xc9,
    0xba,
    0xca,
    0xe2,
    0xbf,
    0xbe,
    0x00,
    0xbb,
    0x00,
    0x00,
    0x00,
    0xcc,
    0xdc,
    0xbc,
    0xe1,
    0x00,
    0x00,
    0xf6,
    0xf8,
    0x98,
    0x92,
    0x9a,
    0x93,
    0x9b,
    0x94,
    0x9c,
    0x00,
    0x00,
    0x96,
    0x9e,
    0x00,
    0x00,
    0x97,
    0x9f,
    0xf5,
    0xb7,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x9f,
    0x00,
    0x00,
    0x00,
    0x00,
    0xde,
    0xce,
    0x00,
    0xdf,
    0x8c,
    0x8d,
    0x95,
    0x9d,
    0xf9,
    0xfa,
    0x30,
    0x31,
    0x32,
    0x33,
    0x34,
    0x35,
    0x36,
    0x37,
    0x38,
    0x39,
    0xbe,
    0xbe,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xf1,
    0x00,
    0x00,
    0x00
};

static const unsigned char deva[128] = {
    0xf7,
    0xf0,
    0xf1,
    0xf2,
    0x80,
    0x80,
    0x88,
    0x82,
    0x8a,
    0x83,
    0x8b,
    0x84,
    0x85,
    0xa6,
    0x86,
    0x86,
    0x8e,
    0xa7,
    0x87,
    0xa7,
    0x8f,
    0xb0,
    0xc0,
    0xb1,
    0xc1,
    0xbd,
    0xb2,
    0xc2,
    0xb3,
    0xc3,
    0xcd,
    0xb4,
    0xc4,
    0xb5,
    0xc5,
    0xc6,
    0xb7,
    0xc7,
    0xb8,
    0xc8,
    0xb6,
    0xb6,
    0xb9,
    0xc9,
    0xba,
    0xca,
    0xe2,
    0xbf,
    0xbe,
    0xde,
    0xbb,
    0xcb,
    0x00,
    0xe0,
    0xcc,
    0xdc,
    0xbc,
    0xe1,
    0x00,
    0x00,
    0xf6,
    0xf8,
    0x98,
    0x92,
    0x9a,
    0x93,
    0x9b,
    0x94,
    0x9c,
    0xae,
    0x96,
    0x96,
    0x9e,
    0xaf,
    0x97,
    0x97,
    0x9f,
    0xf5,
    0x96,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xae,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xd5,
    0x00,
    0x00,
    0xdf,
    0x8c,
    0x8d,
    0x95,
    0x9d,
    0xf9,
    0xfa,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};

static const unsigned char con[128] = {
    0x00,
    0x00,
    0xf1,
    0xf2,
    0x00,
    0x80,
    0x88,
    0x81,
    0x89,
    0x82,
    0x8a,
    0x83,
    0x8b,
    0x84,
    0x8c,
    0x85,
    0x8d,
    0x86,
    0xa6,
    0x81,
    0x87,
    0xa7,
    0x8f,
    0x00,
    0x00,
    0x00,
    0xb0,
    0xc0,
    0xb1,
    0xc1,
    0xbd,
    0xd1,
    0xb2,
    0xc2,
    0xb3,
    0xc3,
    0x00,
    0x00,
    0x00,
    0xb4,
    0xc4,
    0xb5,
    0xc5,
    0xc6,
    0xbd,
    0xb7,
    0xc7,
    0xb8,
    0xc8,
    0xb6,
    0x00,
    0x00,
    0xb9,
    0xc9,
    0xba,
    0xca,
    0xe2,
    0x00,
    0xbf,
    0xbe,
    0x00,
    0xbb,
    0x00,
    0x00,
    0xe0,
    0xcc,
    0xdc,
    0xbc,
    0xe1,
    0xcb,
    0x00,
    0x00,
    0x00,
    0x00,
    0xf5,
    0x00,
    0x00,
    0x00,
    0x00,
    0x91,
    0x99,
    0x99,
    0x92,
    0x9a,
    0x93,
    0x00,
    0x9b,
    0x00,
    0x94,
    0x96,
    0xae,
    0x9e,
    0x97,
    0xaf,
    0x9f,
    0x9f,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x9c,
    0x9d,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};


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
        }

    }
    return 0;
}

int forward(int fp, unsigned char *ob)
{
    unsigned char ch = 0x0;
    unsigned int chars = 0;
    while(0 != read(fp, &ch, 1)) {
        int bytes = numberOfBytesInChar(ch);
        
        if (bytes == 1) {
            memcpy(ob++, &ch, 1);
            chars++;
            continue;
        }
        
        if (ch == 0xe0) {
            unsigned char *buf = (unsigned char *) malloc(sizeof(unsigned char) * bytes);
            read(fp, buf, bytes - 1);
            unsigned char idx = 0;
            unsigned char obx = 0;
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
                memcpy(ob++, &obx, 1);
                chars++;
            } else {
                dprintf(2, "error at char %d index %d from range %#02x %#02x\n", chars, idx, ch, buf[0]);
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
    }

    while(0 != read(fp, &ch, 1)) {
        
        if (ch < 0x80) {
            memcpy(ob++, &ch, 1);
            chars++;
            continue;
        }
        
        buff[0] = 0xe0;
        buff[1] = b11;
        buff[2] = charindex(ch);
        if (buff[2] > 0x40) {
            buff[2] -= 0x40;
            buff[1] = b12;
        }
        buff[2] += 0x80;
        
        //    if (buff[2] != 0) {
                memcpy(ob, &buff, 3);
                ob += 3;
                chars++;
          //  } else {
            //    dprintf(2, "error at char %d index %d from range %#02x %#02x\n", chars, buff[2], ch, buff[1]);
                //write(2, errmsg, strlen(errmsg));
            //}
    }
    
    return chars;
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
    long long allocsize = (statbuf->st_size * 3);
    dprintf(2, "allocated %lld bytes for file %s \n", allocsize, sf);
    unsigned char *ob = (unsigned char *) malloc(sizeof(char) * allocsize);
    unsigned char *ptrob = ob;

    int chars = 0;

    switch (direct){
        case 'f':
            chars = forward(fp, ob);
            break;
        case 'b':
            chars = backward(fp, ob);
            break;
    }

    close(fp);
    
    fp = open(of, O_WRONLY | O_CREAT | S_IRWXU );
    if (fp == -1) {
        dprintf(2, "error creating output file %s\n", of);
        exit(-1);
    }
    write(fp, ptrob, chars);
    close(fp);
    
    return 0;
}