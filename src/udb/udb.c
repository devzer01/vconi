//
// Created by nayana on 11/18/17.
//
#include "udb.h"

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
    int fp = open("data/ucd/UnicodeData.txt", O_RDONLY);
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

int udb_parse_column(struct ucdb_row **row, struct ucdb_column **head)
{
    unsigned short int last = 0;
    short i = 0;
    short s = 0;
    struct ucdb_column *col = (*head);
    struct ucdb_row *rhead = (*row);
    while(i < 10) {
        unsigned short int l = (unsigned char) rhead->colb[i];
        unsigned short int len = l - last;
        //0D82;SINHALA SIGN ANUSVARAYA;Mc;0;L;;;;;N;;;;;
#if DEBUG
        printf("parsing column %hd  length %hhd - %c \n", i, l, rhead->colb[i]);
#endif
        (col)->data = malloc(sizeof(unsigned char) * len);
        memcpy((col)->data, (*row)->data+s, (size_t) len);
        s = l + 1;
        last = l + 1;
        (col)->row = *row;
        (col)->number = i++;
        (col)->size = l;
        (col)->next = (struct ucdb_column *) malloc(sizeof(struct ucdb_column));
        (col)->next->prev = (col);
        (col) = (col)->next;
    }

    return 0;
}

struct ucdb_column *udb_find(int codepoint) {

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
            return (void *) 0x0;
        }
    }
    struct ucdb_column *ucdb_col = malloc(sizeof(struct ucdb_column));
    udb_parse_column(&row, &ucdb_col);
    return ucdb_col;
}

int udb_init()
{
    int fpdat;
    if (-1 == (fpdat = open("udb.dat", O_RDWR))) {
        udb_create();
        udb_build_index();
        return 1;
    }

    /*node = end;
    while (node->prev != 0x0) {
        printf("%s\n", node->data);
        node = node->prev;
    }*/
}

