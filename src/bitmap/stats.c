//
// Created by nayana on 11/28/17.
//

#include "bitmap.h"
#include "stats.h"

struct stat_row_t *stat_row_get()
{
    unsigned int *buff = bmp_row_counts();
    return stat_gaps(buff, 0, bmp_io->px.height);
}

struct stat_row_t *stat_col_get()
{
    unsigned int *buff = bmp_col_counts();
    return stat_gaps(buff, 0, bmp_io->px.width);
}

struct stat_row_t *stat_col_get_offset(unsigned long int col_start, unsigned long int col_end, unsigned long int row_start, unsigned long int height)
{
    unsigned int *buff = bmp_col_counts_offset(col_start, col_end, row_start, height);
    return stat_gaps(buff, col_start, col_end);
}

struct stat_cell_t *stat_cell_get()
{
    stat_cell *cell_root = malloc(sizeof(struct stat_cell_t));
    stat_cell *_cell = cell_root;
    stat_row *row_root = stat_row_get();
    stat_row *_row = row_root;
    while (_row != NULL) {
        stat_row *col_root = stat_col_get_offset(0, bmp_io->px.width, _row->gap.start, (_row->gap.end - _row->gap.start) + 1);
        stat_row *_col = col_root;
        while(_col != NULL) {
            memcpy(&_cell->row, &_row->gap, sizeof(struct stat_gap_t));
            memcpy(&_cell->col, &_col->gap, sizeof(struct stat_gap_t));
            _cell->next = malloc(sizeof(struct stat_cell_t));
            (_cell) = _cell->next;
            (_col) = _col->next;
        }
        (_row) = _row->next;
    }
    return cell_root;
}

struct stat_row_t *stat_gaps(unsigned int *buff, unsigned int start, unsigned int end)
{
    stat_row *root = malloc(sizeof(stat_row));
    root->index = -1;
    p_stat_row cell = root;
    int i = start;
    int gap_count = 0;
    while (i < end) {
        if ((cell->index == -1 && *(buff+i) != 0) || ( i > 0 && *(buff+i-1) == 0 && *(buff+i) != 0)) {
            cell->gap.start = i;
            cell->index = gap_count;
            gap_count++;
        }
        if (i > 0 && (*(buff+i-1) != 0 && *(buff+i) == 0) || ((i == end - 1) && cell->index != -1)) {
            if (i != end - 1) {
                cell->gap.end = i - 1;
            } else {
                cell->gap.end = i;
            }
            cell->next = malloc(sizeof(stat_row));
            cell->next->index = -1;
            (cell) = cell->next;
        }
        i++;
    }

    return root;
}

/*
struct ocr_cell *bmp_stat(struct ocr_cell *root)
{
    //struct ocr_cell *row_stat = malloc(sizeof(struct ocr_cell));
    struct ocr_cell *last_row = bmp_row_stat(root);

    //struct ocr_cell **cell = malloc(sizeof(struct ocr_cell *) * 24);
    //struct ocr_cell *cell = malloc(sizeof(struct ocr_cell));
    struct ocr_cell *rcell = root;
    //struct ocr_cell *cell = malloc(sizeof(struct ocr_cell));;
    while(rcell->index < last_row->index) {
        rcell->first = malloc(sizeof(struct ocr_cell));
        rcell->first->index = 0;
        rcell->first->r_start = rcell->start;
        rcell->first->r_end = rcell->end;
        rcell->last = bmp_col_stat(rcell->first->r_start, 0, (rcell->end - rcell->start) + 1, rcell->first);
        (rcell) = rcell->next;
    }

    return last_row;

}


*/
/**
 * @test pass
 * @param row
 * @param col
 * @param height
 * @param cell
 * @return
 *//*

struct ocr_cell *bmp_col_stat(unsigned long int row, unsigned long int col, unsigned long int height, struct ocr_cell *cell)
{
    short px_count = 0, last_px_count = 0;
    struct ocr_cell *root = cell;
    while (col < bmp_io->px.width) {
        px_count = 0;
        unsigned long int _row = row;
        while (_row < (row + height)) {
            px_count += bmp_px(_row, col);
            _row++;
        }
        if (last_px_count == 0 && px_count != 0) {
            (cell)->start = col;
        }
        if (last_px_count != 0 && px_count == 0 && (cell)->start != -1) {
            (cell)->end = col - 1;
            //(cell)->r_end = _row - 1;
            (cell) = bmp_cell_init(cell);
            (cell)->r_start = row;
            (cell)->r_end = (_row  - 1);
        }
        last_px_count = px_count;
        col++;
    }
    if ((cell)->end == -1 && (cell)->start != -1) {
        (cell)->end = bmp_io->px.width - 1;
        (cell) = (bmp_cell_init(cell));
    }
    return (cell);
}


*/
/**
 * @test pass
 * @param prev
 * @return
 *//*

struct ocr_cell *bmp_cell_init(struct ocr_cell *prev)
{
    prev->next = malloc(sizeof(struct ocr_cell));
    prev->next->index = prev->index + 1;
    (prev->next)->prev = (prev);
    prev->next->start = -1;
    prev->next->end = -1;
    return prev->next;
}
*/
