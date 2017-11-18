//
// Created by nayana on 11/16/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udb.h"
#include "vconi.h"


int z_line = 0;

//unsigned char columns[14][15] = {"CODEPOINT", "NAME", "ATTR", "", "", "", "", "", "", "", "", "", "", "", "", ""};


int main(int argv, unsigned char **argc)
{
    udb_init();
    //unsigned char *diag = "बोधिज्ञानयुत्तो";
    unsigned char *diag ="বহৌতিऀ";
    int x_len = strlen(diag);
    printf("length of unicode string is %d \n", x_len);
    int i = 0;
    while(i < x_len) {
        short len = vconi_char_length(*diag);
        unsigned char *buf = malloc(sizeof(unsigned char) * len);
        memcpy(buf, diag, len);
        diag = diag+len;
        i = i + len;
        printf("%s - ", buf);
        int32_t codepoint = utf82codepoint(buf);
        struct ucdb_column *ucdb_col = udb_find(codepoint);
        printf("%d %s - %s\n", codepoint, ucdb_col->data, ucdb_col->next->data);
    }
    return 0;
}

/**
बोधिज्
बोधिज्ञ
बोधिज्ञा **/