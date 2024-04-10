section .data
newline_char: db 10 
codes: db '0123456789abcdef'

section .text 
global _start

print_newline:
    mov rax, 1              ;numero da syscall
    mov rdi, 1              ;descritor (stdout) (arg 1)
    mov rsi, newline_char   ;mensagem (arg 2)
    mov rdx, 1              ;tamanho da mensagem em bytes (arg 3)
    syscall                 ;realizando chamada da syscall

    ret

print_hex:
    mov rax, rdi

    ;argumentos para a função
    mov rdi, 1 ; descritor stdout pra chamada da syscall write
    mov rdx, 1 ; tamanho da mensagem em write. Nesse caso 1 byte

    mov rcx, 64 ; 64 bits para iterar

    iterate:
        push rax ;adicione na pilha o rax (registrador callee saved) 1122334455667788
        sub rcx, 4 ; retire 4 bits
        sar rax, cl ; desloca rcx bits para a direita
        and rax, 0xf ; limpa todos os bits, menos os 4 menos significativos
        lea rsi, [codes + rax] ; na teoria obtem o codigo de caractere de um digito hexadecimal
        mov rax, 1 ; numero da syscall (parametros definidos anteriormente)

        push rcx    ;isso pq syscall altera rcx
        syscall

        pop rcx

        pop rax
        test rcx, rcx ; faz um AND binário 
        jnz iterate ;se o resultado do test != 0, ele itera mais uma vez

        ret

_start:
    mov rdi, 0x1122334455667788 ; argumento 1 usado em print_hex
    call print_hex
    call print_newline

    mov rax, 60         ; o numero da syscall 'exit' é 60
    xor rdi, rdi        ; faz uma operação XOR e armazena o valor no próprio rdi. matematicamente vc fazer um xor(X, X) vc recebe o retorno 0, pois são iguais.
                        ; portanto essa instrução está settando o primeiro parametro (rdi) da syscall exit com 0.
    syscall
