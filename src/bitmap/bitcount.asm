BITS 64
section .text
global bmp_bitcount

bmp_bitcount:
    mov rcx, rdi
    popcnt rax, rcx
    ret

global bmp_bcount32

bmp_bcount32:
    mov ecx, edi
    popcnt eax, ecx
    ret

global bmp_flip

bmp_flip:
    movq mm0, [rdi]
    movq mm1, [rsi]
    pshufb mm0, mm1
    movq [rdi], mm0
    ret

    ;0x000000efab6745124523452323232323,
    ;0x843b031b01000000efcdab8967452312,
    ;0x01060504030201070605040302010403,
    ;                          7  6   5  4  3  2  1   0
    ;0x01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10
    ;0x0d 0c 0f 0e 0d 0c 0b 0a 09 0f 0e 0d 0c 0b 0a 0f,
    ;561
    ;0x03040102030405060701020304050601,

    ;