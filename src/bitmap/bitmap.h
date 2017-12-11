//
// Created by nayana on 19/11/2560.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "stats.h"

#ifndef CODE_BITMAP_H
#define CODE_BITMAP_H

#define PX_FIRST 0x80000000
#define PX_LAST

#define MAX_SHAPE_WIDTH 16
#define MAX_SHAPE_HEIGHT 16

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned long LONG;

typedef struct tagBITMAPFILEHEADER
{
    //unsigned short bfType;  //specifies the file type
    unsigned int bfSize;  //specifies the size in bytes of the bitmap file
    unsigned int bfReserved1;  //reserved; must be 0
    unsigned int bOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap px
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    unsigned int biSize;  //specifies the number of bytes required by the struct
    unsigned int biWidth;  //specifies width in bmp_data
    unsigned int biHeight;  //species height in bmp_data
    unsigned short biPlanes; //specifies the number of color planes, must be 1
    unsigned short biBitCount; //specifies the number of bit per pixel
    unsigned int biCompression;//spcifies the type of compression
    unsigned int biSizeImage;  //size of image in bytes
    int biXPelsPerMeter;  //number of bmp_data per meter in x axis
    int biYPelsPerMeter;  //number of bmp_data per meter in y axis
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

typedef struct bmp_dimension {
    unsigned long int height;
    unsigned long int width;
} bmp_dimension;

typedef struct bmp_header_t {
    unsigned int offset;
    unsigned int size;
}bmp_header, *ptr_bmp_header;

typedef struct bmp_io_t {
    int fd;
    const char *filename;
    bmp_header header;
    off_t len;
    struct bmp_dimension px;
    struct bmp_dimension chars;
    struct bmp_dimension ints;
    int bit_per_px;
    unsigned char *data;
    unsigned int *bmp_data;
    unsigned int *row_px_count;
    unsigned int *col_px_count;
    struct ocr_cell *root_cell;
} bmp_io_t, *ptr_bmp_io;
ptr_bmp_io bmp_io;

typedef struct shape_t {
    unsigned char buf[MAX_SHAPE_HEIGHT][MAX_SHAPE_WIDTH];
    unsigned short mask[MAX_SHAPE_HEIGHT];
} shape, *ptr_shape;

unsigned int *bmp_row_addr(unsigned long int row);
struct ocr_row *ocr_row_root; // = malloc(sizeof(struct ocr_row));
struct ocr_row *or_root; // = ocr_row_root;
unsigned long bmp_row_offset(unsigned long int row);
unsigned int __bmp_bit2intidx(unsigned long int _bitcol);
unsigned char __col2charmask(unsigned long int _bitcol);
short bmp_px(unsigned long int row, unsigned long int col);
void *bmp_init();
void *bmp_alloc(struct bmp_io_t *_bmp_io);
void bmp_draw_row(unsigned int **matrix, unsigned int row, unsigned int width, unsigned long int px_width);
void *bmp_open(const char *filename);
void *bmp_row(unsigned long int row);
void bmp_print_shape(shape shape1);
void bmp_print_matrix(unsigned char *buffer, short width, short height);
unsigned int bmp_row_bit_count(unsigned long int row);
unsigned int *bmp_row_buffer(unsigned long int row, unsigned int **buffer, unsigned long int width);
unsigned int *bmp_col_buffer(unsigned long int col, unsigned int **buffer, unsigned long int height);
struct ocr_cell *bmp_stat(struct ocr_cell *cell);
void *bmp_flipw(void *mem, void *mask);
struct ocr_cell *bmp_cell_init(struct ocr_cell *prev);
struct ocr_cell *bmp_row_stat(struct ocr_cell *root);
struct ocr_cell *bmp_col_stat(unsigned long int row, unsigned long int col, unsigned long int height, struct ocr_cell *cell);
//int drawchar(int row_start, int row_end, int col_start, int col_end, struct bmp_px_matrix **xbase);
shape bmp_normalize_shape_get(struct stat_cell_t *cell);
unsigned int **bmp_init_matrix(unsigned int *pixels, unsigned int rows, unsigned int width);
unsigned int bmp_edge_mask(unsigned long int px_width);
extern unsigned short bmp_bitcount(uint64_t group);
extern unsigned short bmp_bcount32(uint32_t group);
extern unsigned short bmp_flip(void *p1, void *p2);
unsigned int __bmp_bit2CharIdx(unsigned long int _bitcol);
unsigned int __bmp_bit2idx(unsigned long int _bitcol, unsigned int size);
unsigned int __bmp_col2mask(unsigned long int _bitcol);
unsigned int bmp_col_bit_count(unsigned long int col);
unsigned int *bmp_row_counts();
unsigned int *bmp_col_counts();
unsigned int *bmp_col_buffer_offset(unsigned long int col, unsigned int **buffer, unsigned long int offset, unsigned long int height);
unsigned int *bmp_col_counts_offset(unsigned long int _col_start, unsigned long int _col_end, unsigned long int _row_start, unsigned long int _row_end);
unsigned int bmp_col_bit_count_offset(unsigned long int col, unsigned long int offset, unsigned long int length);
unsigned char *bmp_matrix_get(struct stat_cell_t *cell);
unsigned char *bmp_char_matrix_get(struct stat_cell_t *cell);
unsigned char *bmp_matrix_get_filter(struct stat_cell_t **cell);
shape bmp_normalize_matrix(unsigned char *buffer, struct stat_cell_t **cell); //TODO: pass cell
void bmp_draw_buffer(unsigned char **buffer, unsigned long int width, unsigned long int height, unsigned long int start, unsigned long int end);
unsigned int bmp_row_bit_count_partial(unsigned long int start, unsigned long int col_start, unsigned long int col_end);
unsigned long int **bmp_graph_buffer(unsigned char **buffer, unsigned long int width, unsigned long int height, unsigned long int start,
                                     unsigned long int end);
/* --- PRINTF_BYTE_TO_BINARY macro's --- */
#define PRINTF_BINARY_SEPARATOR
#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c "
#define PRINTF_BYTE_TO_BINARY_BE_INT8(i) \
    (((i) & 0x01ll) ? '1' : '0'), \
    (((i) & 0x02ll) ? '1' : '0'), \
    (((i) & 0x04ll) ? '1' : '0'), \
    (((i) & 0x08ll) ? '1' : '0'), \
    (((i) & 0x10ll) ? '1' : '0'), \
    (((i) & 0x20ll) ? '1' : '0'), \
    (((i) & 0x40ll) ? '1' : '0'), \
    (((i) & 0x80ll) ? '1' : '0')

#define PRINTF_BYTE_TO_BINARY_INT8(i)    \
    (((i) & 0x80ll) ? '1' : '0'), \
    (((i) & 0x40ll) ? '1' : '0'), \
    (((i) & 0x20ll) ? '1' : '0'), \
    (((i) & 0x10ll) ? '1' : '0'), \
    (((i) & 0x08ll) ? '1' : '0'), \
    (((i) & 0x04ll) ? '1' : '0'), \
    (((i) & 0x02ll) ? '1' : '0'), \
    (((i) & 0x01ll) ? '1' : '0')

#define PRINTF_BINARY_PATTERN_INT16 \
    PRINTF_BINARY_PATTERN_INT8               PRINTF_BINARY_SEPARATOR              PRINTF_BINARY_PATTERN_INT8
#define PRINTF_BYTE_TO_BINARY_INT16(i) \
    PRINTF_BYTE_TO_BINARY_INT8(i), PRINTF_BYTE_TO_BINARY_INT8((i) >> 8)
#define PRINTF_BINARY_PATTERN_INT32 \
    PRINTF_BINARY_PATTERN_INT16              PRINTF_BINARY_SEPARATOR              PRINTF_BINARY_PATTERN_INT16
#define PRINTF_BYTE_TO_BINARY_INT32(i) \
    PRINTF_BYTE_TO_BINARY_INT16(i), PRINTF_BYTE_TO_BINARY_INT16((i) >> 16)
#define PRINTF_BINARY_PATTERN_INT64    \
    PRINTF_BINARY_PATTERN_INT32              PRINTF_BINARY_SEPARATOR              PRINTF_BINARY_PATTERN_INT32
#define PRINTF_BYTE_TO_BINARY_INT64(i) \
    PRINTF_BYTE_TO_BINARY_INT32((i) >> 32), PRINTF_BYTE_TO_BINARY_INT32(i)
/* --- end macros --- */

#define ptrval(ptr, val) \
    *(ptr+val)

#endif //CODE_BITMAP_H

