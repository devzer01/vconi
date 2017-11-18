//
// Created by nayana on 11/18/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#ifndef VCONI_UDB_H_H
#define VCONI_UDB_H_H

typedef struct ucdb_row {
    short size;
    unsigned char colb[14];
    unsigned char *data;
    struct ucdb_row *prev;
    struct ucdb_row *next;
} ucdb_row;

typedef struct ucdb_column_def {
    short column;
    unsigned char *name;
    struct ucdb_column_def *prev;
    struct ucdb_column_def *next;
} ucdb_column_def;

typedef struct ucdb_column {
    short number;
    short size;
    struct ucdb_row *row;
    unsigned char *data;
    struct ucdb_column *prev;
    struct ucdb_column *next;
    struct ucdb_column_def *meta;
} ucdb_column;

typedef struct ucdb_index {
    int codepoint;
    struct ucdb_index *parent;
    struct ucdb_index *left;
    struct ucdb_index *right;
    struct ucdb_row *row;
} ucdb_index;

ucdb_row *root;
ucdb_row *end;
ucdb_index *idx_root;
ucdb_column_def *meta_root;

int udb_create();
int udb_build_index();
int udb_parse_column(struct ucdb_row **row, struct ucdb_column **head);
struct ucdb_column *udb_find(int codepoint);
int udb_init();

#endif //VCONI_UDB_H_H
