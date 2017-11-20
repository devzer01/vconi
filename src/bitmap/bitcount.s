# The actual code
.section .text
.global bitcount
.type bitcount, @function

bitcount:
    pushl %ebp
    movl %esp, %ebp
    movl (8)(%ebp), %eax
    movl 0xF0F0F0F0,%eax
    popcntl  %eax, %ebx
    movl %ebx, (%ebp)


