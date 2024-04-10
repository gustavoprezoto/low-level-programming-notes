# Capítulo 2: Linguagem Assembly

Obs.: Neste capítulo utilizamos syscalls (system calls) do Unix, fazendo com que seja necessário executar os códigos em um ambiente linux. Minha sugestão é Debian ou Ubuntu.

Necessário para esse capítulo:
- NASM 2.11.05 (Assembler) ou superior;
- GCC 4.9.2 (Compilar para linguagem C) ou superior;
- GNU Make 4.0 (Sistema de construção) ou superior;
- GDB 7.7.1 (Debugger) ou superior.

Para melhor visualização dos códigos, organizei em pastas de acordo com as listagens do livro, porém não estão compilados.

## Como compilar o código:
Os detalhes mais detalhados sobre compilação serão vistos no capítulo 5. Nesse primeiro momento apenas vamos considerar o seguinte:
```
> nasm -felf64 <nome_do_arquivo>.asm -o <nome_do_arquivo>.o
> ld -o <nome_do_arquivo> <nome_do_arquivo>.o
> chmod u+x <nome_do_arquivo>
```

Também é possível utilizar um mini shell script criado para esse capítulo que executa esse processo mais rapidamente. Utilização:
`./compile.sh <nome_do_arquivo>`
o nome do arquivo deve ser passado sem extensão.

P.s.: o nome do arquivo deve ser passado sem extensão.

