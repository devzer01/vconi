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
    unsigned char *data;
    struct ucdb_column *prev;
    struct ucdb_column *next;
} ucdb_column;

ucdb_row *root;
ucdb_row *end;

int udb_read_line(int fp, unsigned char **buffer)
{
    unsigned char cursor;
    *buffer = (unsigned char *) malloc(sizeof(unsigned char) * 100);
    short length = 0;
    while (0 != read(fp, &cursor, 1)) {
        if (cursor == 0x0A) {
            break;
        }
        length++;
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
        short size = udb_read_line(fp, &buf);
        if (size == 0) {
            node->prev->next = 0x0;
            end = node->prev;
            run = 0x0;
        } else {
            node->size = size; //
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

}

int udb_init()
{
    int fpdat;
    if (-1 == (fpdat = open("udb.dat", O_RDWR))) {
        udb_create();
    }
    ucdb_row *node = root;
    while (node->next != 0x0) {
        printf("%s\n", node->data);
        node = node->next;
    }
    node = end;
    while (node->prev != 0x0) {
        printf("%s\n", node->data);
        node = node->prev;
    }
}

int main(int argv, unsigned char **argc)
{
    udb_init();
    return 0;
}
