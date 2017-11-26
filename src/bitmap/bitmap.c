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
 * @qa tested
 * initialize bmp_io
 * @return
 */
void *bmp_alloc(struct bmp_io_t *_bmp_io)
{
    //if (_bmp_io != NULL)

    if (bmp_io != NULL) {
        munmap(bmp_io->data,(size_t) bmp_io->len);
        close(bmp_io->fd);
        free(bmp_io);
    }
    bmp_io = malloc(sizeof(struct bmp_io_t));
    fileHeader = malloc(sizeof(BITMAPFILEHEADER));
    infoHeader = malloc(sizeof(BITMAPINFOHEADER));
    return bmp_io;
}

/**
 * @qa tested
 * @param filename
 * @return
 */
void *bmp_open(const char *filename)
{
    bmp_alloc(NULL);
    bmp_io->fd = open(filename, O_RDONLY);
    bmp_io->filename = filename;
    if (bmp_io->fd == -1) {
        printf("unable to open file\n");
        exit(-1);
    }

    unsigned char magic[2];
    read(bmp_io->fd, magic, 2);
    if (magic[0] == 'B' && magic[1] == 'M') {

    } else {
        printf("unsupported file\n");
        exit(-1);
    }

    bmp_io->len = lseek(bmp_io->fd, 0, SEEK_END);
    lseek(bmp_io->fd, 2, SEEK_SET);
    read(bmp_io->fd, fileHeader, sizeof(BITMAPFILEHEADER));
    read(bmp_io->fd, infoHeader, sizeof(BITMAPINFOHEADER));
    bmp_io->header.offset = fileHeader->bOffBits;
    lseek(bmp_io->fd, 0, SEEK_SET);
    bmp_io->data = mmap(NULL, (size_t) bmp_io->len, PROT_READ, MAP_PRIVATE, bmp_io->fd, 0);
    bmp_io->bmp_data = (unsigned int *) (bmp_io->data+(bmp_io->header.offset));
    bmp_init();
}



/**
 * @test pass
 * @return
 */
void *bmp_init()
{

    bmp_io->bit_per_px = infoHeader->biBitCount;

    bmp_io->px.width = infoHeader->biWidth;
    bmp_io->px.height = infoHeader->biHeight;

    bmp_io->ints.width =  (((bmp_io->bit_per_px * bmp_io->px.width) + 31) / 32);
    bmp_io->ints.height = (bmp_io->px.height + 31) / 32;

    bmp_io->chars.width = bmp_io->ints.width * 4;
    bmp_io->chars.height = bmp_io->ints.height * 4;
}

/**
 * ****
 * @param _bitcol
 * @return
 */
unsigned int __bmp_bit2intidx(unsigned long int _bitcol)
{
    if (_bitcol < 32) {
        return 0;
    }
    unsigned  int _col = (_bitcol / 32);
            //if (_bitcol % 32 > 0) _col++;

    return _col;
}

/**
 * @test pass
 * @param _bitcol
 * @return
 */
unsigned int __bmp_bit2charidx(unsigned long int _bitcol)
{
    if (_bitcol < 8) {
        return 0;
    }

    return (unsigned int) ((_bitcol + 7) / 8);
}

/**
 * @test pass
 * @param _bitcol
 * @return
 */
unsigned char __col2charmask(unsigned long int _bitcol)
{
    return (unsigned char) 0b10000000 >> ((unsigned char)(_bitcol % 8));
}

unsigned int __col2intmask(unsigned long int _bitcol)
{
    unsigned long int _lbyteindex = __bmp_bit2intidx(_bitcol);
    return (unsigned int) (0b10000000 >> ((unsigned char)(_bitcol % 8))) << _lbyteindex;
}

/**
 *
 * @param row
 * @param col
 * @return
 */
short bmp_px(unsigned long int row, unsigned long int col)
{
    //if (row > bmp_io->height) row--;
    unsigned int mask = __col2intmask(col);
    unsigned long int __index = bmp_io->ints.width * ((bmp_io->px.height - row) - 1);
    __index = __index + __bmp_bit2intidx(col);
    if (bmp_io->bmp_data[__index] & mask) {
        return 1;
    }
    return 0;
}

unsigned long bmp_row_offset(unsigned long int row)
{
    unsigned long first = ((bmp_io->ints.width * (bmp_io->px.height - 1)));
    return (first - (bmp_io->ints.width * row));
}

unsigned int *bmp_row_buffer(unsigned long int row, unsigned int *buffer, unsigned long int length)
{
    buffer = malloc(sizeof(unsigned int) * (bmp_io->ints.width * length));
    memcpy(buffer, &bmp_io->bmp_data[bmp_row_offset(row)], bmp_io->ints.width);
    return buffer;
}

unsigned int bmp_col_index(unsigned int col)
{
    unsigned int __idx = __bmp_bit2intidx(col);

}

unsigned int *bmp_col_buffer(unsigned long int col, unsigned int *buffer, unsigned long int height)
{
    buffer = malloc(sizeof(unsigned int) * height);
    unsigned int *_buffer = buffer;
    unsigned long int _height = height;
    while (height > 0) {
        unsigned int __idxa = (bmp_io->ints.width * height - 1) + __bmp_bit2intidx(col);
        *buffer++ = (bmp_io->bmp_data[__idxa]);
        height--;
    }

    unsigned int mask = __col2intmask(col);
    unsigned int *colbuffer = malloc(sizeof(unsigned int) * bmp_io->ints.height);
    while(height < _height) {
        unsigned int _lindex = __bmp_bit2intidx(height);
        unsigned int _lmask = __col2intmask(height);
        if ((*(buffer+height-1) & mask) == mask) {
            *(colbuffer+_lindex) = *(colbuffer+_lindex) ^ _lmask;
        }
        height++;
    }

    return colbuffer;
}

/**
 * @test pass
 * @param row
 * @return
 */
unsigned int bmp_row_bit_count(unsigned long int row)
{
    unsigned long int col = 0;
    bmp_io->row_px_count[row] = 0;
    unsigned int *buffer = malloc(sizeof(unsigned int) * bmp_io->ints.width);
            buffer = bmp_row_buffer(row, buffer, 1);

    while((col * 31) < bmp_io->px.width) {
        u_int32_t ptr =  (u_int32_t) buffer[col];
        bmp_io->row_px_count[row] += bmp_bcount32(ptr);
        col++;
    }
    return bmp_io->row_px_count[row];
}

/**
 * @test pass
 * @param row
 * @return
 */
unsigned int bmp_col_bit_count(unsigned long int col)
{
    bmp_io->row_px_count[col] = 0;
    unsigned int *buffer = malloc(sizeof(unsigned int) * bmp_io->px.height);
    unsigned int *_buffer = buffer;
    unsigned int *colbuffer = bmp_col_buffer(col, buffer, bmp_io->px.height);

    while((col * 31) < bmp_io->px.height) {
        u_int32_t ptr =  (u_int32_t) colbuffer[col];
        bmp_io->col_px_count[col] += bmp_bcount32(ptr);
        col++;
    }
    return bmp_io->row_px_count[col];
}


struct ocr_cell *bmp_row_stat(struct ocr_cell *cell)
{
    unsigned long int row = 0;
    struct ocr_cell *root = cell;
    cell->r_start = 0;
    cell->start = -1;
    cell->end = -1;
    while(row < bmp_io->px.height) {
        unsigned int cnt = bmp_row_bit_count(row);
        if (cell->start == -1 && cnt != 0) {
            cell->start = row;
        } else if (cell->start != -1 && cnt == 0) {
            cell->end = (row - 1);
            (cell) = (bmp_cell_init(cell));
        }

        if (cell->start != -1 && row == bmp_io->px.height - 1 && cnt != 0) {
            cell->end = (row);
            (cell) = (bmp_cell_init(cell));
        }
        row++;
    }

    return cell;
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
    while (col < bmp_io->px.width) {
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
        (cell)->end = bmp_io->px.width - 1;
        (cell) = (bmp_cell_init(cell));
    }
    return (cell);
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
    return (*(bmp_io->row_px_count + row) == 0);
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



