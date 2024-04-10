global _start

section .data
message: db 'hello, world!', 10; db = define bytes: definindo 9 bytes pra frase 'Olá mundo' e adicionando mais um byte (valor ascii 10 = \n) no final

section .text
_start:
    mov rax, 1          ; o numero da chamada do sistema deve ser armazenado no registrador rax
    mov rdi, 1          ; argumento 1: descritor (stdout == 1)
    mov rsi, message    ; argumento 2: onde começa a string. (Acredito q message seja um ponteiro pra sequencia de bytes onde começa a string)
    mov rdx, 14         ; argumento 3: total de bytes escritos. Nesse caso: 9 bytes da frase 'Olá mundo' + 1 byte de 10 (\n)
    syscall             ; instrução que executa a chamada do sistema 

; Ao executar esse arquivo, veremos uma falha de segmentação no disco. Isso significa, de maneira geral, 
; que não informamos o final do arquivo e o processador continou processando lixo de memória.