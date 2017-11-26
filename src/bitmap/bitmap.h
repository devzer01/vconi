//
// Created by nayana on 19/11/2560.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
    unsigned short n_row_px;
    struct bmp_px_row *top;
    struct bmp_px_row *left;
    struct bmp_px_row *right;
    struct bmp_px_row *bottom;
} bmp_px_row ;

typedef struct ocr_row {
    unsigned int start;
    unsigned int end;
    struct ocr_row *prev;
    struct ocr_row *next;
    struct bmp_px_row *row;
    struct ocr_cell *first_cell;
} ocr_row;

typedef struct ocr_cell {
    signed long int start;
    signed long int end;
    unsigned long int r_start;
    unsigned long int r_end;
    struct ocr_cell *prev;
    struct ocr_cell *next;
    struct ocr_cell *first;
    struct ocr_cell *last;
    short index;
} ocr_cell;


/*typedef struct ocr_char_cell {

};*/

//struct bmp_px_matrix *base;
//struct bmp_col_stat *base_col;
//struct bmp_row_stat *base_row;

struct bmp_px_row *root; // = malloc(sizeof(struct bmp_px_row));
struct bmp_px_row *ptrRoot; // = root;

BITMAPFILEHEADER *fileHeader;
BITMAPINFOHEADER *infoHeader;
typedef struct bmp_io_t {
    int fd;
    off_t len;
    int width;
    unsigned int byte_width;
    unsigned long int bi_width;
    int height;
    int b_height;
    int size;
    unsigned char *data;
    unsigned int *pixels;
    unsigned int **uc_cursor;
    u_int64_t *ui64_cursor;
    unsigned int *n_rpx; //pixel count
    unsigned int **ptr_cols;
    unsigned int **ptr_rows;
    struct ocr_cell **root_cell;
} bmp_io_t, *ptr_bmp_io;
ptr_bmp_io bmp_io;


struct ocr_row *ocr_row_root; // = malloc(sizeof(struct ocr_row));
struct ocr_row *or_root; // = ocr_row_root;
unsigned long bmp_row_offset(unsigned long int row);

unsigned int __bit2index(unsigned long int _bitcol);
unsigned char __col2mask(unsigned long int _bitcol);
short bmp_px(unsigned long int row, unsigned long int col);
void *bmp_init();
void *bmp_alloc();
void bmp_draw_row(unsigned int **matrix, unsigned int row, unsigned int width, unsigned long int px_width);
void *bmp_open(const char *filename);
void *bmp_row(unsigned long int row);
unsigned int bmp_row_bit_count(unsigned long int row);
struct ocr_cell *bmp_stat(struct ocr_cell *cell);
void *bmp_flipw(void *mem, void *mask);
struct ocr_cell *bmp_cell_init(struct ocr_cell *prev);
struct ocr_cell *bmp_row_stat(struct ocr_cell *root);
struct ocr_cell *bmp_col_stat(unsigned long int row, unsigned long int col, unsigned long int height, struct ocr_cell *cell);
//int drawchar(int row_start, int row_end, int col_start, int col_end, struct bmp_px_matrix **xbase);
unsigned int **bmp_init_matrix(unsigned int *pixels, unsigned int rows, unsigned int width);
unsigned int bmp_edge_mask(unsigned long int px_width);
extern unsigned short bmp_bitcount(uint64_t group);
extern unsigned short bmp_bcount32(uint32_t group);
extern unsigned short bmp_flip(void *p1, void *p2);
#endif //CODE_BITMAP_H

