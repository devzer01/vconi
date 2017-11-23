//
// Created by nayana on 19/11/2560.
//

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

unsigned int gayanna[25] = {
         0x0
        ,0x0
        ,0x0
        ,0x0
        ,0x0
        ,0x0
        ,0x0f38
        ,0x3f86
        ,0x3fc2
        ,0x3841
        ,0x7021
        ,0x70e1
        ,0x6081
        ,0x6081
        ,0x6187
        ,0x31ff
        ,0x10fe
        ,0x0f7c
        ,0x0200
        ,0x0
        ,0x0
        ,0x0
        ,0x0
        ,0x0
        ,0x0

};

int drawchar(int s_row, int s_col, int e_row, int e_col, struct bmp_px_row *bmp_row)
{
    if (bmp_row->row != s_row) {
        printf("row missmatch\n");
    }
    struct bmp_px_row *head = bmp_row;
    unsigned int byteIndex = (unsigned int) (s_col / 8);
    printf("byteIndex %d \n", byteIndex);
    unsigned char mask = 0b10000000;
    if (s_col % 8 > 0) {
        mask = mask >> ((s_col % 8) - 1);
        //byteIndex++;
    }
    unsigned int column = s_col;
    printf("     ");
    /*while (column <= e_col) {
        printf(" %d  ", column++);
    }*/
    column = s_col;
    printf("\n");
    int cursor = 0;
    float prob = 0;
    while (bmp_row->row <= e_row) {
        //printf(" %d : ", bmp_row->row);
        unsigned int colhash = 0;
        while (column <= e_col) {
            while (mask > 0 && column <= e_col) {
                if ((bmp_row->bitmap_row[byteIndex] & mask) == mask) {
                    colhash += 1 << (column - s_col);
                   printf("1");
                } else {
                   printf(".");
                }
                column++;
                mask = mask >> 1;
            }
            byteIndex++;
            mask = 0b10000000;
        }
        int lastx = gayanna[cursor];
        printf(" : %#0x %d ", colhash, colhash);
        int xor = colhash ^ gayanna[cursor];
        int x = bitcount(xor);
        int anad = colhash & gayanna[cursor];
        int xand = bitcount(anad);
        if (colhash == (colhash & gayanna[cursor]) || ((colhash >> 2) ==  ((colhash >> 2) & gayanna[cursor])) || ((colhash << 2) == ((colhash << 2) & gayanna[cursor]))) {
            prob += 1.0 / 25.0;
            cursor++;
        }

        printf(" prob %f matched rows %d (%d) (-%d) %d \n", prob * 100, cursor, lastx, x, xand);
        //cursor = 0;
        (bmp_row) = bmp_row->bottom;
        column = s_col;
        byteIndex = (s_col / 8);
        if (s_col % 8 > 0) {
            mask = mask >> ((s_col % 8) - 1);
            //byteIndex++;
        }
    }

    if (prob > 0.7) {
        printf("found near match\n");
    }

   /* while (lbase->px->row < row_start) (lbase) = lbase->bottom;
    while (lbase->px->col < col_start) (lbase) = lbase->right;
    struct bmp_px_matrix *charbase = lbase;
    printf("req %d,%d - %d,%d to %ld %ld \n", row_start, col_start, row_end, col_end, charbase->px->row, charbase->px->col);
    int colHash;
    while (lbase->px->row < row_end && lbase->px->col < col_end) {
        if (lbase->px->col == col_start) colHash = 0;
        if (lbase->px->px == 0) {
            printf(".");
        } else {
            colHash += 1 << (lbase->px->col - col_start);
            printf("8");
        }
        if (lbase->right->px->col >= col_end) {
            printf(" - %#0x %d \n", colHash, colHash);
            (lbase) = charbase->bottom;
            (charbase) = charbase->bottom;
        } else {
            (lbase) = lbase->right;
        }
    }*/

    return 0;
}

int main() {
    BITMAPINFOHEADER bitmapInfoHeader;
    //LoadBitmapFile("data/bitmap/sample.bmp", &bitmapInfoHeader);
    bmp_open("data/bitmap/sample.bmp");
   /* struct ocr_cell *or_cell;
    or_root = ocr_row_root;
    printf("cell breakdown \n");
    int scanning = 1;
    int cnt = 0;
    while (scanning == 1) {

        (or_cell) = or_root->first_cell;

        while (or_cell != 0x0 && or_cell->next->start > or_cell->end) {
            printf(" (%d,%d) - (%d,%d) \n", or_cell->or_row->start, or_cell->start, or_cell->or_row->end,
                   or_cell->end);
           //if (cnt == 0 || cnt == 6)
               drawchar(or_cell->or_row->start, or_cell->start, or_cell->or_row->end, or_cell->end, or_cell->or_row->row);
            //cnt++; //exit(-1);
            (or_cell) = or_cell->next;
        }

        printf("\n");
        (or_root) = or_root->next;
        if (or_root->start < or_root->prev->end) {
            scanning = 0;
        }
    }
*/
    return 0;
}



//......