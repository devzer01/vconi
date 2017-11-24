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

/**
 *
 * @param filename
 * @return
 */
void *bmp_open(const char *filename)
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
    bmp_io->pixels = (unsigned int *) (bmp_io->data+(fileHeader->bOffBits));
    bmp_io->width = ((infoHeader->biBitCount * infoHeader->biWidth) + 31) / (8 * 4);
    bmp_io->height = infoHeader->biHeight;
    bmp_io->b_height = (infoHeader->biHeight + 31 / 32);

    //if ((bmp_io->width * bmp_io->height) < bmp_io->size) bmp_io->width++;
    //bmp_io->width = bmp_io->width * 4;

    printf("bit map data size - %d \n", infoHeader->biSizeImage);

    bmp_io->n_rpx = malloc(sizeof(unsigned int *) * bmp_io->height);
    bmp_io->ptr_cols = malloc(sizeof(unsigned int *) * bmp_io->height); //to store starting address of each row

    unsigned int row = 0;
    bmp_io->n_rpx = malloc(sizeof(unsigned int) * bmp_io->height);
    while (row < bmp_io->height) {
        *(bmp_io->ptr_cols+row) =  (bmp_io->pixels + ((bmp_io->width * (bmp_io->height - 1)) - row));
        *(bmp_io->n_rpx+row) = 0;
        row++;
    }
}


struct ocr_cell *bmp_stat()
{
    unsigned long int row = 0;
    while(row < bmp_io->height) {
        bmp_row_stat(row++);
    }
    //struct ocr_cell **cell = malloc(sizeof(struct ocr_cell *) * 24);
    struct ocr_cell *cell = malloc(sizeof(struct ocr_cell));
    struct ocr_cell *rcell = cell;
    struct ocr_cell *root = cell;
    short n_cell = 0;
    row = 1;
    cell->r_start = 0;
    if (*(bmp_io->n_rpx) != 0) cell->start = 1;
    while(row <= bmp_io->height) {
        if (cell->r_start != 0) {
            while((*(bmp_io->n_rpx+row++) != 0) || row == bmp_io->height);
            cell->r_start--;  cell->r_end = row - cell->r_start;
            cell = bmp_col_stat(cell->r_start, 0, cell->r_end, cell);
            cell->r_start = 0;
        }
        row++;
        if (*(bmp_io->n_rpx+row) != 0) cell->r_start = row;
    }

    return root;

}

unsigned int bmp_row_stat(unsigned long int row)
{
    unsigned long int col = 0;
    bmp_io->ptr_rows = malloc(sizeof(unsigned int *) * bmp_io->height);
    (*(bmp_io->n_rpx+row)) = 0;
    while((col * 64) < bmp_io->bi_width) {
        bmp_io->ui64_cursor = (u_int64_t *) ((u_int64_t) *(bmp_io->ptr_cols + row) + col);
        if (*bmp_io->ui64_cursor != 0) {
            if (bmp_io->bi_width < 32) {
                u_int32_t ptr =  (u_int32_t) *(*(bmp_io->ptr_cols + row) + col);
                (*(bmp_io->n_rpx + row)) += bmp_bcount32(ptr);
            } else {
                (*(bmp_io->n_rpx + row)) += bmp_bitcount(*bmp_io->ui64_cursor);
            }
        }
        col++;
    }
    return (*(bmp_io->n_rpx+row));
}

void *bmp_cell_init(struct ocr_cell *prev)
{
    struct ocr_cell *cell = malloc(sizeof(struct ocr_cell));
    cell->prev = prev;
    prev->next = cell;
    cell->start = 0;
    cell->end = 0;
    return cell;
}

short bmp_px(unsigned long int row, unsigned long int col)
{
    if (row >= bmp_io->height) row--;
    unsigned int lcol = (unsigned int) (col + 31) / 32;
    unsigned char mask = (unsigned char) 0b10000000 >> ((unsigned char)(col % 8));
    if (*(*(bmp_io->ptr_cols+row)+lcol) & mask) {
        return 1;
    }
    return 0;
}

struct ocr_cell *bmp_col_stat(unsigned long int row, unsigned long int col, short height, struct ocr_cell *cell)
{
    short px_count = 0, last_px_count = 0;

    while (col <= bmp_io->bi_width) {
        px_count = 0;
        short lrow = 0;
        while (lrow < height) {
            px_count += bmp_px(row + lrow, col);
            lrow++;
        }
        if (last_px_count == 0 && px_count != 0) {
            (cell)->start = col;
        } else if (last_px_count != 0 && px_count == 0 && (cell)->start != 0) {
            (cell)->end = col;
            (cell) = bmp_cell_init(cell);
            (cell)->r_start = row;
            (cell)->r_end = row + height;
        }
        last_px_count = px_count;
        col++;
    }
    if ((cell)->end == 0 && (cell)->start != 0) {
        (cell)->end = col-1;
        (cell) = bmp_cell_init(cell);
    }
    return (cell);
}