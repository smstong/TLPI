    .global _start
    .text

_start:
    push %rbp
    mov %rsp, %rbp
    mov %edi, -0x4(%rbp)
    mov %rsi, -0x10(%rbp)
    mov $0x9,%eax
    leaveq
    retq
