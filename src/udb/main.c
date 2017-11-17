//
// Created by nayana on 11/16/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

typedef struct ucdb_row {
    short size;
    unsigned char colb[10];
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

int udb_read_line(int fp, unsigned char **buffer, unsigned char (*colb)[10])
{
    unsigned char cursor;
    *buffer = (unsigned char *) malloc(sizeof(unsigned char) * 100);
    short length = 0;
    short col_idx = 0;
    unsigned char i = 0x0;
    while (0 != read(fp, &cursor, 1)) {
        if (cursor == 0x0A) {
            break;
        }
        if (cursor == 0x3B) {
            (*colb)[col_idx] = i;
        }
        length++;
        i++;
        memcpy((*buffer)++, &cursor, 1);
    }
    return length;
}

int udb_create()
{
    int fp = open("data/ucd/UnicodeData.txt.test", O_RDONLY);
    if (fp == -1) {
        dprintf(2, "unable to find unicode data\n");
        exit(-1);
    }

    root = (ucdb_row *) malloc(sizeof(ucdb_row));
    ucdb_row *node = root;
    node->prev = 0x0;
    end = (ucdb_row *) malloc(sizeof(ucdb_row));
    char run = 0x1;
    while (run == 0x1) {
        unsigned char *buf;
        unsigned char colb[10];
        short size = udb_read_line(fp, &buf, &colb);
        if (size == 0) {
            node->prev->next = 0x0;
            end = node->prev;
            run = 0x0;
        } else {
            node->size = size; //
            memcpy(&node->colb, &colb, 10);
            node->data = buf - size; //we need to reverse the pointer
            node->next = (ucdb_row *) malloc(sizeof(ucdb_row));
            node->next->prev = node;
            node = node->next;
        }
    }
    close(fp);
}

int udb_build_index()
{
    ucdb_row *node = root;
    idx_root = (ucdb_index *) malloc(sizeof(ucdb_index));
    ucdb_index *idx_node = idx_root;
    idx_node->parent = 0x00;
    while (node->next != 0x0) {
        unsigned char *idx = (unsigned char *) malloc(sizeof(unsigned char) * 8);
        *idx = 0x30;
        *(idx+1) = 0x78;
        memcpy((idx+2), node->data, 4);
        int codepoint = (int) strtol(idx, NULL, 16);
        ucdb_index *idx_node = idx_root;
        int indexed = 0;
        while(indexed == 0) {
            if (idx_node->parent == 0x0 && idx_node->codepoint == 0x00) {
                idx_node->codepoint = codepoint;
                indexed = 1;
            } else {
                if (idx_node->codepoint == 0x0) {
                    idx_node->codepoint = codepoint;
                    indexed = 1;
                } else if (idx_node->codepoint < codepoint) {
                    idx_node = idx_node->left;
                } else if (idx_node->codepoint > codepoint) {
                    idx_node = idx_node->right;
                }
            }
        }

        idx_node->row = node;
        idx_node->left = (ucdb_index *) malloc(sizeof(ucdb_index));
        idx_node->right = (ucdb_index *) malloc(sizeof(ucdb_index));
        idx_node->left->parent = idx_node;
        idx_node->right->parent = idx_node;
        node = node->next;
    }
}

int udb_find(int codepoint) {

    ucdb_index *idx_node = idx_root;
    ucdb_row *row;
    int found = 0;
    while (found == 0) {
        #if DEBUG
            printf("%d - %d \n", idx_node->codepoint, codepoint);
        #endif
        if (idx_node->codepoint == codepoint) {
            row = idx_node->row;
            found = 1;
        } else if (idx_node->codepoint < codepoint && idx_node->left != 0x00) {
            idx_node = idx_node->left;
        } else if (idx_node->codepoint > codepoint && idx_node->right != 0x00) {
            idx_node = idx_node->right;
        } else {
            printf("%d not found\n", codepoint);
            return 1;
        }
    }

    printf("%d %s\n", codepoint, row->data);

    return 0;
}

int udb_init()
{
    int fpdat;
    if (-1 == (fpdat = open("udb.dat", O_RDWR))) {
        udb_create();
        udb_build_index();
        udb_find(3);
    }

    /*node = end;
    while (node->prev != 0x0) {
        printf("%s\n", node->data);
        node = node->prev;
    }*/
}

int main(int argv, unsigned char **argc)
{
    udb_init();
    return 0;
}
