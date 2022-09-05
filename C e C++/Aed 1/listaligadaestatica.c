#include <stdio.h>
#include <stdbool.h>

// LEMBRETE: NOMES DE STRUCTS DEVEM SER MAIUSCULOS POR CONVENCAO
// a slista ligada permite uma alteracao consideravelmente mais rapida dos seus registros

typedef struct
{
    int chave;
    int proximoNum;
} REGISTRO;

typedef struct
{
    int inicio;
    int disponivel;
    REGISTRO A[100]; // numero arbitrario de posicoes do vetor;
} LISTA_LIGADA_ESTATICA;

bool listasIguais(LISTA_LIGADA_ESTATICA *l1, LISTA_LIGADA_ESTATICA *l2);
bool inserir(LISTA_LIGADA_ESTATICA *l1, int chaveInsert);
bool excluir(LISTA_LIGADA_ESTATICA *l1, int chaveRemover);
int ultimo(LISTA_LIGADA_ESTATICA *l1);
int busca(LISTA_LIGADA_ESTATICA *l1, int chaveBusc, int *anterior);
int obterNo(LISTA_LIGADA_ESTATICA *l1);
void inicializar(LISTA_LIGADA_ESTATICA *l1);
void exibir(LISTA_LIGADA_ESTATICA *l1);
void devolverNo(LISTA_LIGADA_ESTATICA *l1, int num);

int main()
{
    LISTA_LIGADA_ESTATICA l1;
    inicializar(&l1);
    inserir(&l1, 14);
    inserir(&l1, 64);
    exibir(&l1);
    return 0;
}

int busca(LISTA_LIGADA_ESTATICA *l1, int chaveBusc, int *anterior) // retorna o indice da chave buscada, caso nao exista retorna -1
{                                                                  // a variavel anterior, que tambem retorna algo por ser um ponteiro, indica a chave anterior a que estava sendo buscada
    *anterior = -1;
    int i = l1->inicio;
    while (i != -1)
    {
        if (l1->A[i].chave >= chaveBusc)
            break;
        *anterior = i;
        i = l1->A[i].proximoNum;
    }
    if (i == -1)
        return -1;
    if (l1->A[i].chave == chaveBusc)
        return i;
    else
        return -1;
}

bool inserir(LISTA_LIGADA_ESTATICA *l1, int chaveInsert)
{
    int anterior;
    int atual = busca(l1, chaveInsert, &anterior); // o atual deve ser menos um pois nao deve existir
    if (atual != -1)
    {
        return false;
    } // a chave ja existe na lista
    atual = obterNo(l1);
    if (atual == -1)
    {
        return false;
    } // seria o caso vetor estar cheio;
    l1->A[atual].chave = chaveInsert;
    if (anterior != -1) // caso em que há uma anterior e um proximo
    {
        l1->A[atual].proximoNum = l1->A[anterior].proximoNum;
        l1->A[anterior].proximoNum = atual;
    }
    else
    { // caso onde nao ha um anterior ou a lista esta vazia
        l1->A[atual].proximoNum = l1->inicio;
        l1->inicio = atual;
    }
    return true;
}

bool listasIguais(LISTA_LIGADA_ESTATICA *l1, LISTA_LIGADA_ESTATICA *l2)
{
    int i = l1->inicio;
    int j = l2->inicio;
    while (i != -1 && j != -1)
    {
        if (l1->A[i].chave != l2->A[j].chave)
            return false;
        i = l1->A[i].proximoNum;
        j = l1->A[j].proximoNum;
    }
    if (i == j)
        return true;
    else
        return false; // iguais em sequencia porem com tamanhos diferentes
}

bool excluir(LISTA_LIGADA_ESTATICA *l1, int chaveRemover)
{
    int anterior;
    int atual = busca(l1, chaveRemover, &anterior); // a funcao ja garante que a chave existe e portanto a lista nao esta vazia
    if (atual == -1)
        return false;
    if (anterior != -1) // caso de exclusao no meio da lista
    {
        l1->A[anterior].proximoNum = l1->A[atual].proximoNum;
    }
    else
    { // caso em que o elemento a ser removido e o primeiro da lista
        l1->inicio = l1->A[atual].proximoNum;
    }
    devolverNo(l1, atual);
    return true;
}

void inicializar(LISTA_LIGADA_ESTATICA *l1) // cria uma lista vazia
{
    l1->inicio = -1;    // lista vazia
    l1->disponivel = 0; // escolhida arbitrariamente como inicio (por convencao) pois o vetor esta vazio
    for (int i = 0; i < 100 - 1 /*max-1 ja que o valor é arbitrario*/; i++)
    {
        l1->A[i].proximoNum = i + 1;
    }
    l1->A[100 - 1].proximoNum = -1;
}

void exibir(LISTA_LIGADA_ESTATICA *l1) // mostra as chaves da lista de maneira ordenada
{                                      // se a lista estiver vazia, nao mostra nada
    int i = l1->inicio;
    while (i != -1)
    {
        printf("%i\n", l1->A[i].chave);
        i = l1->A[i].proximoNum;
    }
}

void devolverNo(LISTA_LIGADA_ESTATICA *l1, int num) // so deve ser chamada pela funcao de exclusao
{
    l1->A[num].proximoNum = l1->disponivel;
    l1->disponivel = num;
}

int obterNo(LISTA_LIGADA_ESTATICA *l1)
{
    if (l1->disponivel == -1)
    {
        return -1;
    }
    int indiceDevolvido = l1->disponivel;
    l1->disponivel = l1->A[l1->disponivel].proximoNum;
    return indiceDevolvido;
}

int ultimo(LISTA_LIGADA_ESTATICA *l1) // retorna somente o indice do ultimo numero
{
    int i = l1->inicio;
    while (i > -1)
    {
        if (l1->A[i].proximoNum == -1)
            return (i);
        i = l1->A[i].proximoNum;
    }
    return -1;
}