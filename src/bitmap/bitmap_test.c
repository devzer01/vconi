//
// Created by nayana on 11/22/17.
//

#include "bitmap.h"

int main() {
    const char *files[3] = {"test-data/8x8-1.bmp", "test-data/8x8-2.bmp", "test-data/8x8-3.bmp"};
    for (int i = 0; i < 3; i++) {
        printf("file: %s \n", files[i]);
        bmp_open(files[i]);
        printf("w*h: %lu * %d \n", bmp_io->bi_width, bmp_io->height);
        printf("px(n) %#0x \n", (*bmp_io->pixels & 0b10000000));
        //1,0,0,1,1,0,0,1
        for (int h = 0; h < bmp_io->height; h++) {
            printf("row %d - %#0x %hd %d \n", h, *(*(bmp_io->ptr_cols + h)),
                   bmp_bcount32(*(*(bmp_io->ptr_cols + h))), bmp_row_stat(h));
        }
        struct ocr_cell *rcell = bmp_stat();
        struct ocr_cell *root = rcell;
        short n_cell = 0;
        do {
            n_cell++;
            if (0x0 != (rcell) && (rcell->next)) {
                (rcell) = rcell->next;
            } else {
                rcell = 0x0;
            }
        } while(0x0 != rcell);
        printf("found n %d cells \n", n_cell);
        rcell = root;
        short index = 0;
        while(index < n_cell) {
            printf("%ld,%ld - %ld,%ld \n", rcell->r_start, rcell->start, rcell->r_end, rcell->end);
            index++;
            (rcell) = rcell->next;
        }

        //printf("found n %d cells \n", n_cell);
        /*void *mask = (void *) "\x06\x05\x04\x03\x02\x01\x04\x03"; //012
        void *mem  = (void *) "\x10\x0f\x0e\x0d\x0c\x0b\x0a\x09";  //ef = 0 //cd = 1 //ab = 2 //89 == 3
        bmp_flip(mem, mask);*/
           /* *mask = (unsigned int) 0x11001004;
                bmp_flipw(mask);
           */
        /*for (int h = 0; h < bmp_io->height; h++) {
            printf("row %d - %#0x \n", h, *(*(bmp_io->ptr_cols + h)));
        }*/
    }
    return 0;
}