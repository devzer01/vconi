//
// Created by nayana on 11/22/17.
//

#include "bitmap.h"
#include "stats.h"

char *filename;

bmp_io_t test_data[3] =
        {
                {
                 .filename = "test-data/8x8-1.bmp",
                 .bit_per_px = 1,
                 .px.width = 8,
                 .px.height = 8,
                 .ints.width = 1,
                 .ints.height = 1,
                 .chars.width = 4,
                 .chars.height = 4
                },
                {
                .filename = "test-data/8x8-5.bmp",
                .bit_per_px = 1,
                .px.width = 11,
                .px.height = 11,
                .ints.width = 1,
                .ints.height = 1,
                .chars.width = 4,
                .chars.height = 4
                },
                {
                        .filename = "test-data/65x65-1.bmp",
                        .bit_per_px = 1,
                        .px.width = 65,
                        .px.height = 65,
                        .ints.width = 3,
                        .ints.height = 3,
                        .chars.width = 12,
                        .chars.height = 12
                },

        };


void _load()
{
    if (filename != NULL) {
        bmp_open(filename);
    } else {
        bmp_open("test-data/8x8-1.bmp");
    }
}

void bmp_static_test()
{
    unsigned long int data[4*3][2] = {
            {8, 0}, {7, 0}, {31, 0}, {33, 1},
            {32, 0}, {0, 0}, {65, 0}, {64, 1},
            {9, 0}, {96, 0}, {75, 0}, {39, 1},
    };
    for (int i = 0; i < 12; i++) {
        printf("col %ld %ld int-idx %#0x - %#0x \n",
               data[i][0], data[i][1],
               __bmp_bit2intidx(data[i][0]),
               __bmp_col2mask(data[i][0]));
    }
}

void bmp_position_test()
{
   if (filename != NULL) {
    bmp_open(filename);
   } else {
    bmp_open("test-data/8x8-1.bmp");
   }

    printf("col2charmask(0) %#0x \n", __bmp_col2mask(0));
    unsigned int index = bmp_row_offset(0); // if negative then out of bound
    /*printf("offset 0:%d %#0x b:"
                   PRINTF_BINARY_PATTERN_INT32 "\n", index,
           bmp_io->bmp_data[index],
           PRINTF_BYTE_TO_BINARY_INT32(bmp_io->bmp_data[index]));*/
    unsigned int *buffer = malloc(sizeof(unsigned int) * bmp_io->ints.width);
    buffer = bmp_row_buffer(0, &buffer, bmp_io->ints.width);
    short c_col = 0;
    while (c_col < bmp_io->ints.width) {
        printf("b:%#08X %#08X %#08X b:"
                       PRINTF_BINARY_PATTERN_INT32 "\n", c_col, bmp_io->bmp_data[index]+c_col, ptrval(buffer, c_col),
               PRINTF_BYTE_TO_BINARY_INT32(ptrval(buffer, c_col)));
        c_col++;
    }
    free(buffer);

    unsigned int *char_buffer = (unsigned int *) malloc(sizeof(unsigned int) * bmp_io->px.height);
    char_buffer = bmp_col_buffer(0, &char_buffer, bmp_io->px.height);
    unsigned int bitcount = bmp_col_bit_count(0);
    c_col = 0;
    free(buffer);
    while (c_col < bmp_io->px.height) {
        buffer = malloc(sizeof(unsigned int) * 3);
        buffer = bmp_row_buffer(c_col, &buffer, 3);
        printf("b:%d %#0x %#0x b:"
                       PRINTF_BINARY_PATTERN_INT32 ", " PRINTF_BINARY_PATTERN_INT32 "\n", c_col, char_buffer[index]+c_col, bitcount,
               PRINTF_BYTE_TO_BINARY_INT32(*(char_buffer+c_col)), PRINTF_BYTE_TO_BINARY_INT32(*buffer));
        c_col++;
        free(buffer);
    }
    unsigned long int __row = 3, __col = 8;

 /*   for(int i = 0; i < bmp_io->px.height; i++) {
        unsigned int mask = __col2intmask(i);
        printf("%#2d " PRINTF_BINARY_PATTERN_INT32 "\n", i , PRINTF_BYTE_TO_BINARY_INT32(mask));
    }*/

    /*unsigned int _offset = (col / 31);
    unsigned long int _height = bmp_io->ints.height - 1;
    while(_height <= 0) {

        u_int32_t val = (u_int32_t) (ptrval(buffer,_offset) & __col2intmask(col));
        bmp_io->col_px_count[col] += bmp_bcount32(val);
        _height--;
    }*/

    u_int32_t val = (u_int32_t)(ptrval(char_buffer, __row) & __bmp_col2mask(__col));
    printf(PRINTF_BINARY_PATTERN_INT32 "\n"
                   PRINTF_BINARY_PATTERN_INT32 "\n"
                   PRINTF_BINARY_PATTERN_INT32 "\n", PRINTF_BYTE_TO_BINARY_INT32(ptrval(char_buffer, __row)),
           PRINTF_BYTE_TO_BINARY_INT32(__bmp_col2mask(__col)), PRINTF_BYTE_TO_BINARY_INT32(val));

    /*for (int i = 0; i < bmp_io->px.width; i++) {
        printf("col %d bit count %d \n", i, bmp_col_bit_count(i));
    }
*/
    for(int r = 2; r < 4; r++) {
        for (int i = 0; i < bmp_io->px.width; i++) {
            char_buffer = bmp_col_buffer_offset(i, &char_buffer, r, 5);
            unsigned int counter = bmp_col_bit_count_offset(i, r, 5);
            printf("%d:bit " PRINTF_BINARY_PATTERN_INT32 " %d \n", i, PRINTF_BYTE_TO_BINARY_INT32(*char_buffer),
                   counter);
        }
    }

    unsigned int *buff = bmp_row_counts();
    int i = 0;
    while (i < bmp_io->px.height) {
        printf("c:%d %d \n", i, *(buff+i));
        i++;
    }

    unsigned int *cbuff = bmp_col_counts();
     i = 0;
    while (i < bmp_io->px.width) {
        printf("c:%d %d \n", i, *(cbuff+i));
        i++;
    }

    /*printf("b:0 %#0x %#0x \n", bmp_io->bmp_data[index]+1, *buffer+1);
    printf("b:0 %#0x %#0x \n", bmp_io->bmp_data[index]+2, *buffer+2);*/

    //printf("row data %#0x %#0x %#0x \n", *(bmp_io->bmp_data+index), *(bmp_io->bmp_data+index+1), bmp_io->bmp_data[index+2] );
    //int i = 0;
    /*while(i < bmp_io->ints.width) {
        printf("test %d ", bmp_io->bmp_data[index+i]);
        i++;
    }*/
    /**
     * int main() {
    long long int flag = 1648646756487983144ll;
    printf("My Flag "
                   PRINTF_BINARY_PATTERN_INT64 "\n",
           PRINTF_BYTE_TO_BINARY_INT64(flag));
    return 0;
}
     */
    /*for (int i = 0; i < bmp_io->px.height; i++) {
        for (int x = 0; x < bmp_io->px.width; x++) {
            //printf(" %d ", bmp_px(i, x));
        }
        printf("\n");
    }*/
}

void bmp_test_init()
{
    for (int i = 0; i < 3; i++) {

        bmp_open(test_data[i].filename);

        struct bmp_dimension _px[2] = {bmp_io->px, test_data[i].px};
        struct bmp_dimension _ints[2] = {bmp_io->ints, test_data[i].ints};
        struct bmp_dimension _chars[2] = {bmp_io->chars, test_data[i].chars};


        printf("pixels %lu %lu - %lu  %lu\n", 
               _px[0].width, _px[1].width, _px[0].height, _px[1].height);

        printf("ints %lu %lu - %lu  %lu\n",
               _ints[0].width, _ints[1].width, _ints[0].height, _ints[1].height);

        printf("chars %lu %lu - %lu  %lu\n",
               _chars[0].width, _chars[1].width, _chars[0].height, _chars[1].height);

    }
}

void stat_unit_test_row_col()
{
    _load();

    stat_row *root = stat_row_get();
    stat_row *cell = root;
    while (cell != NULL) {
        printf("i: %d s: %ld :e %ld \n", cell->index, cell->gap.start, cell->gap.end);
        (cell) = cell->next;
    }

    root = stat_col_get();
    cell = root;
    while (cell != NULL) {
        printf("i: %d s: %ld :e %ld \n", cell->index, cell->gap.start, cell->gap.end);
        (cell) = cell->next;
    }
}

void stat_unit_test()
{
    _load();

    stat_cell *root_cell = stat_cell_get();
    stat_cell *cell = root_cell;
    while(cell != NULL) {

        printf(" [(%ld, %ld),(%ld, %ld)] , ", cell->row.start, cell->col.start, cell->row.end, cell->col.end);
        unsigned char *buffer = bmp_matrix_get(&cell);
        printf("%s", buffer);
        if (cell->next != NULL && cell->row.start!= cell->next->row.start) {
            printf("\n");
        }

        (cell) = cell->next;

    }
    printf("\n");
}

void cell_raw_test()
{
    _load();

    stat_row *row_root = stat_row_get();
    //stat_row *col_root = stat_col_get();
    stat_row *_row = row_root;
    //stat_row *_col = col_root;
    while (_row != NULL) {
        //printf("(%d) => [%ld,%ld] => ", _row->index, _row->gap.start, _row->gap.end);
        stat_row *col_root = stat_col_get_offset(0, bmp_io->px.width, _row->gap.start, (_row->gap.end - _row->gap.start) + 1);
        stat_row *_col = col_root;
        while(_col != NULL) {
            //printf("(%d) [%ld,%ld] ", _col->index, _col->gap.start, _col->gap.end);
            printf(" [(%ld, %ld),(%ld, %ld)] , ", _row->gap.start, _col->gap.start, _row->gap.end, _col->gap.end);
            (_col) = _col->next;
        }
        printf("\n");
        (_row) = _row->next;
    }
}

void bmp_offset_test()
{
    if (filename != NULL) {
        bmp_open(filename);
    } else {
        bmp_open("test-data/8x8-1.bmp");
    }
    for (int i = 0; i < bmp_io->px.width; i++) {
        printf("%d, 2, 1 %d \n", i, bmp_col_bit_count_offset(i, 0, 8));
    }
}

int main(int argc, char **argv)
{
    filename = argv[1];
    char t_case = *argv[2];
    switch (t_case) {
        //bmp_test_init();
        //bmp_static_test();
        //bmp_position_test();
        case 'r':
            cell_raw_test();
            break;
        case 'o':
            bmp_offset_test();
            break;
        default:
            stat_unit_test();
            break;
    }

    return 0;
}
