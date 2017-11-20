//
// Created by nayana on 19/11/2560.
//

#ifndef CODE_BITMAP_H
#define CODE_BITMAP_H

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned long LONG;

typedef struct tagBITMAPFILEHEADER
{
    //unsigned short bfType;  //specifies the file type
    unsigned int bfSize;  //specifies the size in bytes of the bitmap file
    unsigned int bfReserved1;  //reserved; must be 0
    unsigned int bOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    unsigned int biSize;  //specifies the number of bytes required by the struct
    unsigned int biWidth;  //specifies width in pixels
    unsigned int biHeight;  //species height in pixels
    unsigned short biPlanes; //specifies the number of color planes, must be 1
    unsigned short biBitCount; //specifies the number of bit per pixel
    unsigned int biCompression;//spcifies the type of compression
    unsigned int biSizeImage;  //size of image in bytes
    int biXPelsPerMeter;  //number of pixels per meter in x axis
    int biYPelsPerMeter;  //number of pixels per meter in y axis
    unsigned int biClrUsed;  //number of colors used by th ebitmap
    unsigned int biClrImportant;  //number of colors that are important
    unsigned char prof[4];
    unsigned char rest[64];
}BITMAPINFOHEADER;


typedef struct bmp_px_row {
    unsigned char *bitmap_row;
    unsigned long int row;
    unsigned int n_row_px;
    struct bmp_px_row *top;
    struct bmp_px_row *left;
    struct bmp_px_row *right;
    struct bmp_px_row *bottom;
} bmp_px_row ;

typedef struct bmp_px_gap {
    unsigned int start;
    unsigned int end;
    struct bmp_px_gap *prev;
    struct bmp_px_gap *next;
    struct bmp_px_row *row;
};



/*typedef struct ocr_char_cell {

};*/

struct bmp_px_matrix *base;
//struct bmp_col_stat *base_col;
struct bmp_row_stat *base_row;

struct bmp_px_matrix *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader, bmp_px_matrix **base_node);
int drawchar(int row_start, int row_end, int col_start, int col_end, struct bmp_px_matrix **xbase);

#endif //CODE_BITMAP_H
