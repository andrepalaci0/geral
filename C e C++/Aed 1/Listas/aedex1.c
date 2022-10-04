#include <stdio.h>
#include <stdbool.h>

//funcional

int main()
{
    int tamArr = 9;
    int arr[tamArr];
    printf("Insira 9 variaveis para gerar a lista\n");

    for (int i = 0; i < tamArr; i++)
    {
        scanf("%d" , &arr[i]);
    }

    bool Cresc = true;
    bool Decresc = true;
    int igual = 1;

    for (int j = 0; j < tamArr-1; j++)
    {   
        if( arr[j] < arr[j+1]) Decresc = false;
        if( arr[j] > arr[j+1]) Cresc = false;
        if( arr[j] == arr[j+1]) igual++;
    }

    if(Decresc == false && Cresc == true) printf("E uma lista crescente\n");
    if(Decresc == true && Cresc == false) printf("E uma lista decrescente\n");
    if((Decresc == false || Cresc == false) && igual < tamArr) printf("E uma lista sem ordem de crescimento\n");
    if(Decresc == true && Cresc == true && igual == tamArr) printf("Todos os numeros da lista sao iguais\n");
    
    return 0;
}