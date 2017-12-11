//
// Created by nayana on 11/22/17.
//

#include "bitmap.h"
#include "stats.h"
#include "vconi.h"
#define CHAR_DB_SIZE 13
char *filename;
unsigned long int signature[CHAR_DB_SIZE][32] = {
//unsigned long int _kuyanna[] = {
        {
                807141376,
                2046754816,
                4026499072,
                3481763840,
                484687872,
                806469632,
                538492928,
                1091092480,
                1662566400,
                4294492160,
                3220799488,
                2667544576,
                1572864,
                1073152,
                1597440,
                2080768,
                1032192,
        },
//unsigned long int _ayanna[] =
        {
                523239424,
                479723520,
                281804800,
                1070333952,
                2016149504,
                1886912512,
                1883242496,
                4030726144,
                1883242496,
                2018246656,
                1073217536,
                121634816,
                4194304,
                4194304,
                4194304,
                4194304,
                4194304
        },
        {
//unsigned long int __combuwa[] = {
                62914560,
                536346624,
                807141376,
                1669726208,
                1207042048,
                1146224640,
                3336044544,
                3818389504,
                1882718208,
                2146959360,
                1072693248,
                534773760
        },
        {

//unsigned long int __layanna[] = {
                32505856,
                268173312,
                1007026176,
                2013396992,
                4093313024,
                3762487296,
                3766353920,
                3759669248,
                3758096384,
                3758096384,
                4026597376,
                4026597376,
                2013396992,
                2080768000,
                1058799616,
                267911168,
                25165824
        },
        {
//unsigned long int yayanna[] = {
                7864320,
                214695936,
                1015283712,
                1627127808,
                3222011904,
                2147876864,
                2147614720,
                3238133760,
                3280863232,
                4294836224,
                2147221504,
                1022885888

        },
        {
//unsigned long int nayanna[] =  {
                270401536,
                2088730624,
                1711259648,
                1736695808,
                115400704,
                202403840,
                270036992,
                269496320,
                540553216,
                4294451200,
                2146459648,
                535019520
        },
        {
                //unsigned long int alapilla[] = {
                2013265920,
                2080374784,
                2348810240,
                2382364672,
                234881024,
                234881024,
                234881024,
                201326592,
                2348810240,
                4227858432,
                2013265920
        },
        {
//unsigned long int vayanna[] = {
                260046848,
                817889280,
                1080033280,
                271581184,
                2081423360,
                1678770176,
                1041235968,
                1611661312,
                3222274048,
                2150629376,
                3228565504,
                1893728256,
                2143289344,
                251658240
        },
        {
//unsigned long int vayanna2[] = {
                117440512,
                532676608,
                1613758464,
                1075314688,
                403177472,
                2081161216,
                1644429312,
                34340864,
                1040449536,
                1074528256,
                3222011904,
                3223060480,
                3761766400,
                4294443008,
                2146435072,
                1069547520
        },
        {                //yayanna small
               15728640,
               965738496,
               1106247680,
               3224371200,
               2148007936,
               2148007936,
               3255304192,
               3340238848,
               2146959360,
               1039138816
        },
        {           //hal layanna
                    786432,
                    655360,
                    655360,
                    917504,
                    524288,
                    267911168,
                    471334912,
                    805830656,
                    1676935168,
                    1082916864,
                    3229089792,
                    3221225472,
                    3221225472,
                    3221487616,
                    1610874880,
                    1879834624,
                    941096960,
                    535822336,
                    130023424
        },
        {           //nayanna
                1895563264,
                3955097600,
                3473342464,
                230883328,
                272728064,
                543260672,
                1080131584,
                3233873920,
                2143485952,
                1057882112
        } , { //kombuwa
                264241152,
                946864128,
                1661992960,
                1204289536,
                3425173504,
                3340763136,
                1075838976,
                1893728256,
                1069547520,
                528482304
        }
};

unsigned char *wchar[] = {
        "kuyanna", "ayanna", "kombuwa", "layanna", "yayanna", "nayanna",
        "alapilla", "vayanna",
        "vayanna", "yayanna", "hal layanna", "nayanna", "kombuwa" };
int32_t codepoints[] = {
                  3482, 3461, 3545, 3517, 3514, 3505,
                  3535, 3520, 3520,
                  3535, 3514, 3517, 3499, 3545,
                  3482, 3461, 3482, 3461, 3482, 3461, 3482, 3461, 3482, 3461, 3482, 3461
};

bmp_io_t test_data[3] = {
                {
                        .filename = "test-data/8x8-1.bmp",
                        .bit_per_px = 1,
                        .px.width = 8,
                        .px.height = 8,
                        .ints.width = 1,
                        .ints.height = 1,
                        .chars.width = 4,
                        .chars.height = 4
                },
                {
                        .filename = "test-data/8x8-5.bmp",
                        .bit_per_px = 1,
                        .px.width = 11,
                        .px.height = 11,
                        .ints.width = 1,
                        .ints.height = 1,
                        .chars.width = 4,
                        .chars.height = 4
                },
                {
                        .filename = "test-data/65x65-1.bmp",
                        .bit_per_px = 1,
                        .px.width = 65,
                        .px.height = 65,
                        .ints.width = 3,
                        .ints.height = 3,
                        .chars.width = 12,
                        .chars.height = 12
                },

        };


void _load() {
    if (filename != NULL) {
        bmp_open(filename);
    } else {
        bmp_open("test-data/8x8-1.bmp");
    }
}

void bmp_static_test() {
    unsigned long int data[4 * 3][2] = {
            {8,  0},
            {7,  0},
            {31, 0},
            {33, 1},
            {32, 0},
            {0,  0},
            {65, 0},
            {64, 1},
            {9,  0},
            {96, 0},
            {75, 0},
            {39, 1},
    };
    for (int i = 0; i < 12; i++) {
        printf("col %ld %ld int-idx %#0x - %#0x \n",
               data[i][0], data[i][1],
               __bmp_bit2intidx(data[i][0]),
               __bmp_col2mask(data[i][0]));
    }
}

void bmp_position_test() {
    if (filename != NULL) {
        bmp_open(filename);
    } else {
        bmp_open("test-data/8x8-1.bmp");
    }

    printf("col2charmask(0) %#0x \n", __bmp_col2mask(0));
    unsigned int index = bmp_row_offset(0); // if negative then out of bound
    /*printf("offset 0:%d %#0x b:"
                   PRINTF_BINARY_PATTERN_INT32 "\n", index,
           bmp_io->bmp_data[index],
           PRINTF_BYTE_TO_BINARY_INT32(bmp_io->bmp_data[index]));*/
    unsigned int *buffer = malloc(sizeof(unsigned int) * bmp_io->ints.width);
    buffer = bmp_row_buffer(0, &buffer, bmp_io->ints.width);
    short c_col = 0;
    while (c_col < bmp_io->ints.width) {
        printf("b:%#08X %#08X %#08X b:"
                       PRINTF_BINARY_PATTERN_INT32 "\n", c_col, bmp_io->bmp_data[index] + c_col, ptrval(buffer, c_col),
               PRINTF_BYTE_TO_BINARY_INT32(ptrval(buffer, c_col)));
        c_col++;
    }
    free(buffer);

    unsigned int *char_buffer = (unsigned int *) malloc(sizeof(unsigned int) * bmp_io->px.height);
    char_buffer = bmp_col_buffer(0, &char_buffer, bmp_io->px.height);
    unsigned int bitcount = bmp_col_bit_count(0);
    c_col = 0;
    free(buffer);
    while (c_col < bmp_io->px.height) {
        buffer = malloc(sizeof(unsigned int) * 3);
        buffer = bmp_row_buffer(c_col, &buffer, 3);
        printf("b:%d %#0x %#0x b:"
                       PRINTF_BINARY_PATTERN_INT32 ", " PRINTF_BINARY_PATTERN_INT32 "\n", c_col,
               char_buffer[index] + c_col, bitcount,
               PRINTF_BYTE_TO_BINARY_INT32(*(char_buffer + c_col)), PRINTF_BYTE_TO_BINARY_INT32(*buffer));
        c_col++;
        free(buffer);
    }
    unsigned long int __row = 3, __col = 8;

    /*   for(int i = 0; i < bmp_io->px.height; i++) {
           unsigned int mask = __col2intmask(i);
           printf("%#2d " PRINTF_BINARY_PATTERN_INT32 "\n", i , PRINTF_BYTE_TO_BINARY_INT32(mask));
       }*/

    /*unsigned int _offset = (col / 31);
    unsigned long int _height = bmp_io->ints.height - 1;
    while(_height <= 0) {

        u_int32_t val = (u_int32_t) (ptrval(buffer,_offset) & __col2intmask(col));
        bmp_io->col_px_count[col] += bmp_bcount32(val);
        _height--;
    }*/

    u_int32_t val = (u_int32_t)(ptrval(char_buffer, __row) & __bmp_col2mask(__col));
    printf(PRINTF_BINARY_PATTERN_INT32 "\n"
                   PRINTF_BINARY_PATTERN_INT32 "\n"
                   PRINTF_BINARY_PATTERN_INT32 "\n", PRINTF_BYTE_TO_BINARY_INT32(ptrval(char_buffer, __row)),
           PRINTF_BYTE_TO_BINARY_INT32(__bmp_col2mask(__col)), PRINTF_BYTE_TO_BINARY_INT32(val));

    /*for (int i = 0; i < bmp_io->px.width; i++) {
        printf("col %d bit count %d \n", i, bmp_col_bit_count(i));
    }
*/
    for (int r = 2; r < 4; r++) {
        for (int i = 0; i < bmp_io->px.width; i++) {
            char_buffer = bmp_col_buffer_offset(i, &char_buffer, r, 5);
            unsigned int counter = bmp_col_bit_count_offset(i, r, 5);
            printf("%d:bit " PRINTF_BINARY_PATTERN_INT32 " %d \n", i, PRINTF_BYTE_TO_BINARY_INT32(*char_buffer),
                   counter);
        }
    }

    unsigned int *buff = bmp_row_counts();
    int i = 0;
    while (i < bmp_io->px.height) {
        printf("c:%d %d \n", i, *(buff + i));
        i++;
    }

    unsigned int *cbuff = bmp_col_counts();
    i = 0;
    while (i < bmp_io->px.width) {
        printf("c:%d %d \n", i, *(cbuff + i));
        i++;
    }

    /*printf("b:0 %#0x %#0x \n", bmp_io->bmp_data[index]+1, *buffer+1);
    printf("b:0 %#0x %#0x \n", bmp_io->bmp_data[index]+2, *buffer+2);*/

    //printf("row data %#0x %#0x %#0x \n", *(bmp_io->bmp_data+index), *(bmp_io->bmp_data+index+1), bmp_io->bmp_data[index+2] );
    //int i = 0;
    /*while(i < bmp_io->ints.width) {
        printf("test %d ", bmp_io->bmp_data[index+i]);
        i++;
    }*/
    /**
     * int main() {
    long long int flag = 1648646756487983144ll;
    printf("My Flag "
                   PRINTF_BINARY_PATTERN_INT64 "\n",
           PRINTF_BYTE_TO_BINARY_INT64(flag));
    return 0;
}
     */
    /*for (int i = 0; i < bmp_io->px.height; i++) {
        for (int x = 0; x < bmp_io->px.width; x++) {
            //printf(" %d ", bmp_px(i, x));
        }
        printf("\n");
    }*/
}

void bmp_test_init() {
    for (int i = 0; i < 3; i++) {

        bmp_open(test_data[i].filename);

        struct bmp_dimension _px[2] = {bmp_io->px, test_data[i].px};
        struct bmp_dimension _ints[2] = {bmp_io->ints, test_data[i].ints};
        struct bmp_dimension _chars[2] = {bmp_io->chars, test_data[i].chars};


        printf("pixels %lu %lu - %lu  %lu\n",
               _px[0].width, _px[1].width, _px[0].height, _px[1].height);

        printf("ints %lu %lu - %lu  %lu\n",
               _ints[0].width, _ints[1].width, _ints[0].height, _ints[1].height);

        printf("chars %lu %lu - %lu  %lu\n",
               _chars[0].width, _chars[1].width, _chars[0].height, _chars[1].height);

    }
}

void stat_unit_test_row_col() {
    _load();

    stat_row *root = stat_row_get();
    stat_row *cell = root;
    while (cell != NULL) {
        printf("i: %d s: %ld :e %ld \n", cell->index, cell->gap.start, cell->gap.end);
        (cell) = cell->next;
    }

    root = stat_col_get();
    cell = root;
    while (cell != NULL) {
        printf("i: %d s: %ld :e %ld \n", cell->index, cell->gap.start, cell->gap.end);
        (cell) = cell->next;
    }
}

//stat_cell_get_filter
void stat_unit_test_filter() {
    _load();

    stat_cell *root_cell = stat_cell_get_filter();
    stat_cell *cell = root_cell;
    while (cell != NULL) {

        unsigned char *cell_header = malloc(sizeof(unsigned char) * 20);
        sprintf(cell_header, "[(%ld, %ld),(%ld, %ld)] =>", cell->row.start, cell->col.start, cell->row.end,
                cell->col.end);
        printf("%18s\n", cell_header);
        unsigned char *buffer = bmp_matrix_get(cell);
        unsigned long int width = (cell->col.end - cell->col.start);
        unsigned long int height = (cell->row.end - cell->row.start);
        bmp_draw_buffer(&buffer, width, height, cell->col.start, cell->col.end);
        //printf("buff %#9x", *buffer);
        if (cell->next != NULL && cell->row.start != cell->next->row.start) {
            printf("\n");
        }
        (cell) = cell->next;

    }
    printf("\n");
}

/*unsigned int scan_char(unsigned int idx)
{
    unsigned long int __row = 0;
    unsigned long int __height = 32;
    while (__row < __height) {
        unsigned long int needle = *(*(cell->masked + __row));
        for (int i = __start; i < 14; i++) {
            if (needle == (signature[0][i] & needle)) {
                long int __offset = __row - i;
                if (__start == 0) __start = i + 1;
                //printf("%ld \n", __offset);
                if (__offset <= 3) match++;
                break;
            }

        }
        __row++;
    }
}*/

unsigned int find_match_index(unsigned long int mask, unsigned long int chardex)
{
    unsigned long int _i = 0;
    while (_i < 8) {
        if (signature[chardex][_i] == mask) {
            return _i;
        }
        _i++;
    }
    return 0;
}

int is_potential(unsigned int *base, unsigned long int needle)
{
    unsigned long int _i =0;
    while(_i < CHAR_DB_SIZE) {
        if (*(base+_i) == needle) return 1;
        _i++;
    }
    return 0;
}

unsigned int identify_cell(stat_cell *cell)
{
    unsigned long int width = (cell->col.end - cell->col.start) + 1;
    unsigned long int height = (cell->row.end - cell->row.start) + 1;
    unsigned long int _row = 0, mrow = 0;//cell->row.start;
    long int *match = malloc(sizeof(long int) * CHAR_DB_SIZE);
    while (_row < height) {
        uint32_t v = (uint32_t) * (*(cell->masked + _row));
        int count = bmp_bcount32(v);
        if (count != 0) {
            unsigned int chardex = 0;
            int *potential = malloc(sizeof(int) * CHAR_DB_SIZE);
            int *diff = malloc(sizeof(int) * CHAR_DB_SIZE);
            int *mapped = malloc(sizeof(int) * CHAR_DB_SIZE);
            int *basePotential = potential;
            while (chardex < CHAR_DB_SIZE) {
                *(potential+chardex) = -1;
                *(match+chardex) = -1;
                chardex++;
            }
            chardex = 0;
            unsigned long int _cursor = (unsigned long int) *cell->masked[_row];
            //printf("%ld ", _cursor);
            while (chardex < CHAR_DB_SIZE) {
                if (_cursor == signature[chardex][mrow]) {
                    //printf("match");
                    *(potential) = chardex;
                    potential++;
                    mrow++;
                    break;
                } else {
                    unsigned int _p = find_match_index(v, chardex);
                    if (is_potential(basePotential, _p) != 0) {
                        *(potential) = _p;
                        potential++;
                        break;
                    }
                }
                chardex++;
            }
            chardex = 0;
            while(chardex < CHAR_DB_SIZE) {
                int _x = *(basePotential+chardex);
                if (_x != -1) {
                    *(match+_x) += 1;
                } else {

                }
                chardex++;
            }
            free(diff);
            free(mapped);
            free(basePotential);
        }
        _row++;
    }

    long int *baseMatch = match;
    long int maxMatch = -1, mIndex = 0, charIdx = -1;
    while (mIndex < 9) {
        //printf(" %ld - %ld \n", mIndex, *(baseMatch+mIndex));
        if (*(baseMatch+mIndex) > maxMatch) {
            maxMatch = *(baseMatch+mIndex);
            charIdx = mIndex;
        }
        mIndex++;
    }
    free(match);

    if (charIdx != -1) {
        int codep = codepoints[charIdx];
        unsigned char *buff = malloc(sizeof(unsigned char) * 4);
        buff = getuchar(codep, buff);
        //printf("best match at index %ld is %s which is %s\n", charIdx, wchar[charIdx], buff);
        printf(" %s ", buff);
        free(buff);
        return 1;
    }

    printf(" . ");

    return 0;

}

void normalize_test()
{
    _load();
    stat_cell *root_cell = stat_cell_get();
    stat_cell *cell = root_cell;

    while (cell != NULL && cell->index != -1) {

        unsigned char *cell_header = malloc(sizeof(unsigned char) * 30);
        printf("[(%ld, %ld),(%ld, %ld)] => \n", cell->row.start, cell->col.start, cell->row.end,
                cell->col.end);
        unsigned char *buff = bmp_char_matrix_get(cell);
        unsigned long int width = (cell->col.end - cell->col.start) + 1;
        unsigned long int height = (cell->row.end - cell->row.start) + 1;
        bmp_print_matrix(buff, width, height);
        //bmp_draw_buffer(&buffer, width, height, cell->col.start, cell->col.end);
        //bmp_draw_buffer(&buffer, width, height, cell->col.start, cell->col.end);
        //printf("-----\n");
        shape shape1 = bmp_normalize_shape_get(cell); //TODO: pass cell
        bmp_print_shape(shape1);
        unsigned long int _row = 0;
        unsigned long int match = 0;
        printf("\n\n\n");
        /*if (identify_cell(cell) != 0) {
            //bmp_draw_buffer(&buffer, width, height, cell->col.start, cell->col.end);
        } else {

        }*/
        //printf("buff %#9x", *buffer);
        if (cell->next != NULL && cell->row.start != cell->next->row.start) {
            printf("\n");
        }
        stat_cell *pcell = (cell);
        (cell) = cell->next;
        free(pcell);
    }
    free(root_cell);
    free(cell);
    //printf("\n");
    free(bmp_io);


}

void find_box_test() {
    _load();

    stat_cell *root_cell = stat_cell_get();
    stat_cell *cell = root_cell;
    while (cell != NULL && cell->index != -1) {

        unsigned char *cell_header = malloc(sizeof(unsigned char) * 30);
        sprintf(cell_header, "[(%ld, %ld),(%ld, %ld)] =>", cell->row.start, cell->col.start, cell->row.end,
                cell->col.end);
        unsigned char *buffer = bmp_matrix_get(cell);
        unsigned long int width = (cell->col.end - cell->col.start) + 1;
        unsigned long int height = (cell->row.end - cell->row.start) + 1;
        //bmp_draw_buffer(&buffer, width, height, cell->col.start, cell->col.end);
       // cell->masked = bmp_normalize_shape_get(&cell); //TODO: pass cell
        unsigned long int _row = 0;
        unsigned long int match = 0;

        //printf("buff %#9x", *buffer);
        if (cell->next != NULL && cell->row.start != cell->next->row.start) {
            printf("\n");
        }
        stat_cell *pcell = (cell);
        (cell) = cell->next;
        free(pcell);
    }
    free(root_cell);
    free(cell);
    //printf("\n");
    free(bmp_io);
}

void stat_unit_test() {
    _load();

    stat_cell *root_cell = stat_cell_get();
    stat_cell *cell = root_cell;
    while (cell != NULL) {

        unsigned char *cell_header = malloc(sizeof(unsigned char) * 20);
        sprintf(cell_header, "[(%ld, %ld),(%ld, %ld)] =>", cell->row.start, cell->col.start, cell->row.end,
                cell->col.end);
        printf("%18s\n", cell_header);
        unsigned char *buffer = bmp_matrix_get(cell);
        unsigned long int width = (cell->col.end - cell->col.start) + 1;
        unsigned long int height = (cell->row.end - cell->row.start) + 1;
        bmp_draw_buffer(&buffer, width, height, cell->col.start, cell->col.end);
        cell->masked = bmp_graph_buffer(&buffer, width, height, cell->col.start, cell->col.end);
        unsigned long int _row = 0;
        printf("\n { ");
        while (_row < height) {
            printf(" %ld , \n", *(*(cell->masked + _row)));
            _row++;
        }
        printf(" } ");
        //printf("buff %#9x", *buffer);
        if (cell->next != NULL && cell->row.start != cell->next->row.start) {
            printf("\n");
        }
        (cell) = cell->next;

    }
    printf("\n");
}

void cell_raw_test() {
    _load();

    stat_row *row_root = stat_row_get();
    //stat_row *col_root = stat_col_get();
    stat_row *_row = row_root;
    //stat_row *_col = col_root;
    while (_row != NULL) {
        //printf("(%d) => [%ld,%ld] => ", _row->index, _row->gap.start, _row->gap.end);
        stat_row *col_root = stat_col_get_offset(0, bmp_io->px.width, _row->gap.start,
                                                 (_row->gap.end - _row->gap.start) + 1);
        stat_row *_col = col_root;
        while (_col != NULL) {
            //printf("(%d) [%ld,%ld] ", _col->index, _col->gap.start, _col->gap.end);
            printf("[(%ld, %ld),(%ld, %ld)], ", _row->gap.start, _col->gap.start, _row->gap.end, _col->gap.end);
            (_col) = _col->next;
        }
        printf("\n");
        (_row) = _row->next;
    }
}

void bmp_offset_test() {
    if (filename != NULL) {
        bmp_open(filename);
    } else {
        bmp_open("test-data/8x8-1.bmp");
    }
    for (int i = 0; i < bmp_io->px.width; i++) {
        printf("%d, 2, 1 %d \n", i, bmp_col_bit_count_offset(i, 0, 8));
    }
}

int main(int argc, char **argv) {
    filename = argv[1];
    char t_case = *argv[2];

    switch (t_case) {
        //bmp_test_init();
        //bmp_static_test();
        //bmp_position_test();
        case 'r':
            cell_raw_test();
            break;
        case 'o':
            bmp_offset_test();
            break;
        default:
            //stat_unit_test_filter();
            //stat_unit_test();
            //find_box_test();
            normalize_test();
            break;
    }

    return 0;
}
