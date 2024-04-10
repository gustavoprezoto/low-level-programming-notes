;useful stuff:
;procedure args order: rdi, rsi, rdx, rcx, r8 and r9
;callee saved: rbx, rbp, rsp, r12-r15 (pela rotina) - se houver necessidade
;caller saved: others (por quem chama a rotina) - se houver necessidade
;syscall args: rdi, rsi, rdx, r10, r8 and r9
;syscall number: rax 
;rax armazena o valor do retorno de uma rotina

section .data
newline: db 0x0A ; ascii 10 ou 0x0A == \n
minus_sign: db 0x2D ; ascii 45 ou 0x2D == -

section .text

exit:
    mov rax, 60 ; syscall exit number
    xor rdi, rdi ; defining rdi to 0 (exit code)
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
    mov rdx, rax    ; param rdx = string size in bytes
    mov rax, 1      ; param rax = syscall number
    mov rsi, rdi    ; param rsi = string
    mov rdi, 1      ; param rdi = descriptor (stdout nesse caso == 1)

    syscall
    ret

print_char:
    mov rdx, 1      ; param rdx = char size (1 byte)
    mov rax, 1      ; param rax = syscall number
    mov rsi, rdi    ; param rsi = inputted char
    mov rdi, 1      ; param rdi = descriptor (stdout == 1)

    syscall
    ret

print_newline:
    mov rdi, newline ; param rdi = \n or ascii 10 or 0xA
    call print_char

    ret

print_uint:
    ;rdi(1rst arg) should contain 8byte uint
    mov rax, rdi    ; rax is dividend
    mov rcx, 10     ; decimal base (divisor)
    mov rsi, rsp    ; rsi now points to stacks top
    push 0          ; null terminator for strings end. 1 byte of 8
    dec rsi         ; pointing to the last char before 0 null
    sub rsp, 16     ; adding +16 bytes (total of 24b) for space ((null + 7 bytes) + 16) (space for unsigned long and a null terminator)


.print_uint_loop:  
    cmp rax, 0      ; this loop will continue until rax content (dividend) / 10 (rcx) == 0
    je .print_uint_end
    xor rdx, rdx    ; cleaning rdx
    div rcx         ; this divides value in RDX:RAX format,
                    ; where RAX receives the quocient division
                    ; and RDX receives the remainder
    add rdx, 48     ; this converts RDX to ascii char. (48 = number 0 in ascii)
    dec rsi         ; points to next space in memory
    mov byte[rsi], dl ; writing the lower byte at RDX into the stack
    jmp .print_uint_loop

.print_uint_end:
    mov rdi, rsi
    call print_string
    add rsp, 24 ;getting back rsp to stack top

    ret

print_int:
    ; rdi (1st param) should have a 8 byte integer
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

    



    