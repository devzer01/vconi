BITS 64
section .text
global bitcount

bitcount:
    mov rcx, rdi
    popcnt rax, rcx
    ret

global flip

flip:
    pshufb rdi, rsi
    ret