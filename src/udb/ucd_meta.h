//
// Created by nayana on 11/18/17.
//

#ifndef VCONI_UCD_META_H
#define VCONI_UCD_META_H

typedef struct field_def {
    short index;
    unsigned char *name;
    unsigned char *status;
    unsigned char *detail;
} field_def;

struct field_def heads[15] = {

{.index = 0,  .name = "Code value normative",           .status = "Code value",  .detail = "in 4-digit hexadecimal format"},
{.index = 1,  .name = "Character name",                 .status = "normative",   .detail = "These names match exactly the names published in Chapter 14 of the Unicode Standard, Version 3.0."},
{.index = 2,  .name = "General Category",               .status = "normative",   .detail = "informative", "This is a useful breakdown into various "character types" which can be used as a default categorization in implementations. See below for a brief explanation."},
{.index = 3,  .name = "Canonical Combining Classes",    .status = "normative",   .detail = "The classes used for the Canonical Ordering Algorithm in the Unicode Standard. These classes are also printed in Chapter 4 of the Unicode Standard."},
{.index = 4,  .name = "Bidirectional Category",         .status = "normative",   .detail = "See the list below for an explanation of the abbreviations used in this field. These are the categories required by the Bidirectional Behavior Algorithm in the Unicode Standard. These categories are summarized in Chapter 3 of the Unicode Standard."},
{.index = 5,  .name = "Character Decomposition Mapping",.status = "normative",   .detail = "In the Unicode Standard, not all of the mappings are full (maximal) decompositions. Recursive application of look-up for decompositions will, in all cases, lead to a maximal decomposition. The decomposition mappings match exactly the decomposition mappings published with the character names in the Unicode Standard."},
{.index = 6,  .name = "Decimal digit value",            .status = "normative",   .detail = "This is a numeric field. If the character has the decimal digit property, as specified in Chapter 4 of the Unicode Standard, the value of that digit is represented with an integer value in this field"},
{.index = 7,  .name = "Digit value",                    .status = "normative",   .detail = "This is a numeric field. If the character represents a digit, not necessarily a decimal digit, the value is here. This covers digits which do not form decimal radix forms, such as the compatibility superscript digits"},
{.index = 8,  .name = "Numeric value",                  .status = "normative",   .detail = "This is a numeric field. If the character has the numeric property, as specified in Chapter 4 of the Unicode Standard, the value of that character is represented with an integer or rational number in this field. This includes fractions as, e.g., "1/5" for U+2155 VULGAR FRACTION ONE FIFTH Also included are numerical values for compatibility characters such as circled numbers."},
{.index = 9,  .name = "Mirrored",                       .status = "normative",   .detail = "If the character has been identified as a "mirrored" character in bidirectional text, this field has the value "Y"; otherwise "N". The list of mirrored characters is also printed in Chapter 4 of the Unicode Standard."},
{.index = 10, .name = "Unicode 1.0 Name",               .status = "informative", .detail = "This is the old name as published in Unicode 1.0. This name is only provided when it is significantly different from the Unicode 3.0 name for the character."},
{.index = 11, .name = "10646 comment field",            .status = "informative", .detail = "This is the ISO 10646 comment field. It is in parantheses in the 10646 names list."},
{.index = 12, .name = "Uppercase Mapping",              .status = "informative", .detail = "Upper case equivalent mapping. If a character is part of an alphabet with case distinctions, and has an upper case equivalent, then the upper case equivalent is in this field. See the explanation below on case distinctions. These mappings are always one-to-one, not one-to-many or many-to-one. This field is","informative","."},
{.index = 13, .name = "Lowercase Mapping",              .status = "informative", .detail = "Similar to Uppercase mapping"},
{.index = 14, .name = "Titlecase Mapping",              .status = "informative", .detail = "Similar to Uppercase mapping"}
} ;
 /**




        Lu	Letter, Uppercase
        Ll	Letter, Lowercase
        Lt	Letter, Titlecase
        Mn	Mark, Non-Spacing
        Mc	Mark, Spacing Combining
        Me	Mark, Enclosing
        Nd	Number, Decimal Digit
        Nl	Number, Letter
        No	Number, Other
        Zs	Separator, Space
        Zl	Separator, Line
        Zp	Separator, Paragraph
        Cc	Other, Control
        Cf	Other, Format
        Cs	Other, Surrogate
        Co	Other, Private Use




        Lm	Letter, Modifier
        Lo	Letter, Other
        Pc	Punctuation, Connector
        Pd	Punctuation, Dash
        Ps	Punctuation, Open
        Pe	Punctuation, Close
        Pi	Punctuation, Initial quote (may behave like Ps or Pe depending on usage)
        Pf	Punctuation, Final quote (may behave like Ps or Pe depending on usage)
        Po	Punctuation, Other
        Sm	Symbol, Math
        Sc	Symbol, Currency
        Sk	Symbol, Modifier
        So	Symbol, Other

  Bidirectional Category

Please refer to Chapter 3 for an explanation of the algorithm for Bidirectional Behavior and an explanation of the significance of these categories. An up-to-date version can be found on Unicode Technical Report #9: The Bidirectional Algorithm. These values are normative.

Type

        Description

L	Left-to-Right
LRE	Left-to-Right Embedding
LRO	Left-to-Right Override
R	Right-to-Left
AL	Right-to-Left Arabic
RLE	Right-to-Left Embedding
RLO	Right-to-Left Override
PDF	Pop Directional Format
EN	European Number
ES	European Number Separator
ET	European Number Terminator
AN	Arabic Number
CS	Common Number Separator
NSM	Non-Spacing Mark
BN	Boundary Neutral
B	Paragraph Separator
S	Segment Separator
WS	Whitespace
ON	Other Neutrals






<font>  	A font variant (e.g. a blackletter form).
<noBreak>  	A no-break version of a space or hyphen.
<initial>  	An initial presentation form (Arabic).
<medial>  	A medial presentation form (Arabic).
<final>  	A final presentation form (Arabic).
<isolated> 	An isolated presentation form (Arabic).
<circle>  	An encircled form.
<super>  	A superscript form.
<sub>  	    A subscript form.
<vertical>  A vertical layout presentation form.
<wide>  	A wide (or zenkaku) compatibility character.
<narrow>  	A narrow (or hankaku) compatibility character.
<small>  	A small variant form (CNS compatibility).
<square>  	A CJK squared font variant.
<fraction>  A vulgar fraction form.
<compat>  	Otherwise unspecified compatibility character.

0:	 Spacing, split, enclosing, reordrant, and Tibetan subjoined
1:	 Overlays and interior
7:	 Nuktas
8:	 Hiragana/Katakana voicing marks
9:	 Viramas
10:	 Start of fixed position classes
199: End of fixed position classes
200: Below left attached
202: Below attached
204: Below right attached
208: Left attached (reordrant around single base character)
210: Right attached
212: Above left attached
214: Above attached
216: Above right attached
218: Below left
220: Below
222: Below right
224: Left (reordrant around single base character)
226: Right
228: Above left
230: Above
232: Above right
233: Double below
234: Double above
240: Below (iota subscript)
**/
#endif //VCONI_UCD_META_H
