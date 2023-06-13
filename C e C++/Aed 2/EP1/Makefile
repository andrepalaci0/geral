ep1_lista_13835534.exe: grafo_listaadj.o ep1.o
	gcc -o ep1_lista_13835534.exe grafo_listaadj.o ep1.o

ep1_matriz_13835534.exe: grafo_matrizadj.o ep1.o
	gcc -o ep1_matriz_13835534.exe grafo_matrizadj.o ep1.o

grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc -c grafo_listaadj.c

grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc -c grafo_matrizadj.c

ep1.o: ep1.c grafo_listaadj.h grafo_matrizadj.h
	gcc -c ep1.c

clean:
		rm -f *.o *exe