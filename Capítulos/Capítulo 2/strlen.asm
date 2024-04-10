global _start

section .data
    test_string: db "abcdddf", 0

section .text
%include "lib.inc"

_start:
    mov rdi, test_string ; argumento para strlen
    call string_length
    mov rdi, rax ; valor do retorno da syscall exit

    call exit