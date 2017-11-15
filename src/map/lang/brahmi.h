#ifndef VCONI_brahmi_H
#define VCONI_brahmi_H

const unsigned char bra_config[516] = { 0x10, 0x00, 0x7F, 0x1,
0x50, 0x00, 0x00, 0x00, //11000 69632 Mc BRAHMI SIGN CANDRABINDU 0
0x50, 0x01, 0x00, 0x00, //11001 69633 Mn BRAHMI SIGN ANUSVARA 0
0x50, 0x02, 0x00, 0x00, //11002 69634 Mc BRAHMI SIGN VISARGA 0
0x50, 0x03, 0x00, 0x00, //11003 69635 Lo BRAHMI SIGN JIHVAMULIYA 0
0x50, 0x04, 0x00, 0x00, //11004 69636 Lo BRAHMI SIGN UPADHMANIYA 0
0x50, 0x05, 0x00, 0x00, //11005 SVI A        BRAHMI LETTER A 69637 Lo 
0x58, 0x06, 0x00, 0x00, //11006 SVI AA       BRAHMI LETTER AA 69638 Lo 
0x52, 0x07, 0x00, 0x00, //11007 SVI I        BRAHMI LETTER I 69639 Lo 
0x08, 0x08, 0x00, 0x00, //11008 SVI II       BRAHMI LETTER II 69640 Lo 
0x53, 0x09, 0x00, 0x00, //11009 SVI U        BRAHMI LETTER U 69641 Lo 
0x08, 0x00, 0x00, 0x00, //1100A SVI UU       BRAHMI LETTER UU 69642 Lo 
0x54, 0x00, 0x00, 0x00, //1100B SVI VOC R    BRAHMI LETTER VOCALIC R 69643 Lo 
0x08, 0x00, 0x00, 0x00, //1100C SVI VOC RR   BRAHMI LETTER VOCALIC RR 69644 Lo 
0x55, 0x00, 0x00, 0x00, //1100D SVI VOC L    BRAHMI LETTER VOCALIC L 69645 Lo 
0x08, 0x00, 0x00, 0x00, //1100E SVI VOC LL   BRAHMI LETTER VOCALIC LL 69646 Lo 
0x00, 0x00, 0x00, 0x00, //1100F SVI EE       BRAHMI LETTER E 69647 Lo 
0x08, 0x0A, 0x00, 0x00, //11010 SVI AI       BRAHMI LETTER AI 69648 Lo 
0x00, 0x0B, 0x00, 0x00, //11011 SVI OO       BRAHMI LETTER O 69649 Lo 
0x08, 0x0C, 0x00, 0x00, //11012 SVI AU       BRAHMI LETTER AU 69650 Lo 
0x00, 0x0D, 0x00, 0x00, //11013 SC KA        BRAHMI LETTER KA 69651 Lo 
0x00, 0x0E, 0x00, 0x00, //11014 SC KHA       BRAHMI LETTER KHA 69652 Lo 
0x00, 0x0F, 0x00, 0x00, //11015 SC GA        BRAHMI LETTER GA 69653 Lo 
0x00, 0x10, 0x00, 0x00, //11016 SC GHA       BRAHMI LETTER GHA 69654 Lo 
0x00, 0x11, 0x00, 0x00, //11017 SC NGA       BRAHMI LETTER NGA 69655 Lo 
0x00, 0x12, 0x00, 0x00, //11018 SC CA        BRAHMI LETTER CA 69656 Lo 
0x00, 0x13, 0x00, 0x00, //11019 SC CHA       BRAHMI LETTER CHA 69657 Lo 
0x00, 0x01, 0x00, 0x00, //1101A SC JA        BRAHMI LETTER JA 69658 Lo 
0x00, 0x01, 0x00, 0x00, //1101B SC JHA       BRAHMI LETTER JHA 69659 Lo 
0x00, 0x01, 0x00, 0x00, //1101C SC YHA       BRAHMI LETTER NYA 69660 Lo 
0x00, 0x01, 0x00, 0x00, //1101D SC TTA       BRAHMI LETTER TTA 69661 Lo 
0x00, 0x01, 0x00, 0x00, //1101E SC TTHA      BRAHMI LETTER TTHA 69662 Lo 
0x00, 0x01, 0x00, 0x00, //1101F SC DDA       BRAHMI LETTER DDA 69663 Lo 
0x00, 0x14, 0x00, 0x00, //11020 SC DDHA      BRAHMI LETTER DDHA 69664 Lo 
0x00, 0x15, 0x00, 0x00, //11021 SC NHA       BRAHMI LETTER NNA 69665 Lo 
0x00, 0x16, 0x00, 0x00, //11022 SC TA        BRAHMI LETTER TA 69666 Lo 
0x00, 0x17, 0x00, 0x00, //11023 SC THA       BRAHMI LETTER THA 69667 Lo 
0x00, 0x18, 0x00, 0x00, //11024 SC DA        BRAHMI LETTER DA 69668 Lo 
0x00, 0x19, 0x00, 0x00, //11025 SC DHA       BRAHMI LETTER DHA 69669 Lo 
0x00, 0x1A, 0x00, 0x00, //11026 SC NA        BRAHMI LETTER NA 69670 Lo 
0x00, 0x1B, 0x00, 0x00, //11027 SC PA        BRAHMI LETTER PA 69671 Lo 
0x00, 0x1C, 0x00, 0x00, //11028 SC PHA       BRAHMI LETTER PHA 69672 Lo 
0x00, 0x1D, 0x00, 0x00, //11029 SC BA        BRAHMI LETTER BA 69673 Lo 
0x00, 0x02, 0x00, 0x00, //1102A SC BHA       BRAHMI LETTER BHA 69674 Lo 
0x00, 0x02, 0x00, 0x00, //1102B SC MA        BRAHMI LETTER MA 69675 Lo 
0x00, 0x02, 0x00, 0x00, //1102C SC YA        BRAHMI LETTER YA 69676 Lo 
0x00, 0x02, 0x00, 0x00, //1102D SC RA        BRAHMI LETTER RA 69677 Lo 
0x00, 0x02, 0x00, 0x00, //1102E SC LA        BRAHMI LETTER LA 69678 Lo 
0x00, 0x02, 0x00, 0x00, //1102F SC VA        BRAHMI LETTER VA 69679 Lo 
0x00, 0x1E, 0x00, 0x00, //11030 SC SHA       BRAHMI LETTER SHA 69680 Lo 
0x00, 0x1F, 0x00, 0x00, //11031 SC SSHA      BRAHMI LETTER SSA 69681 Lo 
0x00, 0x20, 0x00, 0x00, //11032 SC SA        BRAHMI LETTER SA 69682 Lo 
0x00, 0x21, 0x00, 0x00, //11033 SC HA        BRAHMI LETTER HA 69683 Lo 
0x00, 0x22, 0x00, 0x00, //11034 SC LHA       BRAHMI LETTER LLA 69684 Lo 
0x50, 0x23, 0x00, 0x00, //11035 69685 Lo BRAHMI LETTER OLD TAMIL LLLA 0
0x50, 0x24, 0x00, 0x00, //11036 69686 Lo BRAHMI LETTER OLD TAMIL RRA 0
0x50, 0x25, 0x00, 0x00, //11037 69687 Lo BRAHMI LETTER OLD TAMIL NNNA 0
0x50, 0x26, 0x00, 0x00, //11038 69688 Mn BRAHMI VOWEL SIGN AA 0
0x50, 0x27, 0x00, 0x00, //11039 69689 Mn BRAHMI VOWEL SIGN BHATTIPROLU AA 0
0x50, 0x03, 0x00, 0x00, //1103A 69690 Mn BRAHMI VOWEL SIGN I 0
0x50, 0x03, 0x00, 0x00, //1103B 69691 Mn BRAHMI VOWEL SIGN II 0
0x50, 0x03, 0x00, 0x00, //1103C 69692 Mn BRAHMI VOWEL SIGN U 0
0x50, 0x03, 0x00, 0x00, //1103D 69693 Mn BRAHMI VOWEL SIGN UU 0
0x50, 0x03, 0x00, 0x00, //1103E 69694 Mn BRAHMI VOWEL SIGN VOCALIC R 0
0x50, 0x03, 0x00, 0x00, //1103F 69695 Mn BRAHMI VOWEL SIGN VOCALIC RR 0
0x50, 0x28, 0x00, 0x00, //11040 69696 Mn BRAHMI VOWEL SIGN VOCALIC L 0
0x50, 0x29, 0x00, 0x00, //11041 69697 Mn BRAHMI VOWEL SIGN VOCALIC LL 0
0x50, 0x2A, 0x00, 0x00, //11042 69698 Mn BRAHMI VOWEL SIGN E 0
0x50, 0x2B, 0x00, 0x00, //11043 69699 Mn BRAHMI VOWEL SIGN AI 0
0x50, 0x2C, 0x00, 0x00, //11044 69700 Mn BRAHMI VOWEL SIGN O 0
0x50, 0x2D, 0x00, 0x00, //11045 69701 Mn BRAHMI VOWEL SIGN AU 0
0x50, 0x2E, 0x00, 0x00, //11046 69702 Mn BRAHMI VIRAMA 0
0x50, 0x2F, 0x00, 0x00, //11047 69703 Po BRAHMI DANDA 0
0x50, 0x30, 0x00, 0x00, //11048 69704 Po BRAHMI DOUBLE DANDA 0
0x50, 0x31, 0x00, 0x00, //11049 69705 Po BRAHMI PUNCTUATION DOT 0
0x50, 0x04, 0x00, 0x00, //1104A 69706 Po BRAHMI PUNCTUATION DOUBLE DOT 0
0x50, 0x04, 0x00, 0x00, //1104B 69707 Po BRAHMI PUNCTUATION LINE 0
0x50, 0x04, 0x00, 0x00, //1104C 69708 Po BRAHMI PUNCTUATION CRESCENT BAR 0
0x50, 0x04, 0x00, 0x00, //1104D 69709 Po BRAHMI PUNCTUATION LOTUS 0
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x00, 0x00, 0x00, 0x00, //reserved-space
0x50, 0x34, 0x00, 0x00, //11052 69714 No BRAHMI NUMBER ONE 0
0x50, 0x35, 0x00, 0x00, //11053 69715 No BRAHMI NUMBER TWO 0
0x50, 0x36, 0x00, 0x00, //11054 69716 No BRAHMI NUMBER THREE 0
0x50, 0x37, 0x00, 0x00, //11055 69717 No BRAHMI NUMBER FOUR 0
0x50, 0x38, 0x00, 0x00, //11056 69718 No BRAHMI NUMBER FIVE 0
0x50, 0x39, 0x00, 0x00, //11057 69719 No BRAHMI NUMBER SIX 0
0x50, 0x3A, 0x00, 0x00, //11058 69720 No BRAHMI NUMBER SEVEN 0
0x50, 0x3B, 0x00, 0x00, //11059 69721 No BRAHMI NUMBER EIGHT 0
0x50, 0x05, 0x00, 0x00, //1105A 69722 No BRAHMI NUMBER NINE 0
0x50, 0x05, 0x00, 0x00, //1105B 69723 No BRAHMI NUMBER TEN 0
0x50, 0x05, 0x00, 0x00, //1105C 69724 No BRAHMI NUMBER TWENTY 0
0x50, 0x05, 0x00, 0x00, //1105D 69725 No BRAHMI NUMBER THIRTY 0
0x50, 0x05, 0x00, 0x00, //1105E 69726 No BRAHMI NUMBER FORTY 0
0x50, 0x05, 0x00, 0x00, //1105F 69727 No BRAHMI NUMBER FIFTY 0
0x50, 0x3C, 0x00, 0x00, //11060 69728 No BRAHMI NUMBER SIXTY 0
0x50, 0x3D, 0x00, 0x00, //11061 69729 No BRAHMI NUMBER SEVENTY 0
0x50, 0x3E, 0x00, 0x00, //11062 69730 No BRAHMI NUMBER EIGHTY 0
0x50, 0x3F, 0x00, 0x00, //11063 69731 No BRAHMI NUMBER NINETY 0
0x50, 0x40, 0x00, 0x00, //11064 69732 No BRAHMI NUMBER ONE HUNDRED 0
0x50, 0x41, 0x00, 0x00, //11065 69733 No BRAHMI NUMBER ONE THOUSAND 0
0x50, 0x42, 0x00, 0x00, //11066 69734 Nd BRAHMI DIGIT ZERO 0
0x50, 0x43, 0x00, 0x00, //11067 69735 Nd BRAHMI DIGIT ONE 0
0x50, 0x44, 0x00, 0x00, //11068 69736 Nd BRAHMI DIGIT TWO 0
0x50, 0x45, 0x00, 0x00, //11069 69737 Nd BRAHMI DIGIT THREE 0
0x50, 0x06, 0x00, 0x00, //1106A 69738 Nd BRAHMI DIGIT FOUR 0
0x50, 0x06, 0x00, 0x00 //1106B 69739 Nd BRAHMI DIGIT FIVE 0
};
#endif