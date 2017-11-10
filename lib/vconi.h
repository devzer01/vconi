//
// Created by nayana on 11/10/17.
//

#ifndef VCONI_VCONI_H
#define VCONI_VCONI_H

#endif //VCONI_VCONI_H

int32_t getCodePoint(unsigned char *buffer) {
    int32_t codepoint = (0b00111111 & buffer[2]);
    codepoint = codepoint + ((0b00111111 & buffer[1]) << 6);
    codepoint = codepoint + ((0b00001111 & buffer[0]) << 12);
    return codepoint;
}



