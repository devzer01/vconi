//
// Created by nayana on 19/11/2560.
//

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

int drawchar(int row_start, int row_end, int col_start, int col_end, struct bmp_px_matrix **xbase)
{
    struct bmp_px_matrix *lbase = *xbase;
    while (lbase->px->row < row_start) (lbase) = lbase->bottom;
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
    }

    return 0;
}

int main() {
    BITMAPINFOHEADER bitmapInfoHeader;
    //base = malloc(sizeof(struct bmp_px_matrix));
    //struct bmp_col_stat *base_col = malloc(sizeof(struct bmp_col_stat));
    //base_col->npix = 0;
    //base_row = malloc(sizeof(struct bmp_row_stat));
    //base_row->npix = 0;
    //struct bmp_px_matrix *lbase = malloc(sizeof(struct bmp_px_matrix));
    //lbase =
            LoadBitmapFile("data/bitmap/sample.bmp", &bitmapInfoHeader, &base);
    //now do what you want with it, later on i will show you how to display it in a normal window
    /*if (lbase == NULL) {
        dprintf(2, "error opening file\n");
        exit(-1);
    }
*/
    /*printf("print row and col stats\n");
    struct ocr_gap *row_gap = malloc(sizeof(struct ocr_gap));
    struct ocr_gap *root_col_gap = row_gap;
    row_gap->col_gap_start = 0;
    row_gap->col_gap_end = 0;
    struct bmp_row_stat *row_node = base_row;
*/



   /* while(row_node != 0x0) {

        while(row_node->npix == 0) (row_node) = row_node->bottom;
        struct bmp_row_stat *char_row_start = row_node;
        while(row_node->npix > 0) (row_node) = row_node->bottom;
        struct bmp_row_stat *char_row_end = row_node;
        printf("row start %ld and end %ld \n", char_row_start->row, char_row_end->row);
        row_node = char_row_start;
        struct bmp_col_stat *char_col_stat = malloc(sizeof(struct bmp_col_stat));
        struct bmp_col_stat *ptrCharStart = char_col_stat;
        for(unsigned long int h = char_row_start->row; h <= char_row_end->row; h++) {
            struct bmp_col_stat *lcol_stat_node = row_node->base_col_stat;
            unsigned long int t_col = 0; //bitmapInfoHeader.biWidth;
            while(t_col < bitmapInfoHeader.biWidth) {
                if (lcol_stat_node->row == char_row_start->row) {
                    char_col_stat->col = lcol_stat_node->col;
                } else if (char_col_stat->col != lcol_stat_node->col) {
                    printf("column miss match %ld %ld \n", char_col_stat->col, lcol_stat_node->col);
                }
                char_col_stat->npix += lcol_stat_node->npix;
                struct bmp_col_stat *tcstat = malloc(sizeof(struct bmp_col_stat));
                char_col_stat->right = tcstat;
                tcstat->left = char_col_stat;
                (char_col_stat) = tcstat;
                t_col = lcol_stat_node->col+1;
                (lcol_stat_node) = lcol_stat_node->right;


            }
            (char_col_stat) = ptrCharStart;
        }

        (char_col_stat) = ptrCharStart;
        printf("width %d \n", bitmapInfoHeader.biWidth);
        while(char_col_stat->col < bitmapInfoHeader.biWidth - 1) {
            if (char_col_stat->npix == 0 && char_col_stat->right->npix != 0) {
                printf("(%ld,%ld) %d ", char_col_stat->row, char_col_stat->col, char_col_stat->right->npix);
            }
            (char_col_stat) = char_col_stat->right;
        }

        exit(-1);
        //printf("row count %d - %d\n", row_node->row, row_node->npix);
        //this is close but we need to first find the gaps in horizontal space
        //for each non gap area we need to do a full cumulative gap count vertically
       *//* struct bmp_col_stat *col_node = row_node->base_col_stat;
        while(col_node != 0x0) {
            if ((col_node->right != 0x0 && col_node->npix != col_node->right->npix) || (col_node->left != 0x0 && col_node->npix != col_node->left->npix)) {
                printf(" %ld,%ld ", row_node->row, col_node->col);
            }

            (col_node) = col_node->right;
        }
        printf("\n");*//*

        *//*if (row_node->top != 0x0 && row_node->top->npix != 0 && row_node->npix == 0) {
            printf("row count %d - %d\n", row_node->row, row_node->npix);
            row_gap->row_gap_start = row_node->row;
        }
        
        if (row_node->npix == 0 && row_node->bottom != 0x0 && row_node->bottom->npix != 0) {
            row_gap->row_gap_end = row_node->bottom->row;
            struct bmp_col_stat *col_node = row_node->base_col_stat;
            row_gap->col = malloc(sizeof(struct ocr_gap));
            struct ocr_gap *col_gap = row_gap->col;
            while (col_node != 0x0) {
                //printf("col count %d - %d\n", col_node->col, col_node->npix);
                if (col_node->npix == 0 && col_node->right != 0x0 && col_node->right->npix != 0) {
                    col_gap->col_gap_end = col_node->right->col;
                    col_gap->next = malloc(sizeof(struct ocr_gap));
                    col_gap->next->prev = col_gap;
                    (col_gap) = col_gap->next;
                }

                if (col_node->left != 0x0 && col_node->left->npix != 0 && col_node->npix == 0) {
                    col_gap->col_gap_start = col_node->col;
                }

                (col_node) = col_node->right;
            }
            
            row_gap->next = malloc(sizeof(struct ocr_gap));
            row_gap->next->prev = row_gap;
            (row_gap) = row_gap->next;
        }*//*

        

        (row_node) = row_node->bottom;
        
        
    }

    row_gap = root_col_gap;
    struct ocr_gap *xcol_gap;
    while (row_gap != 0x0) {
        xcol_gap = row_gap->col;
        while (xcol_gap != 0x0 && xcol_gap->next != 0x0) {
            int x = drawchar(row_gap->row_gap_end, row_gap->next->row_gap_start, xcol_gap->col_gap_end,
                             xcol_gap->next->col_gap_start, &lbase);
            (xcol_gap) = xcol_gap->next;
        }

        (row_gap) = row_gap->next;
    }*/

    return 0;
}



//......