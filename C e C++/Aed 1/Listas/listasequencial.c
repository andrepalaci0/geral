#include <stdio.h>
#include <stdbool.h>

//CORRECAO: NOMES DE STRUCTS DEVEM SER MAIUSCULOS
//sempre testar as condicoes de erro de uma funcao no seu comeco
//numero arbitrario max = 100 neste exercicio
//toda lista de elementos deve ser considerada ordenada para que haja diferenca no uso de poder computacional de cada estrutura de dados
//LISTA SEQUENCIAL: ORDEM LOGICA = ORDEM FISICA
//uma lista sequencial tem a vantagem de todos os elementos serem conhecidos pelos seu indices, porem, na maioria dos casos o indice do elemento procurado eh desconhecidp
//oque torna essa vantagem relativa 


typedef struct {
    int chave; //propria de cada registro especifico
    //outras variaveis
    //cada registro é UM index no vetor da lista Sequencial
} registro;

typedef struct //cria a lista que é composta por um vetor  de registro e uma variavel que é seu numero de elementos 
{
    int numElement;
    registro A[100]; //valor arbitrario no vetor
} listaSeq;

//header das funcoes para evitar problemas de declaracao implicita


int tamanho (listaSeq* l1);
int buscaSeq(listaSeq* l1, int chaveProcurada);
int buscaBinaria(listaSeq* l1, int chaveEncontrar);
bool anexar(listaSeq* l1, int novaChave);
bool excluir(listaSeq* l1, int chaveDeletar);
void exibir(listaSeq* l1);
void inicializar(listaSeq* l1);

int main()
{
    listaSeq l1; //declara uma lista de registro
    inicializar(&l1); //cria a lista
    anexar(&l1, 10); //adiciona registro com uma chave especifica a lista
    anexar(&l1, 356);
    anexar(&l1, 35);
    exibir(&l1); //exibe a lista 
    return 0;
}

bool anexar(listaSeq* l1, int novaChave) //coloca elementos na proxima posicao livre (no caso coloca somentea as chaves)
{
    if(l1 -> numElement == 100 /*numero que seria o max, que é o tamannho do vetor*/ ) return false;
    l1 -> A[l1 ->numElement].chave = novaChave;
    l1 -> numElement++;
    return true;    
}

int buscaBinaria(listaSeq* l1, int chaveEncontrar) //ESTUDAR BUSCA BINARIA
{                                                   //a busca binaria e um dos meios mais faceis e rapidos de se encontrar um objeto em uma lista (ordenada)
    int inferior = 0;                               //a busca binaria gasta o tempo em uma escala logaritmica (logN)
    int superior = l1 -> numElement-1;
    while(inferior <= superior)
    {
        int meio = (superior + inferior)/2;
        if(l1 -> A[meio].chave == chaveEncontrar ) return meio;
        else{
            if (l1 -> A[meio].chave < chaveEncontrar) inferior = meio + 1;
            else superior = meio -1;
        }
    }
}

bool excluir(listaSeq* l1, int chaveDeletar) //exclui um registro da lista
{
    int posi = buscaSeq(l1 , chaveDeletar); //chama a busca sequencial para confirmar que ela existe e obter sua posicao (busca a chave)
    if(posi == -1) return false; //se nao esta na lista, retorna falso e encerra a funcao
    for (int i = posi; i < l1 -> numElement-1; i++)
    {
        l1 -> A[i].chave = l1 -> A[i+1].chave; //se a chave esta na lista, arruma a lista substituindo a posicao atual pela proxima
    }
    l1 -> numElement--; //reduz o numero de elemtnos da lista
    return true;
}

int tamanho (listaSeq* l1) //mostra o tamanho atual dela (quantidade de elementos)
{
    return l1 -> numElement;
}

int buscaSeq(listaSeq* l1, int chaveProcurada) //ira, por convencao, retorna o indice ou o numero -1 caso ocorra um erro
{
    for (int i = 0; i < l1 -> numElement; i++)
    {
        if(l1 -> A[i].chave == chaveProcurada) return i;
    }
    printf("Chave nao encontrada");
    return -1;
}

void exibir(listaSeq* l1) //exibe os registros e suas respectivas chaves
{
    for (int i = 0; i < l1 -> numElement; i++)
    {
        printf("Registro %d Chave %d\n" , i+1, l1 -> A[i].chave);
    }   
}

void inicializar(listaSeq* l1) //cria uma lista de registro vazia, definindo seu numero de elementos para zero
{
    l1->numElement = 0;
}



