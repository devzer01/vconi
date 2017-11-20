//
// Created by nayana on 19/11/2560.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "bitmap.h"

void *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; //our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data
    int imageIdx=0;  //image index counter
    unsigned char tempRGB;  //our swap variable

    //open filename in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    unsigned char *bfType = malloc(sizeof(unsigned char) * 2);
    unsigned short *bPtr = (unsigned short *) bfType;
    fread(bfType, sizeof(unsigned char), 2, filePtr);

    //verify that this is a bmp file by check bitmap id
    if (*bPtr != 0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

    printf("bitmap file type %ls \n", ((unsigned int *) bfType));


    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr); // small edit. forgot to add the closing bracket at sizeof

    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bOffBits, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc((size_t) bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage)
    {
        dprintf(2, "error allocating memory\n");
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }


    //read in the bitmap image data
    fread(bitmapImage, bitmapInfoHeader->biSizeImage, 1, filePtr);
    printf("bit map data size - %d \n", bitmapInfoHeader->biSizeImage);
    fclose(filePtr);
    //so now we have the image data in backwards lets set it properly
    //since we gonna spend time traversing it once lets try to make good use of it

    unsigned int iPerRow = ((bitmapInfoHeader->biBitCount * bitmapInfoHeader->biWidth) / (8 * 4));
    if (((bitmapInfoHeader->biBitCount * bitmapInfoHeader->biWidth) / (8 * 4)) > 0) iPerRow++;
    unsigned int widthInBytes =  iPerRow * 4;
    unsigned char *revptr = (unsigned char *) ((bitmapImage+bitmapInfoHeader->biSizeImage) - widthInBytes);
    struct bmp_px_row *root = malloc(sizeof(struct bmp_px_row));
    struct bmp_px_row *ptrRoot = root;
    unsigned long int row = 0;
    while(row < (bitmapInfoHeader->biHeight)) {
        root->row = row + 1;
        root->n_row_px = 0;
        root->bitmap_row = malloc(sizeof(unsigned char) * widthInBytes);
        memcpy(root->bitmap_row, revptr, widthInBytes);
        revptr = ((bitmapImage + bitmapInfoHeader->biSizeImage) - (widthInBytes * ++row));
        struct bmp_px_row *temp_row = malloc(sizeof(struct bmp_px_row));
        temp_row->top = root;
        root->bottom = temp_row;
        (root) = temp_row;
    }

   //now do stats
    root = ptrRoot;
    printf("image dimensions %d x %d\n", bitmapInfoHeader->biHeight, bitmapInfoHeader->biWidth);
    while(root->row < (bitmapInfoHeader->biHeight)) {
        u_int16_t v_count = 0;
        u_int64_t *pixGroup = (u_int64_t *) root->bitmap_row;
        //u_int64_t *ptr64 = (u_int64_t *) root->bitmap_row;
        //while (ptr64 != 0x0) printf("%" PRIu64 " ", (unsigned long) ptr64++);
        unsigned int column = 0;
        //uint64_t *pixGroup = (uint64_t *) ptrRowData;

        while(column < bitmapInfoHeader->biWidth) {
            column += 64;
            if (*pixGroup == 0) {
                pixGroup++;
                continue;
            }
            //*pixGroup = 0b1111111111000000011111100000000111;
            //printf("input - %ld ", *pixGroup);
            u_int64_t retval = bitcount(*pixGroup);
            root->n_row_px += retval;
            if (root->n_row_px > bitmapInfoHeader->biWidth) {
                int i = 8;
                printf("%llu =## ", retval);
                u_int64_t temp = *pixGroup;
                while (i > 0) {
                    printf(" %#0x ", (unsigned  char) (temp & 0xff));
                    temp = temp >> 8;
                    i--;
                }
                printf(" - row %d - iteration %d input %llu \n", root->n_row_px, column, *pixGroup);
            }
            //printf("return %d\n ", count);
             // += count;
                    //root->n_row_px += bitCount;
            pixGroup++;
        }
        printf("row %ld has %d / %d pixels on \n", root->row, root->n_row_px, column);
        (root) = root->bottom;
    }
}