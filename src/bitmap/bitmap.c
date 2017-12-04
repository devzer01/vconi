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
#include "stats.h"


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

    bmp_io->row_px_count = malloc(sizeof(unsigned int) * bmp_io->px.height);
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
    return (_bitcol / 32);
}

/**
 *
 * @param _bitcol
 * @return
 */
unsigned int __bmp_col2mask(unsigned long int _bitcol)
{
    unsigned int offset = (_bitcol / 8) + 1; //because we are zero based
    unsigned int index =  (_bitcol % 8) + 1; //because we are zero based
    unsigned int needle = 0x01 << ((offset * 8) - index);
   // unsigned int needle = 0x80 << ((offset * 8) - index);
    //needle = needle >> index;
    return  needle;
}

/**
 *
 * @param row
 * @return
 */
unsigned long bmp_row_offset(unsigned long int row)
{
    unsigned long int l_row = (bmp_io->px.height - row - 1);
    return (bmp_io->ints.width * l_row);
}

/**
 *
 * @param row
 * @param buffer
 * @param width
 * @return
 */
unsigned int *bmp_row_buffer(unsigned long int row, unsigned int **buffer, unsigned long int width)
{
    *buffer = malloc(sizeof(unsigned int) * width);
    memcpy(*buffer, (unsigned int *) &bmp_io->bmp_data[bmp_row_offset(row)], sizeof(unsigned int) * width);
    return *buffer;
}

/**
 *
 * @param col
 * @param buffer
 * @param height
 * @param offset
 * @return
 */
unsigned int *bmp_col_buffer_offset(unsigned long int col, unsigned int **buffer, unsigned long int offset, unsigned long int height)
{
    *buffer = malloc(sizeof(unsigned int) * bmp_io->px.height);
    unsigned long int _height = 0; //(height - 1);
    unsigned long int _col = __bmp_bit2intidx(col);
    while (_height < bmp_io->px.height) {
        unsigned int *tmp = malloc(sizeof(unsigned int) * bmp_io->ints.width);
        memcpy(tmp, (unsigned int *) &bmp_io->bmp_data[bmp_row_offset(_height)], sizeof(unsigned int) * bmp_io->ints.width);
        memcpy((*buffer+_height), tmp+_col, sizeof(unsigned int));
        free(tmp);
        _height++;
    }

    return (*buffer);
}

unsigned char *bmp_matrix_get(struct stat_cell_t **cell)
{
    bmp_row_buffer((*cell)->row.start, );
}

/**
 *
 * @param col
 * @param buffer
 * @param height
 * @return
 */
unsigned int *bmp_col_buffer(unsigned long int col, unsigned int **buffer, unsigned long int height)
{
    *buffer = malloc(sizeof(unsigned int) * height);
    unsigned long int _height = 0; //(height - 1);
    while (_height < height) {
        memcpy((*buffer+_height), (unsigned int *) &bmp_io->bmp_data[bmp_row_offset(_height)], sizeof(unsigned int));
        _height++;
    }

    return (*buffer);
}

unsigned int *bmp_row_counts()
{
    unsigned int *vec = malloc(sizeof(unsigned int) * bmp_io->px.height);
    for (int i = 0; i < bmp_io->px.height; i++) {
        *(vec+i) =bmp_row_bit_count(i);
    }

    return vec;
}

unsigned int *bmp_col_counts()
{
    unsigned int *vec = malloc(sizeof(unsigned int) * bmp_io->px.width);
    for (int i = 0; i < bmp_io->px.width; i++) {
        *(vec+i) =bmp_col_bit_count(i);
    }

    return vec;
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
    uint32_t *buffer = malloc(sizeof(unsigned int) * bmp_io->ints.width);
            buffer = bmp_row_buffer(row, &buffer,  bmp_io->ints.width);
    unsigned long int index = 0;
    while (index < bmp_io->ints.width) {
        bmp_io->row_px_count[row] += bmp_bcount32(*(buffer+index));
        index++;
    }
    return bmp_io->row_px_count[row];
}

/**
 *
 * @return
 */
unsigned int *bmp_col_counts_offset(unsigned long int _col_start, unsigned long int _col_end, unsigned long int _row_start, unsigned long int height)
{
    unsigned int *vec = malloc(sizeof(unsigned int) * bmp_io->px.width);
    for (int i = 0; i < bmp_io->px.width; i++) {
        *(vec+i) = bmp_col_bit_count_offset(i, _row_start, height);
    }

    return vec;
}

/**
 *
 * @param col
 * @param offset row offset
 * @param length
 * @return
 */
unsigned int bmp_col_bit_count_offset(unsigned long int col, unsigned long int _row_start, unsigned long int height)
{
    //bmp_io->col_px_count = malloc(sizeof(unsigned int) * bmp_io->px.width);
    unsigned int *buffer = malloc(sizeof(unsigned int) * height);
    buffer = bmp_col_buffer_offset(col, &buffer, _row_start, height);
    unsigned long int _height = _row_start;
    unsigned long int counter = 0;
    while(_height < (_row_start + height)) {
        u_int32_t val = (u_int32_t) (ptrval(buffer, _height) & __bmp_col2mask(col));
        counter += bmp_bcount32(val);
        _height++;
    }
    return counter;
}

/**
 * @test pass
 * @param row
 * @return
 */
unsigned int bmp_col_bit_count(unsigned long int col)
{
    bmp_io->col_px_count = malloc(sizeof(unsigned int) * bmp_io->px.width);
    unsigned int *buffer = malloc(sizeof(unsigned int) * bmp_io->px.height);
    buffer = bmp_col_buffer(col, &buffer, bmp_io->px.height);
    unsigned int _offset = (col / 31);
    unsigned long int _height = 0;
    while(_height < bmp_io->px.height) {
        u_int32_t val = (u_int32_t) (ptrval(buffer,_height) & __bmp_col2mask(col));
        *((bmp_io->col_px_count)+col) += bmp_bcount32(val);
        _height++;
    }
    return *(bmp_io->col_px_count+col);
}

short bmp_is_row_empty(unsigned long int row)
{
    return (*(bmp_io->row_px_count + row) == 0);
}





