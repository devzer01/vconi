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

unsigned int gap_same(struct stat_gap_t gapa, struct stat_gap_t gapb)
{
    if (gapa.start == gapb.start && gapa.end == gapb.end) return 1;
    return 0;
}


struct stat_cell_t *stat_cell_get_filter()
{
    stat_cell *root_cell = stat_cell_get();
    stat_cell *cell = root_cell;
    while(cell != NULL) {
        unsigned int _i = 0;
        while (_i + cell->row.start < cell->row.end) {
            unsigned int count = bmp_row_bit_count_partial((cell->row.start + _i), cell->col.start, cell->col.end);
            if (count == 0 && cell->row.end != (_i + cell->row.start)) {
                cell->row.end = (_i + cell->row.start) + 1;
                break;
            }
            _i++;
        }
        if (cell->next != NULL && gap_same(cell->col, cell->next->col) == 1 && gap_same(cell->row, cell->next->row) == 1) {
            (cell->next) = cell->next->next;
        }
        (cell) = cell->next;
    }
    return root_cell;
}

struct stat_cell_t *stat_cell_get()
{
    stat_cell *cell_root = malloc(sizeof(struct stat_cell_t));
    stat_cell *_cell = cell_root;
    stat_row *row_root = stat_row_get();
    stat_row *_row = row_root;
    unsigned int index = 0;
    while (_row != NULL && _row->index != -1) {
        stat_row *col_root = stat_col_get_offset(0, bmp_io->px.width, _row->gap.start, (_row->gap.end - _row->gap.start) + 1);
        stat_row *_col = col_root;
        while(_col != NULL && _col->index != -1) {
            /*int _i = _row->gap.start, cumul = 0;
            stat_gap _gap = {.start = _row->gap.start, .end = _row->gap.end };
            while (_i < _row->gap.end) {
                unsigned int count = bmp_row_bit_count_partial(_i, _col->gap.start, _col->gap.end);
                if (cumul == 0 && count != 0) {
                    _gap.start = _i;
                } else if (cumul != 0 && count == 0) {
                    _gap.end = _i;
                }
                cumul += count;
                _i++;
            }*/
            //_cell->row = _gap;
            memcpy(&_cell->row, &_row->gap, sizeof(struct stat_gap_t));
            memcpy(&_cell->col, &_col->gap, sizeof(struct stat_gap_t));
            _cell->index = ++index;
            _cell->next = malloc(sizeof(struct stat_cell_t));
            _cell->next->index = -1;
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
        if (cell->index == -1 && (*(buff+i) != 0)) {
            cell->gap.start = i;
            cell->gap.end = end - 1;
            cell->index = gap_count;
            gap_count++;
        } else if (cell->index != -1 && (*(buff+i) == 0)) {
            cell->gap.end = i - 1;
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
