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
int z_line = 0;

short udb_read_line(int fp, unsigned char **buffer, unsigned char (*colb)[14])
{
    unsigned char cursor;
    (*buffer) = malloc(sizeof(*buffer) * 70);
    if (*buffer == 0x00) {
        printf("unable to allocate memory\n");
        exit(-1);
    }
    short length = 0;
    short col_idx = 0;
    unsigned char i = 0x0;
    while (0 != read(fp, &cursor, 1)) {
        if (cursor == 0x0A) {
            break;
        }
        if (cursor == 0x3B) {
            (*colb)[col_idx++] = (unsigned char) i;
        }
        length++;
        i = (unsigned char) ((unsigned char) (i) + 0x01);
        if (memcpy((*buffer)++, &cursor, 1) == 0x00) {
            printf("error\n");
            exit(-1);
        }
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

    root = malloc(sizeof(*root));
    ucdb_row *node = root;
    node->prev = 0x0;
    end = malloc(sizeof(*end));
    char run = 0x1;
    while (run == 0x1) {
        unsigned char *buf;
        unsigned char colb[14];
        short size = udb_read_line(fp, &buf, &colb);
        if (size == 0) {
            node->prev->next = 0x0;
            end = node->prev;
            run = 0x0;
        } else {
            node->size = size; //
            memcpy(&node->colb, colb, 14);
            node->data = buf - size; //we need to reverse the pointer
            node->next = malloc(sizeof(*node));
            //node->next->prev = malloc(sizeof(node->next->prev));
            node->next->prev = node;
            node = node->next;
        }
    }
    close(fp);
}

int udb_build_index()
{
    ucdb_row *node = root;
    idx_root = malloc(sizeof(*idx_root));
    idx_root->codepoint = 0;
    struct ucdb_index *idx_node = idx_root;
    int codepoint = 0;
    while (node->next != 0x0) {
        short int length = (short int) node->colb[0];
        unsigned char *idx = (unsigned char *) malloc(sizeof(unsigned char) * (length + 3));
        *idx = 0x30;
        *(idx+1) = 0x78;
        memcpy((idx+2), node->data, length);
        codepoint = (int) strtol((const char *)idx, NULL, 16);
        int indexed = 0;
        ucdb_index *next;
        while(indexed == 0) {
            if (idx_node->codepoint == 0) {
                idx_node->codepoint = codepoint;
                indexed = 1;
            } else if (idx_node->codepoint < codepoint) {
               idx_node = idx_node->left;
            } else if (idx_node->codepoint > codepoint) {
                idx_node = idx_node->right;
            }
        }

        if (idx_node->left == 0x0) {
            next = malloc(sizeof(struct ucdb_index));
            next->codepoint = 0;
            idx_node->left = next;
            idx_node->left->parent = idx_node;
        }

        if (idx_node->right == 0x0) {
            next = malloc(sizeof(struct ucdb_index));
            next->codepoint = 0;
            idx_node->right = next;
            idx_node->right->parent = idx_node;
        }

        idx_node->row = node;
        node = node->next;
    }
}

/**
 * typedef struct ucdb_row {
    short size;
    unsigned char colb[10];
    unsigned char *data;
    struct ucdb_row *prev;
    struct ucdb_row *next;
} ucdb_row;

typedef struct ucdb_column {
    short number;
    short size;
    struct ucdb_row *row;
    unsigned char *data;
    struct ucdb_column *prev;
    struct ucdb_column *next;
} ucdb_column;
 * @param ucdb_row1 
 * @param head 
 * @return 
 */

int udb_parse_column(struct ucdb_row **row, struct ucdb_column **head) 
{
    short i = 0;
    short s = 0;
    struct ucdb_column *col = (*head);
    struct ucdb_row *rhead = (*row);
    while(i < 10) {
        unsigned short l = (unsigned short) rhead->colb[i];
        printf("parsing column %hd  length %hd - %hhd \n", i, l, rhead->colb[i]);
        (col)->data = malloc(sizeof(unsigned char) * l);
        memcpy((col)->data, (*row+s)->data, (size_t) l);
        s += l;
        (col)->row = *row;
        (col)->number = i++;
        (col)->size = l;
        (col)->next = (struct ucdb_column *) malloc(sizeof(*(col)->next));
        (col)->next->prev = (col);
        (col) = (col)->next;
    }
        
    return 0;
}

int udb_find(int codepoint) {

    ucdb_index *idx_node = idx_root->left;
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
    struct ucdb_column *ucdb_col = malloc(sizeof(struct ucdb_column));
    udb_parse_column(&row, &ucdb_col);
    printf("%s - %s\n", ucdb_col->data, ucdb_col->next->data);

    return 0;
}

int udb_init()
{
    int fpdat;
    if (-1 == (fpdat = open("udb.dat", O_RDWR))) {
        udb_create();
        udb_build_index();
        udb_find(3458);
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
