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

    root = malloc(sizeof(struct bmp_px_row));
    ptrRoot = root;
    root->row = 1;
    root->n_row_px = 0;
    root->top = 0x0;
    unsigned long int row = 0;

    while(row < (bitmapInfoHeader->biHeight)) {
        root->bitmap_row = malloc(sizeof(unsigned char) * widthInBytes);
        memcpy(root->bitmap_row, revptr, widthInBytes);
        revptr = ((bitmapImage + bitmapInfoHeader->biSizeImage) - (widthInBytes * ++row));
        struct bmp_px_row *temp_row = malloc(sizeof(struct bmp_px_row));
        temp_row->row = root->row + 1;
        temp_row->n_row_px = 0;
        temp_row->top = root;
        root->bottom = temp_row;
        (root) = temp_row;
    }

   //now do stats
    root = ptrRoot;
    ocr_row_root = malloc(sizeof(struct ocr_row));
    or_root = ocr_row_root;
    or_root->start = 0;
    unsigned int column = 0;
    printf("image dimensions %d x %d\n", bitmapInfoHeader->biHeight, bitmapInfoHeader->biWidth);
    while(root->row < (bitmapInfoHeader->biHeight)) {
        u_int64_t *pixGroup = (u_int64_t *) root->bitmap_row;
        while(column < bitmapInfoHeader->biWidth) {
            column += 64;
            if (*pixGroup == 0) {
            } else {
                root->n_row_px += bitcount(*pixGroup);
            }
            pixGroup++;
        }
        if (root->row > 1 && root->row < bitmapInfoHeader->biHeight) {
            if(root->top->n_row_px == 0 && root->n_row_px != 0) {
                or_root->start = root->row;
                or_root->row = root;
            } else if (root->top->n_row_px != 0 && root->n_row_px == 0 && or_root->start != 0) {
                or_root->end = root->row;
                or_root->next = malloc(sizeof(struct ocr_row));
                or_root->next->prev = or_root;
                (or_root) = or_root->next;
                or_root->next = 0;
            }
        }
        (root) = root->bottom;
        column = 0;
    }
    //printf("row %ld has %d / %d pixels on \n", root->row, root->n_row_px, column);
    or_root = ocr_row_root;
    struct ocr_cell *or_cell = malloc(sizeof(struct ocr_cell));
    or_root->first_cell = or_cell;
    int last_col_px_count = 0;
    int col_px_count = 0;
    //now we go look for char cell breaks
    while (or_root != 0) {
        unsigned int byteIndex = 0;
        unsigned char mask = 0b10000000;
        column = 1;
        last_col_px_count = 0;
        col_px_count = 0;
        while (column <= bitmapInfoHeader->biWidth) {
            while (mask > 0) {
                struct bmp_px_row *bmp_row = or_root->row;
                int height = or_root->end - or_root->start;
                while (height > 0) {
                    if ((bmp_row->bitmap_row[byteIndex] & mask) == mask) {
                        col_px_count++;
                    }
                    (bmp_row) = bmp_row->bottom;
                    height--;
                }
                if (column > 1) {
                    if (col_px_count != 0 && last_col_px_count == 0) {
                        or_cell->start = column;
                        or_cell->or_row = or_root;
                    } else if (last_col_px_count != 0 && col_px_count == 0) {
                        or_cell->end = column;
                        or_cell->next = malloc(sizeof(struct ocr_cell));
                        or_cell->next->prev = or_cell;
                        (or_cell) = or_cell->next;
                        or_cell->next = 0;
                    }
                }
                last_col_px_count = col_px_count;
                col_px_count = 0;
                column++;
                mask = mask >> 1;
            }
            byteIndex++;
            mask = 0b10000000;
        }
        if (or_root->next != 0) {
            (or_root) = or_root->next;
            or_cell = malloc(sizeof(struct ocr_cell));
            or_root->first_cell = or_cell;
        } else {
            or_root = 0;
        }
    }

    or_root = ocr_row_root;
    /*printf("cell breakdown \n");
    int scanning = 1;
    while (scanning == 1) {

        (or_cell) = or_root->first_cell;

        while (or_cell != 0x0 && or_cell->next->start > or_cell->end) {
            printf(" (%d,%d) - (%d,%d) ", or_cell->or_row->start, or_cell->start, or_cell->or_row->end,
                   or_cell->end);
            (or_cell) = or_cell->next;
        }

        printf("\n");
        (or_root) = or_root->next;
        if (or_root->start < or_root->prev->end) {
            scanning = 0;
        }
    }*/
}