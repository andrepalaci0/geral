testa_matriz: grafo_direcionado_matrizadj.o testa_grafo.o
	gcc -o testa_grafo_matriz.exe grafo_direcionado_matrizadj.o testa_grafo.o

grafo_direcionado_matrizadj.o: grafo_direcionado_matrizadj.c grafo_direcionado_matrizadj.h
	gcc -c grafo_direcionado_matrizadj.c

testa_grafo.o: testa_grafo.c grafo_direcionado_matrizadj.h
	gcc -c testa_grafo.c

clean:
		rm -f *.o
