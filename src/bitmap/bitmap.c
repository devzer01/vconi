//
// Created by nayana on 19/11/2560.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "bitmap.h"

BITMAPFILEHEADER *fileHeader;
BITMAPINFOHEADER *infoHeader;
typedef struct bmp_io_t {
    int fd;
    off_t len;
    int width;
    unsigned long int bi_width;
    int height;
    int size;
    unsigned char *data;
    unsigned char **pixels;
    unsigned char **uc_cursor;
    u_int64_t **ui64_cursor;
    unsigned int **n_px;
    unsigned char **ptr_cols;
} bmp_io_t, *ptr_bmp_io;
ptr_bmp_io bmp_io;

/**
 *
 * @param filename
 * @return
 */
void *bmp_open(char *filename)
{
    bmp_alloc();
    bmp_io->fd = open(filename, O_RDONLY);
    bmp_io->len = lseek(bmp_io->fd, 0, SEEK_END);
    bmp_io->data = mmap(NULL, (size_t) bmp_io->len, PROT_READ, MAP_PRIVATE, bmp_io->fd, 0);

    if (*(bmp_io->data) == 'B' && *(bmp_io->data+1) == 'M') {
        printf("correct\n");
    }

    bmp_init();
}

/**
 * initialize bmp_io
 * @return
 */
void *bmp_alloc()
{
    if (bmp_io != NULL) free(bmp_io);
    bmp_io = malloc(sizeof(struct bmp_io_t));
    return bmp_io;
}
/**
 *
 * @return
 */
void *bmp_init()
{
    fileHeader = (BITMAPFILEHEADER *) (bmp_io->data+2);
    infoHeader = (BITMAPINFOHEADER *) (bmp_io->data+2+sizeof(BITMAPFILEHEADER));

    bmp_io->bi_width = infoHeader->biWidth;
    bmp_io->pixels =  &bmp_io->data+(fileHeader->bOffBits);
    bmp_io->width = ((infoHeader->biBitCount * infoHeader->biWidth) / (8 * 4));
    bmp_io->height = infoHeader->biHeight;

    if ((bmp_io->width * bmp_io->height) < bmp_io->size) bmp_io->width++;
    bmp_io->width = bmp_io->width * 4;

    printf("bit map data size - %d \n", infoHeader->biSizeImage);

    bmp_io->n_px = malloc(sizeof(unsigned int *) * bmp_io->height);
    bmp_io->ptr_cols = malloc(sizeof(unsigned char *) * bmp_io->height); //to store starting address of each row

    unsigned int row = 0;

    while (row < bmp_io->height) {
        (*(bmp_io->ptr_cols+row)) = (bmp_io->data + (bmp_io->len - (bmp_io->width * row + 1)));
        (*(bmp_io->n_px)) = malloc(sizeof(unsigned int) * bmp_io->bi_width);
    }
}

void *bmp_row(unsigned long int row)
{
    return bmp_io->ui64_cursor = (u_int64_t  **) (*(bmp_io->ptr_cols+row));
}

void *bmp_stat()
{
    unsigned long int row = 0;
    while(row < bmp_io->height) {
        bmp_row_stat(row++);
    }
    struct ocr_cell *cell = malloc(sizeof(struct ocr_cell));
    struct ocr_cell *root_cell = cell;

    bmp_col_stat(0, 0, 10, &root_cell);

}

void *bmp_row_stat(unsigned long int row)
{
    unsigned long int col = 0;
    *(*(bmp_io->n_px+row)) = 0;
    while((col * 64) < bmp_io->bi_width) {
        if (*(*(bmp_io->ui64_cursor+row)+col) != 0) {
            *(*(bmp_io->n_px+row)) += bitcount((**bmp_io->ui64_cursor));
        }
        col++;
    }
}

void *bmp_cell_init(struct ocr_cell *prev)
{
    struct ocr_cell *cell = malloc(sizeof(struct ocr_cell));
    cell->prev = prev;
    prev->next = cell;
    cell->start = 0;
    return cell;
}

void *bmp_col_stat(unsigned long int row, unsigned long int col, short height, struct ocr_cell **cell)
{
    unsigned int byte = 0;
    unsigned char mask = 0b10000000;
    short px_count = 0, last_px_count = 0;
    while (col <= bmp_io->bi_width) {
        while (mask > 0) {
            px_count = 0;
            for (unsigned long int l_row = row; l_row < (row + height); l_row++) {
                if ((*(*(bmp_io->ptr_cols+l_row)+byte) & mask) == mask) {
                    px_count++;
                }
            }
            if (last_px_count == 0 && px_count != 0) {
                (*cell)->start = col;
            } else if (last_px_count != 0 && px_count == 0 && (*cell)->start != 0) {
                (*cell)->end = col;
                (*cell) = bmp_cell_init(*cell);
            }
            last_px_count = px_count;
            mask = mask >> 1;

        }
        col = col + 8;
        byte++;
        mask = 0b10000000;
    }
}