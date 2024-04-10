section .data

section .text
%include "lib.inc"
global _start
_start:
    mov rdi, 123456789
    call print_int
    call print_newline

    mov rdi, -123456789
    call print_int
    call print_newline

    mov rdi, 0
    call exit