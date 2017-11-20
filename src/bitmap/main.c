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
    base = malloc(sizeof(struct bmp_px_matrix));
    base_col = malloc(sizeof(struct bmp_col_stat));
    base_col->npix = 0;
    base_row = malloc(sizeof(struct bmp_row_stat));
    base_row->npix = 0;
    struct bmp_px_matrix *lbase = malloc(sizeof(struct bmp_px_matrix));
    lbase = LoadBitmapFile("data/bitmap/sample.bmp", &bitmapInfoHeader, &base);
    //now do what you want with it, later on i will show you how to display it in a normal window
    if (lbase == NULL) {
        dprintf(2, "error opening file\n");
        exit(-1);
    }

    printf("print row and col stats\n");
    struct ocr_gap *gap = malloc(sizeof(struct ocr_gap));
    struct ocr_gap *root_col_gap = gap;
    gap->col_gap_start = 0;
    gap->col_gap_end = 0;
    struct bmp_col_stat *node;
    node = base_col;
    int rstart = 0, rend = 0;
    while(node != 0x0) {
        if (node->npix == 0 && node->right != 0x0 && node->right->npix != 0) {
            gap->col_gap_end = node->right->col;
            gap->next = malloc(sizeof(struct ocr_gap));
            gap->next->prev = gap;
            (gap) = gap->next;
        }

        if (node->left != 0x0 && node->left->npix != 0 && node->npix == 0) {
            gap->col_gap_start = node->col;
        }

        (node) = node->right;
    }
    struct bmp_row_stat *row_node;
    row_node = base_row;
    struct ocr_gap *row_gap = malloc(sizeof(struct ocr_gap));
    struct ocr_gap *root_row_gap = row_gap;
    while(row_node != 0x0) {
        if (row_node->npix == 0 && row_node->bottom != 0x0 && row_node->bottom->npix != 0) {
            row_gap->row_gap_end = row_node->bottom->row;
            row_gap->next = malloc(sizeof(struct ocr_gap));
            row_gap->next->prev = row_gap;
            (row_gap) = row_gap->next;
        }

        if (row_node->top != 0x0 && row_node->top->npix != 0 && row_node->npix == 0) {
            row_gap->row_gap_start = row_node->row;
        }

        (row_node) = row_node->bottom;
    }

    gap = root_col_gap;
    row_gap = root_row_gap;
    while (row_gap != 0x0) {
        while (gap != 0x0) {
            int x = drawchar(row_gap->row_gap_end, row_gap->next->row_gap_start, gap->col_gap_end,
                             gap->next->col_gap_start, &lbase);
            (gap) = gap->next;
        }

        (row_gap) = row_gap->next;
        (gap) = root_col_gap;

    }

    return 0;
}



//......