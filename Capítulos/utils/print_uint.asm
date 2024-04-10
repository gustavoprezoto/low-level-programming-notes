section .data

section .text
%include "lib.inc"
global _start
_start:
    mov rdi, 18446744073709551615;
    call print_uint;
    mov rdi, 0;
    call exit;