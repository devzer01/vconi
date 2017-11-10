static const unsigned short b8e_sinh_wc[128] = {
        0xb685, 0xb687, 0xb689, 0xb68b, 0xb68d, 0xb68f, 0xb691, 0xb694, 0xb686, 0xb688, 0xb68a, 0xb68c, 0xb68e, 0xb690,
        0x0000, 0xb696, 0x0000, 0xb78f, 0xb792, 0xb794, 0xb798, 0x0000, 0xb799, 0xb79c, 0x0000, 0xb790, 0xb793, 0xb796,
        0xb7b2, 0xb7b3, 0xb79b, 0xb79e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xb695, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xb79d, 0xb69a, 0xb69c, 0xb6a0, 0xb6a2, 0x0000, 0xb6a9, 0xb6ab, 0xb6a7,
        0xb6af, 0xb6b4, 0xb6b6, 0xb6bd, 0xb781, 0xb69e, 0xb6bb, 0xb6ba, 0xb69b, 0xb69d, 0xb6a1, 0xb6a3, 0xb6a8, 0x0000,
        0x0000, 0xb6ad, 0xb6b0, 0xb6b5, 0xb6b7, 0x0000, 0xb782, 0x0000, 0x0000, 0x0000, 0x0000, 0xb69f, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xb780, 0xb784,
        0xb6b8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xb78a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000
};

static const unsigned char b8e_sinh_b[128] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x88, 0x81,
        0x89, 0x82, 0x8a, 0x83, 0x8b, 0x84, 0x8c, 0x85,
        0x8d, 0x86, 0x00, 0x81, 0x87, 0xa7, 0x8f, 0x00,
        0x00, 0x00, 0xb0, 0xc0, 0xb1, 0xc1, 0xbd, 0xd1,
        0xb2, 0xc2, 0xb3, 0xc3, 0x00, 0x00, 0x00, 0xb7,
        0xc4, 0xb5, 0x00, 0xb6, 0x00, 0xc7, 0x00, 0xb8,
        0xc8, 0xb6, 0x00, 0x00, 0xb9, 0xc9, 0xba, 0xca,
        0xe2, 0x00, 0xbf, 0xbe, 0x00, 0xbb, 0x00, 0x00,
        0xe0, 0xcc, 0xdc, 0xbc, 0xe1, 0x00, 0x00, 0x00,
        0x00, 0x00, 0xf5, 0x00, 0x00, 0x00, 0x00, 0x91,
        0x99, 0x99, 0x92, 0x9a, 0x93, 0x00, 0x9b, 0x00,
        0x94, 0x96, 0x00, 0x9e, 0x97, 0xaf, 0x9f, 0x9f,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x9c, 0x9d, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


static int
b8esinh_mbtowc(conv_t conv, ucs4_t *pwc, const unsigned char *s, size_t n) {
    unsigned char c = *s;
    if (c < 0x80) {
        *pwc = (ucs4_t) c;
        return 1;
    } else {
        unsigned short wc = b8e_sinh_wc[c - 0x80];
        *pwc = (ucs4_t) wc;
        return 1;
    }
    return RET_ILSEQ;
}

static int
b8esinh_wctomb(conv_t conv, unsigned char *r, ucs4_t wc, size_t n) {
    if (wc < 0x0080) {
        *r = wc;
        return 1;
    } else if (wc >= 0x0D80 && wc <= 0x0DFF) {
        *r = b8e_sinh_b[wc - 0x0D80];
        return 1;
    } else if (wc == 0x200d) {
        return 0;
    }
    return RET_ILUNI;
}