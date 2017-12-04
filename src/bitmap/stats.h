//
// Created by nayana on 11/28/17.
//

#ifndef VCONI_STATS_H
#define VCONI_STATS_H


typedef struct stat_gap_t {
    unsigned long int start;
    unsigned long int end;
} stat_gap;

typedef struct stat_point_t {
    unsigned long int row;
    unsigned long int col;
} stat_point;

typedef struct stat_cell_t {
    struct stat_gap_t row;
    struct stat_gap_t col;
    struct stat_cell_t *next;
} stat_cell;

typedef struct stat_row_t {
    int index;
    stat_gap gap;
    struct stat_row_t *next;
} stat_row, *p_stat_row;

struct stat_row_t *stat_row_get();
struct stat_row_t *stat_col_get();
struct stat_row_t *stat_gaps(unsigned int *buff, unsigned int start, unsigned int end);
struct stat_row_t *stat_col_get_offset(unsigned long int col_start, unsigned long int col_end, unsigned long int row_start, unsigned long int height);
struct stat_cell_t *stat_cell_get();

#endif //VCONI_STATS_H
