//
// Created by nayana on 11/6/17.
//

#include "convert.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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

int main(int argc, char **argv)
{
    unsigned char *sf = argv[1];
    int fp = open(sf, O_RDONLY);
    struct stat *statbuf = (struct stat *) malloc(sizeof(struct stat));
    fstat(fp, statbuf);
    unsigned char *ob = (char *) malloc(sizeof(char) * statbuf->st_size / 3);
    unsigned char *ptrob = ob;
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
    write(1, ptrob, chars);
    return 1;
}

/*
int main(){
    FILE *fin;
    FILE *fout;
    int character;
    fin = fopen("in.txt", "r");
    fout = fopen("out.txt","w");
    while( (character = fgetc(fin)) != EOF) {
        for (int i = 0; i < numberOfBytesInChar((unsigned char)character) - 1; i++) {
            putchar(character);
            fprintf(fout, "%c", character);
            character = fgetc(fin);
        }
        putchar(character);
        printf(" ");
        fprintf(fout, "%c ", character);
    }
    fclose(fin);
    fclose(fout);
    printf("\nFile has been created...\n");
    return 0;
}*/
