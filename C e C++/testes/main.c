#include <stdio.h>

void testeGiba(int amor, double pesos[], double antecessores[], int tamArray) {
  amor = 2;
  for (int i = 0; i < tamArray; i++) {
    pesos[i] = 0;
    antecessores[i] = -1;
  }
}

int main() {
  int tamArray = 10;
  double pesos[tamArray];
  double antecessores[tamArray];
  int amor = 100;

  for (int i = 0; i < tamArray; i++) {
    pesos[i] = i + 3;
    printf("peso antes: %f\n", pesos[i]);
    antecessores[i] = i + 4;
    printf("ant antes: %f\n", antecessores[i]);
  }
  printf("\n");

  testeGiba(amor, pesos, antecessores, tamArray);
  printf("amor: %d\n", amor);

  for (int i = 0; i < tamArray; i++) {
    printf("pesos: %f", pesos[i]);
  }
  printf("\n");
  for (int i = 0; i < tamArray; i++) {
    printf("ants: %f", antecessores[i]);
  }
}