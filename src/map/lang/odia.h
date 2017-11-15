#ifndef VCONI_odia_H
#define VCONI_odia_H

const unsigned char odi_config[516] = { 0x0B, 0x00, 0x7F, 0x1,
0x00, 0x00, 0x00, 0x00, //reserved-space
0x50, 0x01, 0x00, 0x00, //0B01 2817 Mn ORIYA SIGN CANDRABINDU 0
0x00, 0x02, 0x00, 0x00, //0B02 SS ANUSVARA   ORIYA SIGN ANUSVARA 2818 Mc 
0x00, 0x03, 0x00, 0x00, //0B03 SS VISARGA    ORIYA SIGN VISARGA 2819 Mc 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x50, 0x05, 0x00, 0x00, //0B05 SVI A         ORIYA LETTER A 2821 Lo 
0x58, 0x06, 0x00, 0x00, //0B06 SVI AA        ORIYA LETTER AA 2822 Lo 
0x52, 0x07, 0x00, 0x00, //0B07 SVI I         ORIYA LETTER I 2823 Lo 
0x08, 0x08, 0x00, 0x00, //0B08 SVI II        ORIYA LETTER II 2824 Lo 
0x53, 0x09, 0x00, 0x00, //0B09 SVI U         ORIYA LETTER U 2825 Lo 
0x08, 0x00, 0x00, 0x00, //0B0A SVI UU        ORIYA LETTER UU 2826 Lo 
0x54, 0x00, 0x00, 0x00, //0B0B SVI VOC R     ORIYA LETTER VOCALIC R 2827 Lo 
0x55, 0x00, 0x00, 0x00, //0B0C SVI VOC L     ORIYA LETTER VOCALIC L 2828 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //0B0F SVI EE        ORIYA LETTER E 2831 Lo 
0x08, 0x0A, 0x00, 0x00, //0B10 SVI AI        ORIYA LETTER AI 2832 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x0D, 0x00, 0x00, //0B13 SVI OO        ORIYA LETTER O 2835 Lo 
0x08, 0x0E, 0x00, 0x00, //0B14 SVI AU        ORIYA LETTER AU 2836 Lo 
0x5A, 0x0F, 0x00, 0x00, //0B15 SVD A         ORIYA LETTER KA 2837 Lo 
0x00, 0x10, 0x00, 0x00, //0B16 SC KHA        ORIYA LETTER KHA 2838 Lo 
0x00, 0x11, 0x00, 0x00, //0B17 SC GA         ORIYA LETTER GA 2839 Lo 
0x00, 0x12, 0x00, 0x00, //0B18 SC GHA        ORIYA LETTER GHA 2840 Lo 
0x00, 0x13, 0x00, 0x00, //0B19 SC NGA        ORIYA LETTER NGA 2841 Lo 
0x00, 0x01, 0x00, 0x00, //0B1A SC CA         ORIYA LETTER CA 2842 Lo 
0x00, 0x01, 0x00, 0x00, //0B1B SC CHA        ORIYA LETTER CHA 2843 Lo 
0x00, 0x01, 0x00, 0x00, //0B1C SC JA         ORIYA LETTER JA 2844 Lo 
0x00, 0x01, 0x00, 0x00, //0B1D SC JHA        ORIYA LETTER JHA 2845 Lo 
0x00, 0x01, 0x00, 0x00, //0B1E SC YHA        ORIYA LETTER NYA 2846 Lo 
0x00, 0x01, 0x00, 0x00, //0B1F SC TTA        ORIYA LETTER TTA 2847 Lo 
0x00, 0x14, 0x00, 0x00, //0B20 SC TTHA       ORIYA LETTER TTHA 2848 Lo 
0x00, 0x15, 0x00, 0x00, //0B21 SC DDA        ORIYA LETTER DDA 2849 Lo 
0x00, 0x16, 0x00, 0x00, //0B22 SC DDHA       ORIYA LETTER DDHA 2850 Lo 
0x00, 0x17, 0x00, 0x00, //0B23 SC NHA        ORIYA LETTER NNA 2851 Lo 
0x00, 0x18, 0x00, 0x00, //0B24 SC TA         ORIYA LETTER TA 2852 Lo 
0x00, 0x19, 0x00, 0x00, //0B25 SC THA        ORIYA LETTER THA 2853 Lo 
0x00, 0x1A, 0x00, 0x00, //0B26 SC DA         ORIYA LETTER DA 2854 Lo 
0x00, 0x1B, 0x00, 0x00, //0B27 SC DHA        ORIYA LETTER DHA 2855 Lo 
0x00, 0x1C, 0x00, 0x00, //0B28 SC NA         ORIYA LETTER NA 2856 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x02, 0x00, 0x00, //0B2A SC PA         ORIYA LETTER PA 2858 Lo 
0x00, 0x02, 0x00, 0x00, //0B2B SC PHA        ORIYA LETTER PHA 2859 Lo 
0x00, 0x02, 0x00, 0x00, //0B2C SC BA         ORIYA LETTER BA 2860 Lo 
0x00, 0x02, 0x00, 0x00, //0B2D SC BHA        ORIYA LETTER BHA 2861 Lo 
0x00, 0x02, 0x00, 0x00, //0B2E SC MA         ORIYA LETTER MA 2862 Lo 
0x50, 0x02, 0x00, 0x00, //0B2F 2863 Lo ORIYA LETTER YA 0
0x00, 0x1E, 0x00, 0x00, //0B30 SC RA         ORIYA LETTER RA 2864 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x20, 0x00, 0x00, //0B32 SC LA         ORIYA LETTER LA 2866 Lo 
0x00, 0x21, 0x00, 0x00, //0B33 SC LHA        ORIYA LETTER LLA 2867 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x50, 0x23, 0x00, 0x00, //0B35 2869 Lo ORIYA LETTER VA 0
0x00, 0x24, 0x00, 0x00, //0B36 SC SHA        ORIYA LETTER SHA 2870 Lo 
0x00, 0x25, 0x00, 0x00, //0B37 SC SSHA       ORIYA LETTER SSA 2871 Lo 
0x00, 0x26, 0x00, 0x00, //0B38 SC SA         ORIYA LETTER SA 2872 Lo 
0x00, 0x27, 0x00, 0x00, //0B39 SC HA         ORIYA LETTER HA 2873 Lo 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x50, 0x03, 0x00, 0x00, //0B3C 2876 Mn ORIYA SIGN NUKTA 0
0x5B, 0x03, 0x00, 0x00, //0B3D SVD AE        ORIYA SIGN AVAGRAHA 2877 Lo 
0x62, 0x03, 0x00, 0x00, //0B3E SVD AA        ORIYA VOWEL SIGN AA 2878 Mc 
0x5C, 0x03, 0x00, 0x00, //0B3F SVD I         ORIYA VOWEL SIGN I 2879 Mn 
0x09, 0x28, 0x00, 0x00, //0B40 SVD II        ORIYA VOWEL SIGN II 2880 Mc 
0x5D, 0x29, 0x00, 0x00, //0B41 SVD U         ORIYA VOWEL SIGN U 2881 Mn 
0x09, 0x2A, 0x00, 0x00, //0B42 SVD UU        ORIYA VOWEL SIGN UU 2882 Mn 
0x5E, 0x2B, 0x00, 0x00, //0B43 SVD VOC R     ORIYA VOWEL SIGN VOCALIC R 2883 Mn 
0x50, 0x2C, 0x00, 0x00, //0B44 2884 Mn ORIYA VOWEL SIGN VOCALIC RR 0
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x2F, 0x00, 0x00, //0B47 SVD EE        ORIYA VOWEL SIGN E 2887 Mc 
0x09, 0x30, 0x00, 0x00, //0B48 SVD AI        ORIYA VOWEL SIGN AI 2888 Mc 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x04, 0x00, 0x00, //0B4B SVD OO        ORIYA VOWEL SIGN O 2891 Mc 
0x09, 0x04, 0x00, 0x00, //0B4C SVD AU        ORIYA VOWEL SIGN AU 2892 Mc 
0x08, 0x04, 0x00, 0x00, //0B4D SVI VOC RR    ORIYA SIGN VIRAMA 2893 Mn 
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x50, 0x38, 0x00, 0x00, //0B56 2902 Mn ORIYA AI LENGTH MARK 0
0x50, 0x39, 0x00, 0x00, //0B57 2903 Mc ORIYA AU LENGTH MARK 0
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00 //reserved-space
};
#endif