#include <stdio.h>

//codigo profissional deve ser bem identado
//com bom espacamento, boa nomenclatura de variaveis e funcoes e comentarios
//um codigo eh como um texto, deve ser possivel uma pessoa 'leiga' no assunto (nao sabia como o codigo funcionava) entende-lo 

int main()
{            
    printf("Teste gcc");
    return 0;
}

typedef struct 
{
    int idade;
    float salario;    
}tipoAluno;


void aniversario(tipoAluno* x)
{
    x->idade++;
}
