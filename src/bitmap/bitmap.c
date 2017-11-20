//
// Created by nayana on 19/11/2560.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

struct bmp_px_matrix *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader, bmp_px_matrix **base_node)
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

    unsigned int row, col, index = bitmapInfoHeader->biSizeImage;
    unsigned int iPerRow = ((bitmapInfoHeader->biBitCount * bitmapInfoHeader->biWidth) / (8 * 4));
    if (((bitmapInfoHeader->biBitCount * bitmapInfoHeader->biWidth) / (8 * 4)) > 0) iPerRow++;
    unsigned int rowSize =  iPerRow * 4;
    unsigned char *revptr = (unsigned char *) ((bitmapImage+bitmapInfoHeader->biSizeImage) - rowSize);
    unsigned char *rowData = malloc(sizeof(unsigned char) * rowSize);
    unsigned char *ptrRowData = rowData;
    signed int colSize = bitmapInfoHeader->biHeight;

    memcpy(rowData, revptr, rowSize);
    row = 0;
    struct bmp_px_matrix *matrix = *base_node;
    struct bmp_px_matrix *origin = matrix;
    //struct bmp_col_stat *lcol_stat = base_col;
    struct bmp_row_stat *lrow_stat = base_row;
    struct bmp_col_stat *lcol_stat;
    lrow_stat->npix = 0;
    for (int c = 0; c < colSize; c++) {
        lrow_stat->row = c;
        lrow_stat->base_col_stat = malloc(sizeof(struct bmp_col_stat));
        lcol_stat = lrow_stat->base_col_stat;
#if DEBUG
        printf("row %d ", c);
#endif
        for (int i = 0; i < rowSize; i++) {
            unsigned char mask = 0b10000000;
            for (int b = 0; b < 8; b++) {
                if (((i * 8) + b) >= bitmapInfoHeader->biWidth) continue;
                struct bmp_px *px = malloc(sizeof(struct bmp_px));
                px->row = c;
                px->col = (i * 8) + b;
                px->px = 0;
                lcol_stat->col = px->col;
                if (mask == (*rowData & mask)) {
                    px->px = 1;
                    lcol_stat->npix++;
                    lrow_stat->npix++;
                }

                if (matrix->right != 0x0) {
                    matrix->bottom = malloc(sizeof(struct bmp_px_matrix));
                    matrix->bottom->left = 0x0;
                    matrix->bottom->right = 0x0;
                    matrix->bottom->bottom = 0x0;
                    matrix->bottom->top = matrix;
                    matrix->bottom->px = px;

                } else if (matrix->right == 0x0) {
                    matrix->px = px;
                    matrix->right = malloc(sizeof(struct bmp_px_matrix));
                    matrix->right->left = matrix;
                    matrix->right->bottom = 0x0;
                    matrix->right->right = 0x0;
                }

                if (matrix->left != 0x0 && matrix->bottom != 0x0) {
                    matrix->bottom->left = matrix->left->bottom;
                    matrix->left->bottom->right = matrix->bottom;
                }

                lcol_stat->right = malloc(sizeof(struct bmp_col_stat));
                lcol_stat->right->left = lcol_stat;
                lcol_stat->right->npix = 0;


                (lcol_stat) = lcol_stat->right;
#if DEBUG
                printf("c %ld ", matrix->px->col);
#endif
                (matrix) = matrix->right;
                mask = mask >> 1;
            }
            rowData++;
        }
        if ((c + 1) != colSize) {
            revptr = ((bitmapImage + bitmapInfoHeader->biSizeImage) - rowSize * (c + 2));
            free(ptrRowData);
            rowData = malloc(sizeof(unsigned char) * rowSize);
            ptrRowData = rowData;
            memcpy(rowData, revptr, rowSize);

            if (c > 0 && (c % 2) == 1) {
                (origin) = origin->bottom;
            }

            (matrix) = origin;
        }
        //(lcol_stat) = base_col;
        lrow_stat->bottom = malloc(sizeof(struct bmp_row_stat));
        lrow_stat->bottom->top = lrow_stat;
        (lrow_stat) = lrow_stat->bottom;
        lrow_stat->npix = 0;
    }

    return base;
}