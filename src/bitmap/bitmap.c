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

    if (bmp_io->fd == -1) {
        printf("unable to open file\n");
        exit(-1);
    }

    bmp_io->len = lseek(bmp_io->fd, 0, SEEK_END);
    bmp_io->data = mmap(NULL, (size_t) bmp_io->len, PROT_READ, MAP_PRIVATE, bmp_io->fd, 0);

    if (*(bmp_io->data) == 'B' && *(bmp_io->data+1) == 'M') {
        //xxxx
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

unsigned long bmp_row_offset(unsigned long int row)
{
    return ((bmp_io->width * (bmp_io->height - 1)) - row);
}
/**
 * @test pass
 * @return
 */
void *bmp_init()
{
    fileHeader = (BITMAPFILEHEADER *) (bmp_io->data+2);
    infoHeader = (BITMAPINFOHEADER *) (bmp_io->data+2+sizeof(BITMAPFILEHEADER));

    bmp_io->bi_width = infoHeader->biWidth;
    bmp_io->pixels = (unsigned int *) (bmp_io->data+(fileHeader->bOffBits));
    bmp_io->byte_width = ((infoHeader->biBitCount * infoHeader->biWidth) + 31) / 8;
    bmp_io->width =  bmp_io->byte_width / 4;
    bmp_io->height = infoHeader->biHeight;
    bmp_io->b_height = (infoHeader->biHeight + 31 / 32);

    //if ((bmp_io->width * bmp_io->height) < bmp_io->size) bmp_io->width++;
    //bmp_io->width = bmp_io->width * 4;

    bmp_io->n_rpx = malloc(sizeof(unsigned int *) * bmp_io->height);
    bmp_io->ptr_cols = malloc(sizeof(unsigned int *) * bmp_io->height); //to store starting address of each row

    /*unsigned int row = bmp_io->height;
    bmp_io->n_rpx = malloc(sizeof(unsigned int) * bmp_io->height);
    *(bmp_io->ptr_cols) =  (bmp_io->pixels + bmp_row_offset(0));
    while (row < bmp_io->height) {
        *(bmp_io->ptr_cols+row) =  *(bmp_io->ptr_cols)
        *(bmp_io->n_rpx+row) = 0;
        row--;
    }*/
}
unsigned int bmp_edge_mask(unsigned long int px_width)
{
    unsigned long int bytes_used = (px_width % 32) / 8;
    unsigned long int partial_index = (px_width % 32) % 8;
    unsigned int mask = (unsigned int) (0b00000001 << (partial_index + (bytes_used * 8)));
    return mask;
}


void bmp_draw_row(unsigned int **matrix, unsigned int row, unsigned int width, unsigned long int px_width) {
    //unsigned int bytes = width * sizeof(unsigned int);
    unsigned int segment = 0;
    unsigned int mask = 0b00000001;
    unsigned int cursor = matrix[row][segment];
    while (segment < width) {
        while (mask > 0 && px_width > 0) {
            if ((mask & cursor) == mask) {
                printf("*");
            } else {
                printf(".");
            }
            mask = mask << 1;
            px_width--;
        }
        segment++;
        cursor = matrix[row][segment];
        mask = 0b00000001;
    }

    printf("\n");
}

unsigned int **bmp_init_matrix(unsigned int *pixels, unsigned int rows, unsigned int width)
{
    unsigned int **matrix = malloc(sizeof(unsigned int *) * rows);
    unsigned int l_cursor = 0;
    while(rows > 0) {
        matrix[l_cursor] = malloc(sizeof(unsigned int ) * width);
        memcpy(matrix[l_cursor], &pixels[(rows-1) * width], sizeof(unsigned int) * width);
        rows--; l_cursor++;
    }

    return matrix;

    /**(matrix) = malloc(sizeof(unsigned int) * 1);
    *(matrix+1) = malloc(sizeof(unsigned int) * 2);
    *(matrix+2) = malloc(sizeof(unsigned int) * 3);
    *(matrix+4) = malloc(sizeof(unsigned int) * 4);*/

    /**(*(matrix)) = 0xFAFAFAFA;
    *(*(matrix+1)) = 0xFFFFFFFF;
    *(*(matrix+1)+1) = 0xFFFFFFFA;*/
}

struct ocr_cell *bmp_row_stat(struct ocr_cell *cell)
{
    unsigned long int row = 0;
    struct ocr_cell *_root = cell;
    cell->r_start = 0;
    cell->start = -1;
    cell->end = -1;
    while(row < bmp_io->height) {
        unsigned int cnt = bmp_row_bit_count(row);
        if (cell->start == -1 && cnt != 0) {
            cell->start = row;
        } else if (cell->start != -1 && cnt == 0) {
            cell->end = (row - 1);
            (cell) = (bmp_cell_init(cell));
        }

        if (cell->start != -1 && row == bmp_io->height - 1 && cnt != 0) {
            cell->end = (row);
            (cell) = (bmp_cell_init(cell));
        }
        row++;
    }

    return cell;
}

struct ocr_cell *bmp_stat(struct ocr_cell *root)
{
    //struct ocr_cell *row_stat = malloc(sizeof(struct ocr_cell));
    struct ocr_cell *last_row = bmp_row_stat(root);

    //struct ocr_cell **cell = malloc(sizeof(struct ocr_cell *) * 24);
    //struct ocr_cell *cell = malloc(sizeof(struct ocr_cell));
    struct ocr_cell *rcell = root;
    //struct ocr_cell *cell = malloc(sizeof(struct ocr_cell));;
    while(rcell->index < last_row->index) {
        rcell->first = malloc(sizeof(struct ocr_cell));
        rcell->first->index = 0;
        rcell->first->r_start = rcell->start;
        rcell->first->r_end = rcell->end;
        rcell->last = bmp_col_stat(rcell->first->r_start, 0, (rcell->end - rcell->start) + 1, rcell->first);
        (rcell) = rcell->next;
    }

    return last_row;

}

short bmp_is_row_empty(unsigned long int row)
{
    return (*(bmp_io->n_rpx + row) == 0);
}

/**
 * @test pass
 * @param row
 * @return
 */
unsigned int bmp_row_bit_count(unsigned long int row)
{
    unsigned long int col = 0;
    //TODO check if data corruption
    bmp_io->ptr_rows = malloc(sizeof(unsigned int *) * bmp_io->height);
    (*(bmp_io->n_rpx+row)) = 0;
    while((col * 31) < bmp_io->bi_width) {
        //bmp_io->ui64_cursor = (u_int64_t *) ((u_int64_t) *(bmp_io->ptr_cols + row) + col);
        //if (*bmp_io->ui64_cursor != 0) {
     /*       if (bmp_io->bi_width < 32 || (col * 63) > bmp_io->bi_width) { */
                u_int32_t ptr =  (u_int32_t) *(*(bmp_io->ptr_cols + row) + col);
                (*(bmp_io->n_rpx + row)) += bmp_bcount32(ptr);
     /*       } else {*/
                //(*(bmp_io->n_rpx + row)) += bmp_bitcount(*bmp_io->ui64_cursor);
            //}
        //}
        col++;
    }
    return (*(bmp_io->n_rpx+row));
}

/**
 * @test pass
 * @param prev
 * @return
 */
struct ocr_cell *bmp_cell_init(struct ocr_cell *prev)
{
    prev->next = malloc(sizeof(struct ocr_cell));
    prev->next->index = prev->index + 1;
    (prev->next)->prev = (prev);
    prev->next->start = -1;
    prev->next->end = -1;
    return prev->next;
}

/**
 * @test pass
 * @param _bitcol
 * @return
 */
unsigned int __bit2index(unsigned long int _bitcol)
{
    if (_bitcol < 32) {
        return 0;
    }

    return (unsigned int) ((_bitcol + 31) / 32);
}

/**
 * @test pass
 * @param _bitcol
 * @return
 */
unsigned char __col2mask(unsigned long int _bitcol)
{
    return (unsigned char) 0b10000000 >> ((unsigned char)(_bitcol % 8));
}

short bmp_px(unsigned long int row, unsigned long int col)
{
    //if (row > bmp_io->height) row--;
    unsigned int lcol = __bit2index(col);
    unsigned char mask = __col2mask(col);
    if (*(*(bmp_io->ptr_cols+row)+lcol) & mask) {
        return 1;
    }
    return 0;
}

/**
 * @test pass
 * @param row
 * @param col
 * @param height
 * @param cell
 * @return
 */
struct ocr_cell *bmp_col_stat(unsigned long int row, unsigned long int col, unsigned long int height, struct ocr_cell *cell)
{
    short px_count = 0, last_px_count = 0;
    struct ocr_cell *root = cell;
    while (col < bmp_io->bi_width) {
        px_count = 0;
        unsigned long int _row = row;
        while (_row < (row + height)) {
            px_count += bmp_px(_row, col);
            _row++;
        }
        if (last_px_count == 0 && px_count != 0) {
            (cell)->start = col;
        }
        if (last_px_count != 0 && px_count == 0 && (cell)->start != -1) {
            (cell)->end = col - 1;
            //(cell)->r_end = _row - 1;
            (cell) = bmp_cell_init(cell);
            (cell)->r_start = row;
            (cell)->r_end = (_row  - 1);
        }
        last_px_count = px_count;
        col++;
    }
    if ((cell)->end == -1 && (cell)->start != -1) {
        (cell)->end = bmp_io->bi_width - 1;
        (cell) = (bmp_cell_init(cell));
    }
    return (cell);
}