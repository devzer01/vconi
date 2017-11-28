//
// Created by nayana on 11/22/17.
//

#include "bitmap.h"

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

void bmp_static_test()
{
    unsigned long int data[4*3][2] = {
            {8, 0}, {7, 0}, {31, 0}, {33, 1},
            {32, 0}, {0, 0}, {65, 0}, {64, 1},
            {9, 0}, {96, 0}, {75, 0}, {39, 1},
    };
    for (int i = 0; i < 12; i++) {
        printf("col %ld %ld int-idx %d char-idx %d - %#0x - %#0x \n",
               data[i][0], data[i][1],
               __bmp_bit2intidx(data[i][0]),
               __bmp_bit2charidx(data[i][0]),
               __col2charmask(data[i][0]),
               __col2intmask(data[i][0])
        );
    }
}

void bmp_position_test()
{
   if (filename != NULL) {
    bmp_open(filename);
   } else {
    bmp_open("test-data/65x65-1.bmp");
   }

    printf("col2charmask(0) %#0x \n", __col2charmask(0));
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
    unsigned long int __row = 0, __col = 8;

    for(int i = 0; i < bmp_io->px.height; i++) {
        unsigned int mask = __col2intmask(i);
        printf("%d " PRINTF_BINARY_PATTERN_INT32 "\n", i , PRINTF_BYTE_TO_BINARY_INT32(mask));
    }

    u_int32_t val = (u_int32_t) (ptrval(char_buffer,__row) & __col2intmask(__col));
    printf(PRINTF_BINARY_PATTERN_INT32 "\n"
                   PRINTF_BINARY_PATTERN_INT32 "\n"
                   PRINTF_BINARY_PATTERN_INT32 "\n", PRINTF_BYTE_TO_BINARY_INT32(ptrval(char_buffer,__row)), PRINTF_BYTE_TO_BINARY_INT32(__col2intmask(__col)), PRINTF_BYTE_TO_BINARY_INT32(val));


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


int main(int argc, char **argv)
{
   filename = argv[1];
    //bmp_test_init();
    bmp_static_test();
    bmp_position_test();
    return 0;
}
