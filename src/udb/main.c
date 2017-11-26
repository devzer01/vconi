//
// Created by nayana on 11/16/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include "udb.h"
#include "vconi.h"
#include "../vconi.h"


int z_line = 0;

//unsigned char columns[14][15] = {"CODEPOINT", "NAME", "ATTR", "", "", "", "", "", "", "", "", "", "", "", "", ""};


int main(int argv, unsigned char **argc)
{
    off_t len = lseek(0, 0, SEEK_END);
    int input = 0;
    if (len == -1) {
#if DEBUG
        unsigned char *error_message = strerror(errno);
        printf("error %d %d - %s \n", ESPIPE, errno, error_message);
#endif
        off_t len_prev = 0;
        unsigned char ch;
        input = open("/tmp", __O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR );
        len = 0;
        while (0 < read(0, &ch, 1)) {
            if (ch == 0x0A) continue;
            write(input, &ch, 1);
            len++;
        }
    }


    unsigned char *diag = malloc(sizeof(unsigned char) * (size_t) len);
    lseek(input, 0, SEEK_SET);
    read(input, diag, (size_t) len);

#if DEBUG
    printf("len %ld\n", len);
    printf("got string  %s \n", diag);
#endif
    if (input != 0) close(input);

    udb_init();
    int x_len = strlen(diag);
#if DEBUG
    dprintf(2, "%ld", time(0x0));
#endif
    printf("start analysis of %s of length %d \n", diag, x_len);
    int i = 0;
    while(i < x_len) {
        short len = vconi_char_length(*diag);
        unsigned char *buf = malloc(sizeof(unsigned char) * len);
        memcpy(buf, diag, len);
        diag = diag+len;
        i = i + len;
#if DEBUG
        dprintf(2, "%ld", time(0x0));
#endif
        printf("%s - ", buf);
        int32_t codepoint = vconi_utf82codepoint(buf, len);
        struct ucdb_column *ucdb_col = udb_find(codepoint);
        if (ucdb_col != 0x0) {
            printf("%d %s - %s\n", codepoint, ucdb_col->data, ucdb_col->next->data);
        }
    }
    return 0;
}

/**
बोधिज्
बोधिज्ञ
बोधिज्ञा **/