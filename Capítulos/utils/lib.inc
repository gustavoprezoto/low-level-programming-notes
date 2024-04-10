;coisas úteis:
;ordem dos parametros de um rotina: rdi, rsi, rdx, rcx, r8 e r9
;callee saved: rbx, rbp, rsp, r12-r15 (pela rotina) - se houver necessidade
;caller saved: others (por quem chama a rotina) - se houver necessidade
;syscall args: rdi, rsi, rdx, r10, r8 and r9
;numero da syscall: rax 
;rax armazena o valor do retorno de uma rotina

section .data
newline: db 0x0A ; ascii 10 ou 0x0A == \n
minus_sign: db 0x2D ; ascii 45 ou 0x2D == -

section .text

exit:
    mov rax, 60 ; número da syscall de exit
    xor rdi, rdi ; definindo rdi como 0 (código de saída 0)
    syscall

string_length:

    xor rax, rax ; zera o registrador

.loop:
    cmp byte[rdi+rax], 0    ; compara o byte com o ascii \0
    je .end                 ; pula pra end se o cmp for igual. (eflags)
    inc rax                 

    jmp .loop               ; volta pro inicio do loop

.end:
    ret                     ; retorna em rax

print_string:
    call string_length
    mov rdx, rax    ; param rdx = tamanho da string em bytes
    mov rax, 1      ; param rax = número da syscall
    mov rsi, rdi    ; param rsi = string que ira ser printada
    mov rdi, 1      ; param rdi = descritor (stdout nesse caso, então 1)

    syscall
    ret

print_char:
    mov rdx, 1      ; param rdx = tamanho do char (1 byte)
    mov rax, 1      ; param rax = número da syscall
    mov rsi, rdi    ; param rsi = inputted char
    mov rdi, 1      ; param rdi = descritor (stdout == 1)

    syscall
    ret

print_newline:
    mov rdi, newline ; param rdi = o que vai ser printado
    call print_char

    ret

print_uint:
    ;rdi(primeiro parametro) deve conter um inteiro não assinado que pode ser até um 24 bytes (unsigned long)
    mov rax, rdi    ; rax é o dividendo
    mov rcx, 10     ; base decimal (divisor)
    mov rsi, rsp    ; rsi agora aponta pro topo da pilha
    push 0          ; adiciona um terminador nulo na pilha (1 byte de 8)
    dec rsi         ; decrementa o rsi e passa apontar para o último char antes do terminador nulo
    sub rsp, 16     ; adiciona +16 bytes (total de 24 (unsigned long)) ((null + 7 bytes) + 16 bytes)


.print_uint_loop:  
    cmp rax, 0      
    je .print_uint_end  ; esse loop vai continuar até o conteúdo de rax (dividendo) por 10 == 0
    xor rdx, rdx    ; limpa rdx
    div rcx         ; divide rax por rcx e armazena o valor no formato RDX:RAX, onde
                    ; RAX é o quociente da divisão 
                    ; e RDX recebe o resto da divisão
    add rdx, 48     ; converte o rdx para ascii, pois o decimal 48 é 0 em ascii
    dec rsi         ; decrementa rsi para apontar para o próximo espaço vago na memória
    mov byte[rsi], dl ; escreve o menor byte de rdx (dl) na pilha
    jmp .print_uint_loop

.print_uint_end:
    mov rdi, rsi
    call print_string
    add rsp, 24 ; voltando rsp ao topo da pilha

    ret

print_int:
    ; rdi (primeiro parametro) deve conter um inteiro 8 bytes
    mov rsi, rdi
    sar rsi, 63     ; move o bit mais significativo (identificador para negativo em complemento de dois) para a primeira posição
    cmp sil, 0xFF   ; compara os 8 bytes menos significativos de rsi com 0xFF, 
                    ; se for igual quer dizer que é negativo (orquestrado pela instrução acima)
    jne print_uint  ; se não for negativo == pula pra função de printar unsigned int
    push rdi        ; registrador caller-saved
    mov rdi, minus_sign   
    call print_char
    pop rdi         ; recuperando registrador caller-saved
    neg rdi         ; nega os bits de rdi e adiciona 1
    call print_uint

    ret

    



    