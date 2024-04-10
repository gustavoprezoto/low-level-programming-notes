# Questões do capítulo 2:

**Questão 11:**
O que faz a instrução `xor rdi, rdi`?
R: Faz uma operação XOR e armazena o valor no próprio rdi. matematicamente vc fazer um xor(X, X) vc recebe o retorno 0, pois são iguais. Portanto essa instrução está settando o primeiro parametro (rdi) da syscall exit com 0.

**Questão 12:**
Qual é o código de retorno do programa?
R: Nesse caso estamos settando como 0 por conta da operação `xor rdi, rdi`

**Questão 13:**
Qual o primeiro argumento da chamada de sistema `exit`?
O primeiro e único argumento da chamada `exit` é o código de erro que será retornado, no nosso caso é 0. 