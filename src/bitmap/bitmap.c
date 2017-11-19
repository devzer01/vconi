//
// Created by nayana on 19/11/2560.
//

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
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

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

    printf("bitmap file type %#04x \n", bitmapFileHeader.bfType);
    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

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
    //make sure bitmap image data was read

    //swap the r and b values to get RGB (bitmap is BGR)
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3) // fixed semicolon
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    //close file and return bitmap iamge data
    fclose(filePtr);
    return bitmapImage;
}