//
// Created by nayana on 11/20/17.
//

#include <stdio.h>
#include "vconi.h"

int main()
{
    /*unsigned char mask[3] = {0b11101111, 0b10111111, 0b10111111};
    //unsigned char mask[3] = {0b11100000, 0b10000000, 0b10000000};
    int codepoint = 0x1001;
    unsigned char buf[3];

    buf[2] = 0b10000000 + (codepoint & 0b00111111);
    codepoint = codepoint >> 6;
    buf[1] = 0b10000000 + (codepoint & 0b00111111);
    codepoint = codepoint >> 6;
    buf[0] = 0b11100000 + (codepoint & 0x00001111);*/
    unsigned char *buf;
    buf = getuchar(0x1001, buf);

    printf("%s", buf);
    return 0;
}
