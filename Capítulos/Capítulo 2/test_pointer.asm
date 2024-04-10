section .data
test: dq -1

section .text

global _start
_start:
    mov byte[test], 1   ;1 byte
    mov word[test], 1   ;2 bytes
    mov dword[test], 1  ;4 bytes
    mov qword[test], 1  ;8 bytes

    mov rax, 60         ; o numero da syscall 'exit' é 60
    xor rdi, rdi        ; faz uma operação XOR e armazena o valor no próprio rdi. matematicamente vc fazer um xor(X, X) vc recebe o retorno 0, pois são iguais.
                        ; portanto essa instrução está settando o primeiro parametro (rdi) da syscall exit com 0.
    syscall