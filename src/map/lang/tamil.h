#ifndef VCONI_TAMIL_H
#define VCONI_TAMIL_H

const unsigned char tam_config[516] = { 0x0B, 0x80, 0x7F, 0x1,
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x80, 0x82, 0x00, 0x00, //[2] 0B82 2946 Mn TAMIL SIGN ANUSVARA 0
0x80, 0x83, 0x00, 0x00, //[3] 0B83 2947 Lo TAMIL SIGN VISARGA 0
0x00, 0x00, 0x00, 0x00, //reserved-space
0x80, 0x85, 0x00, 0x00, //[5] 0B85 SVI A     TAMIL LETTER A 2949 Lo 
0x88, 0x86, 0x00, 0x00, //[6] 0B86 SVI AA    TAMIL LETTER AA 2950 Lo 
0x82, 0x87, 0x00, 0x00, //[7] 0B87 SVI I     TAMIL LETTER I 2951 Lo 
0x8A, 0x88, 0x00, 0x00, //[8] 0B88 SVI II    TAMIL LETTER II 2952 Lo 
0x83, 0x89, 0x00, 0x00, //[9] 0B89 SVI U     TAMIL LETTER U 2953 Lo 
0x8B, 0x8A, 0x00, 0x00, //[10] 0B8A SVI UU   TAMIL LETTER UU 2954 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x86, 0x8E, 0x00, 0x00, //[14] 0B8E SVI E    TAMIL LETTER E 2958 Lo 
0xA6, 0x8F, 0x00, 0x00, //[15] 0B8F SVI EE   TAMIL LETTER EE 2959 Lo 
0x8E, 0x90, 0x00, 0x00, //[16] 0B90 SVI AI   TAMIL LETTER AI 2960 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x87, 0x92, 0x00, 0x00, //[18] 0B92 SVI O    TAMIL LETTER O 2962 Lo 
0xA7, 0x93, 0x00, 0x00, //[19] 0B93 SVI OO   TAMIL LETTER OO 2963 Lo 
0x8F, 0x94, 0x00, 0x00, //[20] 0B94 SVI AU   TAMIL LETTER AU 2964 Lo 
0x90, 0x95, 0x00, 0x00, //[21] 0B95 SVD A    TAMIL LETTER KA 2965 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0xBD, 0x99, 0x00, 0x00, //[25] 0B99 SC NGA   TAMIL LETTER NGA 2969 Lo 
0xB2, 0x9A, 0x00, 0x00, //[26] 0B9A SC CA    TAMIL LETTER CA 2970 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0xB3, 0x9C, 0x00, 0x00, //[28] 0B9C SC JA    TAMIL LETTER JA 2972 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0xCF, 0x9E, 0x00, 0x00, //[30] 0B9E SC YHA   TAMIL LETTER NYA 2974 Lo 
0xB4, 0x9F, 0x00, 0x00, //[31] 0B9F SC TTA   TAMIL LETTER TTA 2975 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0xC6, 0xA3, 0x00, 0x00, //[35] 0BA3 SC NHA   TAMIL LETTER NNA 2979 Lo 
0xB7, 0xA4, 0x00, 0x00, //[36] 0BA4 SC TA    TAMIL LETTER TA 2980 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0xB6, 0xA8, 0x00, 0x00, //[40] 0BA8 SC NA    TAMIL LETTER NA 2984 Lo 
0xD6, 0xA9, 0x00, 0x00, //[41] 0BA9 SCN NNNA  TAMIL LETTER NNNA 2985 Lo 
0xB9, 0xAA, 0x00, 0x00, //[42] 0BAA SC PA    TAMIL LETTER PA 2986 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0xE2, 0xAE, 0x00, 0x00, //[46] 0BAE SC MA    TAMIL LETTER MA 2990 Lo 
0xBF, 0xAF, 0x00, 0x00, //[47] 0BAF SC YA    TAMIL LETTER YA 2991 Lo 
0xBE, 0xB0, 0x00, 0x00, //[48] 0BB0 SC RA    TAMIL LETTER RA 2992 Lo 
0x84, 0xB1, 0x00, 0x00, //[49] 0BB1 SVI VOC R  TAMIL LETTER RRA 2993 Lo 
0xBB, 0xB2, 0x00, 0x00, //[50] 0BB2 SC LA    TAMIL LETTER LA 2994 Lo 
0xCB, 0xB3, 0x00, 0x00, //[51] 0BB3 SC LHA   TAMIL LETTER LLA 2995 Lo 
0x85, 0xB4, 0x00, 0x00, //[52] 0BB4 SVI VOC L  TAMIL LETTER LLLA 2996 Lo 
0xE0, 0xB5, 0x00, 0x00, //[53] 0BB5 SC VA    TAMIL LETTER VA 2997 Lo 
0xCC, 0xB6, 0x00, 0x00, //[54] 0BB6 SC SHA   TAMIL LETTER SHA 2998 Lo 
0xDC, 0xB7, 0x00, 0x00, //[55] 0BB7 SC SSHA  TAMIL LETTER SSA 2999 Lo 
0xBC, 0xB8, 0x00, 0x00, //[56] 0BB8 SC SA    TAMIL LETTER SA 3000 Lo 
0xE1, 0xB9, 0x00, 0x00, //[57] 0BB9 SC HA    TAMIL LETTER HA 3001 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x98, 0xBE, 0x00, 0x00, //[62] 0BBE SVD AA   TAMIL VOWEL SIGN AA 3006 Mc 
0x92, 0xBF, 0x00, 0x00, //[63] 0BBF SVD I    TAMIL VOWEL SIGN I 3007 Mc 
0x9A, 0xC0, 0x00, 0x00, //[64] 0BC0 SVD II   TAMIL VOWEL SIGN II 3008 Mn 
0x93, 0xC1, 0x00, 0x00, //[65] 0BC1 SVD U    TAMIL VOWEL SIGN U 3009 Mc 
0x9B, 0xC2, 0x00, 0x00, //[66] 0BC2 SVD UU   TAMIL VOWEL SIGN UU 3010 Mc 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x96, 0xC6, 0x00, 0x00, //[70] 0BC6 SVD E    TAMIL VOWEL SIGN E 3014 Mc 
0xAE, 0xC7, 0x00, 0x00, //[71] 0BC7 SVD EE   TAMIL VOWEL SIGN EE 3015 Mc 
0x9E, 0xC8, 0x00, 0x00, //[72] 0BC8 SVD AI   TAMIL VOWEL SIGN AI 3016 Mc 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x97, 0xCA, 0x00, 0x00, //[74] 0BCA SVD O    TAMIL VOWEL SIGN O 3018 Mc 
0xAF, 0xCB, 0x00, 0x00, //[75] 0BCB SVD OO   TAMIL VOWEL SIGN OO 3019 Mc 
0x9F, 0xCC, 0x00, 0x00, //[76] 0BCC SVD AU   TAMIL VOWEL SIGN AU 3020 Mc 
0x80, 0xCD, 0x00, 0x00, //[77] 0BCD 3021 Mn TAMIL SIGN VIRAMA 0
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x80, 0xD0, 0x00, 0x00, //[80] 0BD0 3024 Lo TAMIL OM 0
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x80, 0xD7, 0x00, 0x00, //[87] 0BD7 3031 Mc TAMIL AU LENGTH MARK 0
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x80, 0xE6, 0x00, 0x00, //[102] 0BE6 3046 Nd TAMIL DIGIT ZERO 0
0x80, 0xE7, 0x00, 0x00, //[103] 0BE7 3047 Nd TAMIL DIGIT ONE 0
0x80, 0xE8, 0x00, 0x00, //[104] 0BE8 3048 Nd TAMIL DIGIT TWO 0
0x80, 0xE9, 0x00, 0x00, //[105] 0BE9 3049 Nd TAMIL DIGIT THREE 0
0x80, 0xEA, 0x00, 0x00, //[106] 0BEA 3050 Nd TAMIL DIGIT FOUR 0
0x80, 0xEB, 0x00, 0x00, //[107] 0BEB 3051 Nd TAMIL DIGIT FIVE 0
0x80, 0xEC, 0x00, 0x00, //[108] 0BEC 3052 Nd TAMIL DIGIT SIX 0
0x80, 0xED, 0x00, 0x00, //[109] 0BED 3053 Nd TAMIL DIGIT SEVEN 0
0x80, 0xEE, 0x00, 0x00, //[110] 0BEE 3054 Nd TAMIL DIGIT EIGHT 0
0x80, 0xEF, 0x00, 0x00, //[111] 0BEF 3055 Nd TAMIL DIGIT NINE 0
0x80, 0xF0, 0x00, 0x00, //[112] 0BF0 3056 No TAMIL NUMBER TEN 0
0x80, 0xF1, 0x00, 0x00, //[113] 0BF1 3057 No TAMIL NUMBER ONE HUNDRED 0
0x80, 0xF2, 0x00, 0x00, //[114] 0BF2 3058 No TAMIL NUMBER ONE THOUSAND 0
0x80, 0xF3, 0x00, 0x00, //[115] 0BF3 3059 So TAMIL DAY SIGN 0
0x80, 0xF4, 0x00, 0x00, //[116] 0BF4 3060 So TAMIL MONTH SIGN 0
0x80, 0xF5, 0x00, 0x00, //[117] 0BF5 3061 So TAMIL YEAR SIGN 0
0x80, 0xF6, 0x00, 0x00, //[118] 0BF6 3062 So TAMIL DEBIT SIGN 0
0x80, 0xF7, 0x00, 0x00, //[119] 0BF7 3063 So TAMIL CREDIT SIGN 0
0x80, 0xF8, 0x00, 0x00, //[120] 0BF8 3064 So TAMIL AS ABOVE SIGN 0
0x80, 0xF9, 0x00, 0x00, //[121] 0BF9 3065 Sc TAMIL RUPEE SIGN 0
0x80, 0xFA, 0x00, 0x00, //[122] 0BFA 3066 So TAMIL NUMBER SIGN 0
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00 //reserved-space
};
#endif