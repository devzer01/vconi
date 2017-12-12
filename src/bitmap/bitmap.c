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
    return __bmp_bit2idx(_bitcol, 32);
}

unsigned int __bmp_bit2CharIdx(unsigned long int _bitcol)
{
    return __bmp_bit2idx(_bitcol, 8);
}

unsigned int __bmp_bit2idx(unsigned long int _bitcol, unsigned int size)
{
    if (_bitcol < size) {
        return 0;
    }
    return (_bitcol / size);
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
    short shift_counter = ((offset * 8) - index);
    unsigned int needle = 0x01 << shift_counter;
   // unsigned int needle = 0x80 << ((offset * 8) - index);
    //needle = needle >> index;
    return  needle;
}

/**
 *
 * @param _bitcol
 * @return
 */
unsigned char __bmp_col2mask_char(unsigned long int _bitcol)
{
    unsigned int offset = (_bitcol % 8); //because we are zero based
    unsigned char needle = 0x80 >> offset;
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

unsigned char *bmp_row_char_buffer(unsigned long int row, unsigned char **buffer, unsigned long int width)
{
    *buffer = (unsigned char *) malloc(sizeof(unsigned int) * width);
    memcpy(*buffer, (unsigned char *) &bmp_io->bmp_data[bmp_row_offset(row)], sizeof(unsigned int) * width);
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

unsigned char *bmp_char_matrix_get(struct stat_cell_t *cell)
{
    unsigned long int height = (cell->row.end - cell->row.start) + 1;
    unsigned long int _row = 0, _col = 0;
    unsigned long int width = (cell->col.end - cell->col.start) + 1;
    unsigned char mask = __bmp_col2mask_char(cell->col.start);

    if (height * width == 0) {
        printf("heign witdth 0 \n");
        return NULL;
    }
    unsigned char *matrix = malloc(sizeof(unsigned char *) * height * width);
    unsigned char *ptrMatrix = matrix;
    unsigned char *buffer = bmp_matrix_get(cell);
    unsigned short charCounter = 0;
    while (_row < height) {
        _col = 0;
        while (_col < width) {
            unsigned char cursor = *(buffer+charCounter);
            while (mask > 0 && _col < width) {
                if (mask == (cursor & mask) && mask > 0) {
                    *matrix = '1'; //(cursor & mask);
                } else {
                    *matrix = '0';
                }
                matrix++;
                mask = mask >> 1;
                _col++;
            }
            mask = 0x80;
            charCounter++;
        }
        mask = __bmp_col2mask_char(cell->col.start);
        _row++;
    }
    free(buffer);
    return ptrMatrix;
}

unsigned char *bmp_matrix_get(struct stat_cell_t *cell)
{
    unsigned long int height = cell->row.end - cell->row.start + 1;
    unsigned long int _row = cell->row.start;
    unsigned long int width = (cell->col.end - cell->col.start) + 1;
    unsigned int column = __bmp_bit2CharIdx(cell->col.start);
    unsigned int columnEnd = __bmp_bit2CharIdx(cell->col.end);
    unsigned long int bWidth = (columnEnd - column + 1);
    unsigned char *matrix = malloc(sizeof(unsigned char *) * height * bWidth);
    unsigned long int __row = 0;
    while (_row <= cell->row.end) {
        unsigned int *buffer = malloc(sizeof(unsigned int) * bmp_io->ints.width);
        unsigned char *charBuffer = malloc(sizeof(unsigned char) * (bmp_io->ints.width * 4));
        unsigned char *ptr = charBuffer;
        short irow = 0;
        buffer = bmp_row_buffer(_row, &buffer, bmp_io->ints.width);
        while (irow < bmp_io->ints.width) {
            (*(charBuffer+3)) = (*buffer >> 24) & 0xFF;
            (*(charBuffer+2)) = (*buffer >> 16) & 0xFF;
            (*(charBuffer+1)) = (*buffer >> 8) & 0xFF;
            (*(charBuffer)) = *buffer & 0xFF;
            charBuffer += 4;
            buffer++;
            irow++;
        }
        memcpy((matrix + (__row * bWidth)), (ptr+column), bWidth);
        _row++;
        __row++;
    }
    return matrix;
}

unsigned char *bmp_matrix_get_filter(struct stat_cell_t **cell)
{
    unsigned long int height = ((*cell)->row.end - (*cell)->row.start) + 1;
    unsigned long int _row = (*cell)->row.start;
    unsigned long int width = ((*cell)->col.end - (*cell)->col.start) + 1;
    unsigned int column = __bmp_bit2CharIdx((*cell)->col.start);
    unsigned int columnEnd = __bmp_bit2CharIdx((*cell)->col.end);
    unsigned long int bWidth = (columnEnd - column + 1);
    unsigned char *matrix = malloc(sizeof(unsigned char *) * height * bWidth);
    unsigned long int __row = 0;
    while (_row < (*cell)->row.end) {
        unsigned int *buffer = malloc(sizeof(unsigned int) * bmp_io->ints.width);
        unsigned char *cBuffer = (unsigned char *) bmp_row_buffer(_row, &buffer, bmp_io->ints.width);
        unsigned long int __col = column;
        int skip = 0;
        unsigned long int count = 0;
        while(__col <= columnEnd) {
            count += bmp_bcount32((uint32_t) *(cBuffer+column));
            __col++;
        }
        if (count != 0) {
            memcpy((matrix + (__row * bWidth)), (cBuffer+column), bWidth);
            __row++;
        }
        _row++;
    }
    return matrix;
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

unsigned long int **bmp_graph_buffer(unsigned char **buffer, unsigned long int width, unsigned long int height, unsigned long int start,
                      unsigned long int end)
{
    unsigned long int _row = 0;
    unsigned long int _col = 0;
    int _start = __bmp_bit2CharIdx(start);
    int _end = __bmp_bit2CharIdx(end);
    unsigned long int bWidth = _end - _start + 1;
    unsigned long int **maskValues = malloc(sizeof(unsigned long int *) * height);
    while (_row < height) {
        _col = start;
        unsigned char *ptrCol = (unsigned char *) (*buffer+(_row*bWidth));
        unsigned char mask = 0b10000000 >> (start % 8);
        unsigned long int bCol = 0;
        unsigned long int maskVal = 0;
        unsigned long int iMask = 0x80000000;
        while (bCol < bWidth) {
            unsigned char cursor = *(ptrCol+bCol);
            while (mask > 0 && _col < (start + width)) {
                if ((mask & cursor) == mask) {
                    maskVal += iMask;
                }
                mask = mask >> 1;
                iMask = iMask >> 1;
                _col++;
            }
            mask = 0x80;
            bCol++;
        }
        *(maskValues+_row) = malloc(sizeof(unsigned long int));
        *(*(maskValues+_row)) = maskVal;
        _row++;
    }
    return maskValues;
}


void bmp_draw_buffer(unsigned char **buffer, unsigned long int width, unsigned long int height, unsigned long int start,
                     unsigned long int end)
{
    unsigned long int _row = 0;
    unsigned long int _col = 0;
    int _start = __bmp_bit2CharIdx(start);
    int _end = __bmp_bit2CharIdx(end);
    unsigned long int bWidth = _end - _start + 1;

    while (_row < height) {
        _col = start;
        unsigned char *ptrCol = (unsigned char *) (*buffer+(_row*bWidth));
        unsigned char mask = 0b10000000 >> (start % 8);
        unsigned long int bCol = 0;
        unsigned char *tabs = " ";
        //printf("starting mask %#0x width %d ", mask, width);
        unsigned long int maskVal = 0;
        unsigned long int iMask = 0x80000000;
        printf("%20s", tabs);
        while (bCol < bWidth) {
            unsigned char cursor = *(ptrCol+bCol);
            while (mask > 0 && _col < (start + width)) {
                //printf("cursor %#0x ", cursor);
                unsigned char _x = ((mask & cursor) == mask) ? '1' : '0';
                if ((mask & cursor) == mask) {
                    maskVal += iMask;
                }
                printf("%c", _x);
                mask = mask >> 1;
                iMask = iMask >> 1;
                _col++;
            }
            mask = 0x80;
            bCol++;
        }
        printf(" - %ld \n", maskVal);
        _row++;
    }
}



unsigned int bmp_row_bit_count_partial(unsigned long int row, unsigned long int col_start, unsigned long int col_end) {
    unsigned long int int_start = __bmp_bit2intidx(col_start);
    unsigned long int int_end = __bmp_bit2intidx(col_end);
    unsigned long int iWidth = (int_end - int_start + 1);
    unsigned int *buffer = malloc(sizeof(unsigned int) * bmp_io->ints.width);
    buffer = bmp_row_buffer(row, &buffer, bmp_io->ints.width);
    unsigned int *offset = (buffer+int_start);
    unsigned int *offset_end = (buffer+int_end);
    unsigned int *tbuff = malloc(sizeof(unsigned int) * iWidth);
    memcpy(tbuff, offset, iWidth * 4);
    unsigned long int index = 0;
    unsigned long int counter = 0;
    while (index < iWidth) {
        counter += bmp_bcount32(*(tbuff+index));
        index++;
    }
    return counter;
}

void bmp_print_matrix(unsigned char *buffer, short width, short height)
{
    for (short _row = 0; _row < height; _row++) {
        for (short _col = 0; _col < width; _col++) {
            if ((*(buffer+(_row*width)+_col)) != '0') {
                printf("1");
            } else {
                printf("0");
            }
            //printf("%#x", shape1.buf[_row][_col]);
        }
        printf("\n");
    }
}

void bmp_print_shape(shape shape1)
{
    for (short _row = 0; _row < MAX_SHAPE_HEIGHT; _row++) {
        for (short _col = 0; _col < MAX_SHAPE_WIDTH; _col++) {
            if (shape1.buf[_row][_col] != '0' && shape1.buf[_row][_col] != '1') continue;
            if (shape1.buf[_row][_col] != '0') {
                printf("1");
            } else {
                printf("0");
            }
            //printf("%#x", shape1.buf[_row][_col]);
        }
        printf("\n");
    }
}

shape bmp_normalize_shape_get(struct stat_cell_t *cell)
{
    unsigned char *buff = bmp_char_matrix_get(cell);
    unsigned long int _row = 0, _col = 0, _height = (cell->row.end - cell->row.start + 1);
    unsigned long int _width = (cell->col.end - cell->col.start + 1);
    shape matrix;
    //unsigned char matrix[MAX_SHAPE_HEIGHT][MAX_SHAPE_WIDTH] = {};
    int _x_factor = (_width / MAX_SHAPE_WIDTH) + 1;
    int _y_factor = _height / MAX_SHAPE_HEIGHT;
    unsigned short int _f = 0, _mcol = MAX_SHAPE_WIDTH - 1, _z = 0, _mrow = 0;
    shape _shape; //_shape.buf[_row][_col];
    unsigned short int _temp_buffer_length = MAX_SHAPE_WIDTH * _y_factor;
    if (_temp_buffer_length  == 0 || _x_factor == 0 || _y_factor == 0) {
        printf("too small \n");
        memcpy(&matrix.buf, buff, sizeof(unsigned char) * _width * _height);
        return matrix;
    }
    short _tx_row = 0;
    //char (*tbufer)[MAX_SHAPE_WIDTH];
    char tbufer[3][MAX_SHAPE_WIDTH] = {};
    //char **ptTbuffer = tbufer;
    unsigned short int cursor = 0, dcursor = 0;
    short _trow = 0;
    short _tcol = 0;
    short _max_col = 0;
    printf("x %d y %d w %d\n", _x_factor, _y_factor, _width);
    //_x_factor = 3;
    while (_row < _height) {
        _col = 0;
        _tcol = 0;
        _trow++;
        if (_trow >= _y_factor) _trow = 0;
        while (_col < _width) {
            float _avg = 0.0L;
            if (_tcol > _max_col) _max_col = _tcol;
            while (_f < _x_factor) {
                //printf(".%d.", cursor);
                if (*(buff + cursor) == '1') {
                    _avg++;
                }
                cursor++;
                _f++;
            }
            //printf(".%d.", _tcol);
            tbufer[_trow][_tcol] = '0';
            //printf("avg %f ..", _avg);
            if (_avg / _x_factor > _x_factor / 2 ) {
                tbufer[_trow][_tcol] = '1';
            }
            _col += _x_factor;
            _tcol++;
            dcursor++;
            _f = 0;

            if (dcursor % _temp_buffer_length == 0) {
                _mcol = 0;
                _z = 0;
                short _a = 0;
                while (_a < _y_factor) {
                    _z = 0;
                    while (_z <= _max_col) {
                        //printf("%c", tbufer[_a][_z]);
                        _z++;
                    }
                    //printf("\n");
                    _a++;
                }
                //printf("------\n");
                _z = 0;
                while(_z <= _max_col) {
                    _f = 0;
                    short _n = 0;
                    while (_f < _y_factor) {
                        if (tbufer[_f][_mcol] == '1') _n++;
                        _f++;
                    }
                    matrix.buf[_mrow][_mcol] = '3';
                    if ((_n / _y_factor) > 0.0) {
                        //printf("1");
                        matrix.buf[_mrow][_mcol] = '1';
                    } else {
                        //printf("0");
                        matrix.buf[_mrow][_mcol] = '0';
                    }
                    _mcol++;
                    _z++;
                }
               // printf("\n");
                _mrow++;
            }
        }
        cursor = (_row * _width);
        _tx_row++;
        _row++;
    }
    if (buff != NULL) free(buff);
    return matrix;
}
