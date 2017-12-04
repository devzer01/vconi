//
// Created by nayana on 11/28/17.
//

#include "shape.h"

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


/**
 *
 * @param row
 * @param col
 * @return
 */
short bmp_px(unsigned long int row, unsigned long int col)
{
    //if (row > bmp_io->height) row--;
    unsigned int mask = __bmp_col2mask(col);
    unsigned long int __index = bmp_io->ints.width * ((bmp_io->px.height - row) - 1);
    __index = __index + __bmp_bit2intidx(col);
    if (bmp_io->bmp_data[__index] & mask) {
        return 1;
    }
    return 0;
}