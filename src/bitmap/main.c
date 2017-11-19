//
// Created by nayana on 19/11/2560.
//

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

int main() {
    BITMAPINFOHEADER bitmapInfoHeader;
    unsigned char *bitmapData;
    bitmapData = LoadBitmapFile("data/bitmap/sample.bmp", &bitmapInfoHeader);
    //now do what you want with it, later on i will show you how to display it in a normal window
    if (bitmapData == NULL) {
        dprintf(2, "error opening file\n");
        exit(-1);
    }
    printf("bitmap info bit count %hd \n", bitmapInfoHeader.biBitCount);

}