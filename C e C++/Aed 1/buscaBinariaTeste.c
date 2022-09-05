#include <stdio.h>
#include <stdbool.h>

#define VALORINVALIDO = -1;

void populaArrOrdenado(int *arr, int tamArr);
int buscaBinaria(int *arr, int tamArr, int busca);

int main()
{
    int arr[100];
    int tamArr = 100;
    populaArrOrdenado(arr, tamArr);
    printf("Insira o numero entre 0 a 99 que deseja buscar\n");
    int busca;
    scanf("%d", &busca);
    printf("O numero esta no indice: %d\n", 
    buscaBinaria(arr, tamArr, busca)); //colocar ponteiro 
    return 0; 
    
}

int buscaBinaria(int *arr, int tamArr, int busca)
{
    int comeco, fim
    , meio;
    fim = tamArr - 1;
    comeco = 0;
    meio = (fim + comeco)/2;
    while(arr[meio] != busca)
    {
        meio = (fim + comeco)/2;
        if(meio == fim || meio == comeco) return -1;
        else if(busca < arr[meio])
        {
            fim = meio;
        }
        else if(busca > arr[meio]) 
        {
            comeco = meio;
        }
    }
    printf("t3");
    if(arr[meio] == busca)
    {
        busca = meio;
        return busca;
    }
    else return -1;

}


void populaArrOrdenado(int *arr, int tamArr)
{
    for (int i = 0; i < tamArr; i++)
    {
        arr[i] = i;
    }
}
