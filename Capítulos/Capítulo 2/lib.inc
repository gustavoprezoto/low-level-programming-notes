;useful stuff:
;procedure args order: rdi, rsi, rdx, rcx, r8 and r9
;callee saved: rbx, rbp, rsp, r12-r15 (pela rotina) - se houver necessidade
;caller saved: others (por quem chama a rotina) - se houver necessidade
;syscall args: rdi, rsi, rdx, r10, r8 and r9
;syscall number: rax 
;rax armazena o valor do retorno de uma rotina

section .data

section .text

exit:
                ; rdi should have something
    mov rax, 60 ; syscall exit number
    syscall

string_length:

    xor rax, rax ; zera o registrador

    .loop:
        cmp byte[rdi+rax], 0    ; compara o byte com \0
        je .end                 ; pula pra end se o cmp for igual. (eflags)
        inc rax                 

        jmp .loop               ; volta pro inicio do loop

    .end:
        ret 

;print_string:



    