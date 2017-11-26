//
// Created by nayana on 11/22/17.
//

#include "bitmap.h"


void functiona_tests() {
    const char *files[3] = {"test-data/8x8-1.bmp", "test-data/65x65-1.bmp", "test-data/8x8-3.bmp"};
    for (int i = 1; i < 2; i++) {
        printf("file: %s \n", files[i]);
        bmp_open(files[i]);
        printf("w*h: %lu * %d [%d] \n", bmp_io->bi_width, bmp_io->height, bmp_io->width);
        printf("px(n) %#0x \n", (*bmp_io->bmp_data & 0b10000000));
        //1,0,0,1,1,0,0,1
        for (int h = 0; h < bmp_io->height; h++) {
            u_int32_t ptr =  (u_int32_t) *(*(bmp_io->ptr_cols + h));

            printf("row %d - %#0x %hd %d \n", h, *(*(bmp_io->ptr_cols + h)),
                   bmp_bcount32(ptr), bmp_row_bit_count(h));
        }


        /*      printf("0,0 %#0x \t %d \n", __col2mask(7), __bit2index(7));
              printf("0,7 %d \t 7,0 %d \t 0,0 %d \n", bmp_px(0, 7), bmp_px(7, 0), bmp_px(0, 0));
              struct ocr_cell *row = malloc(sizeof(struct ocr_cell));
              row->index = 0;
              bmp_row_stat(row);*/
        struct ocr_cell *cell = malloc(sizeof(struct ocr_cell));
        /*    cell->start = -1;
            cell->end = -1;
            cell->r_start = 0;
            cell->r_end = 0;
            struct ocr_cell *root = cell;
            struct ocr_cell *last = bmp_col_stat(0, 0, 1, cell);
            last->r_start = 3; last->r_end = 4;
            last = bmp_col_stat(3, 0, 2, last);
            last->r_start = 7; last->r_end = 7;
            bmp_col_stat(7, 0, 1, last);
            printf("c1\tc2\tr1\tr2\n");
            (cell) = root;
            while (cell->start != -1) {
                printf("%ld\t%ld\t%ld\t%ld\n", cell->start, cell->end, cell->r_start, cell->r_end);
                (cell) = (cell)->next;
            }*/
        printf("-----------------------\n");
        struct ocr_cell *row_root = malloc(sizeof(struct ocr_cell));
        row_root->index = 0;
        struct ocr_cell *stat_last = bmp_stat(row_root);
        (cell) = row_root;
        while (cell->index < stat_last->index) {
            struct ocr_cell *ccell = cell->first;
            while (ccell->index < cell->last->index) {
                printf("%ld\t%ld\t%ld\t%ld\n", ccell->start, ccell->end, ccell->r_start, ccell->r_end);
                (ccell) = (ccell)->next;
            }
            (cell) = (cell)->next;
        }

    }

}

void bmp_calc_tests()
{
    int dimensions[4][2] = {
            {3, 65}, {1, 31}, {2, 33},

    };

    /**
     * /*unsigned int row = bmp_io->height;
    bmp_io->n_rpx = malloc(sizeof(unsigned int) * bmp_io->height);
    *(bmp_io->ptr_cols) =  (bmp_io->pixels + bmp_row_offset(0));
    while (row < bmp_io->height) {
        *(bmp_io->ptr_cols+row) =  *(bmp_io->ptr_cols)
        *(bmp_io->n_rpx+row) = 0;
        row--;
    }*/


    bmp_open("test-data/8x8-5.bmp");
    printf("height %d width %d bi-width %ld int width %d \n", bmp_io->height, bmp_io->width, bmp_io->bi_width, bmp_io->b_height);
    printf("end 11 %d 17 %d 25 %d 23 %d 31 %d  34 %d \n",  bmp_edge_mask(11), bmp_edge_mask(17), bmp_edge_mask(25), bmp_edge_mask(23), bmp_edge_mask(31), bmp_edge_mask(34));
    unsigned int **matrix = bmp_init_matrix(bmp_io->bmp_data, bmp_io->height, bmp_io->width);
    unsigned int row = 0;
    while(row < bmp_io->height) {
        bmp_draw_row(matrix, row, bmp_io->width, bmp_io->bi_width);
        row++;
    }

    /*for (int i = 0; i < 1; i++) {
        printf("%d -  %d \n ", bmp_io->width,  bmp_io->width == dimensions[i][0]);
        printf("%d -  %d \n ", bmp_io->height,  bmp_io->height == dimensions[i][1]); //bmp_io->height = dimensions[i][1];

        printf("%d %d %ld\n", dimensions[i][0], dimensions[i][1], bmp_row_offset(1));
    }*/
}

int main() {
    bmp_calc_tests();
        return 0;
}