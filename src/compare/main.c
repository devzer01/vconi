//
//  main.c
//  compare
//
//  Created by Hettiarachchi, Nayana (Agoda) on 11/7/17.
//
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
    
#define MAX_WORD_SIZE 73
    
int resetptr(unsigned char * ptr) {
        const char nullb[73] = "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                               "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                               "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                               "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000";
        
        memcpy(ptr, nullb, MAX_WORD_SIZE);
        return 0;
}

    //int main(int argc, const char * argv[]) {
    int main( int argc, const char **argv)
    {
        const char *file1 = argv[1];
        const char *file2 = argv[2];
        
        unsigned char words[1202][MAX_WORD_SIZE];
        unsigned char words2[1202][MAX_WORD_SIZE];
        unsigned int index;
        int fp1 = open(file1, O_RDONLY);
        unsigned char cursor = 0x00;
        unsigned char *current = (unsigned char *) malloc(sizeof(unsigned char) * MAX_WORD_SIZE);
        resetptr(current);
        int row = 0;
        int s = 0;
        while(0 < read(fp1, &cursor, 1)) {
            switch (cursor) {
                case 0xa:
                    memcpy(&words[row], current, s);
                    resetptr(current);
                    row++;
                    s = 0;
                    break;
                case 0x00:
                    break;
                default:
                    current[s++] = cursor;
                    if (s >= MAX_WORD_SIZE) {
                        dprintf(2, "reaching buffer limit\n");
                    }
                    break;
            }
        }
        
        free(current);
        close(fp1);
        int word_length = row;
        index = 0;
        
        int fp2 = open(file2, O_RDONLY);
        s = 0;
        cursor = 0x00;
        row = 0;
        resetptr(current);
        while(0 < read(fp2, &cursor, 1)) {
            switch (cursor) {
                case 0x0a:
                    memcpy(&words2[row], current, s);
                    resetptr(current);
                    row++;
                    s = 0;
                    break;
                case 0x00:
                    break;
                default:
                    current[s++] = cursor;
                    if (s >= MAX_WORD_SIZE) {
                        dprintf(2, "reaching buffer limit\n");
                    }
                    break;
            }
        }
        int word2_length = row;
        close(fp2);
        int match = 0;
        unsigned char matching[100][2][MAX_WORD_SIZE];
        for (int x = 0; x < word_length; x++) {
            if (words[x][0] == 0x00) continue;
            for (int y = 0; y < word2_length; y++) {
                if (words[y][0] == 0x00) continue;
                if (memcmp(words[x], words2[y], MAX_WORD_SIZE) == 0) {
                    memcpy(matching[match][0], words[x], MAX_WORD_SIZE);
                    memcpy(matching[match][1], words2[y], MAX_WORD_SIZE);
                    match++;
                    break;
                }
            }
        }
        //int pmatch = (match * 100) / word_length;
        printf("matches %d out of %d percent  \n",  match, word_length);
        fp1 = open("matches.txt", O_WRONLY | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
        for (int i = 0; i < 100; i++) {
            if (*matching[i][0] == 0x00) break;
            dprintf(fp1, "%s\n", matching[i][0]);
            dprintf(1, "1:%s:%s:0\n", matching[i][0], matching[i][1]);
        }
        close(fp1);
        close(fp2);

        return 0;
}