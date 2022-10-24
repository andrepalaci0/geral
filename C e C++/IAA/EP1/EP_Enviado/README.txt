Andre Palacio Braga Tivo
NUSP 13835534

Compilar programa:

gcc ep1_13835534.c -o ep1_13835534 -lm

o '-lm' é para forçar o funcionamento das bibliotecas envolvidas no programa, no caso a biblioteca math.h. Tive alguns problemas com ela e sem o '-lm' ela nao funcionamento

Rodar o programa:

./ep1_13835534 'tamanhoMatriz' ./entrada.txt

onde 'tamanhoMatriz' é um inteiro que pode ser escrito como 2^n e menor que 1024