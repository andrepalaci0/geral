#include <stdio.h>


typedef struct NOME_MUITO_LONGO_PARA_SER_USADO_PARA_DECLARAR_EM_VARIAVEL_SO_PRA_DAR_EXEMPLO_KKKKKKKKKKKKKKKKK_QUE_BOSTA {
    int x;
    int y;
} ponto;

int main()
{
    ponto ponto1, ponto2; //o typedef cria uma nova variavel chamada ponto, que referencia o struct de nome mt longo
    ponto1.x = 1;
    ponto1.y = 2;
    ponto2.x = 4;
    ponto2.y = 7;

    ponto arr[2]; 
    arr[0] = ponto1;
    arr[1] = ponto2;

    for (int i = 0; i < 2; i++)
    {
        printf("Ponto %d X=%d Y=%d\n", i+1, arr[i].x, arr[i].y );
    }
    
    return 0;
}

    
