//--------------------------------------------------------------
// NOME: André Palacio Braga Tivo
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// ######### ESCREVA SEU NROUSP AQUI
const char *nroUSP()
{
    return ("13835534");
}

// no da arvore
typedef struct estr
{
    int chave;
    struct estr *esq;
    struct estr *dir;
} NO;

// no de lista ligada (caso queira usar alguma estrutura auxiliar)
typedef struct estrL
{
    int chave;
    struct estrL *prox;
} NOL;

// caso o compilador exija declarar a funcao aqui

NO *copiaCompleta(NO *raiz);
NO *copiaOriginalPraManipulavel(NO *raiz);
NO *arvorePraLista(NO *raiz);
NOL *insercao(NOL **p, int chaveIns);
NO *insercaoBinaria(NO *p, int chaveIns);
NO *criaNO(int chave);
NO *posElemento(NO *raiz, int posicao);
int tamanhoLista(NO *raiz);
void criaArvoreAlturaMinima(NO *listaDir, int comeco, int fim, NO **resp);
void arvoreSomenteDir(NO *raiz);
void ordenar(NO **listaUnida);
void printaPreOrdem(NO *raiz);

//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------

NO *copiaCompleta(NO *raiz)
{
    if (raiz)
    {
        // raiz = raizOriginal (NAO UTILIZAR);
        NO *novaArvore = (NO *)malloc(sizeof(NO));
        novaArvore = copiaOriginalPraManipulavel(raiz);
        NO *transformarEmLista = copiaOriginalPraManipulavel(novaArvore);

        NO *listaLigada = arvorePraLista(transformarEmLista); // a lista ligada é na verdade uma arvore que tem todos seus elementos à direita
        int tamanho = tamanhoLista(listaLigada);
        printf("TAMANHO\n%i\n", tamanho);
        int meio = (tamanho - 1) / 2;
        NO *aux = posElemento(listaLigada, meio);
        NO *resp = criaNO(aux->chave);
        criaArvoreAlturaMinima(listaLigada, 0, (tamanho - 1), &resp);
        printaPreOrdem(resp);
    }
}

void criaArvoreAlturaMinima(NO *listaDir, int comeco, int fim, NO **resp)
{
    if (listaDir)
    {
        if (comeco > fim)
            return;
        int meio = (comeco + fim) / 2;
        int aux = posElemento(listaDir, meio)->chave;
        NO *elementoMeio = criaNO(aux);
        insercaoBinaria(*resp, elementoMeio->chave);
        criaArvoreAlturaMinima(listaDir, meio + 1, fim, resp);
        criaArvoreAlturaMinima(listaDir, comeco, meio - 1, resp);
    }
}

void printaPreOrdem(NO *raiz)
{
    if (raiz)
    {
        printf("%i ", raiz->chave);
        printaPreOrdem(raiz->esq);
        printaPreOrdem(raiz->dir);
    }
}

NO *posElemento(NO *raiz, int posicao)
{
    if (raiz)
    {
        for (int i = 0; i < posicao; i++)
        {
            raiz = raiz->dir;
        }
        return raiz;
    }
    return raiz;
}

NO *copiaOriginalPraManipulavel(NO *raizOriginal)
{
    // atualizada 100% funcional
    // vital sempre utilizar uma funcao criaNo
    if (raizOriginal)
    {
        if (raizOriginal->dir == NULL && raizOriginal->esq == NULL)
        {
            NO *novo = (NO *)malloc(sizeof(NO));
            novo->chave = raizOriginal->chave;
            novo->dir, novo->esq = NULL;
            return novo;
        }
        NO *novo = criaNO(raizOriginal->chave);
        novo->esq = copiaOriginalPraManipulavel(raizOriginal->esq);
        novo->dir = copiaOriginalPraManipulavel(raizOriginal->dir);
        return novo;
    }
    return raizOriginal; // caso a lista for vazia retorna ela mesma (NULL)
}

NO *arvorePraLista(NO *raiz)
{
    if (!raiz)
        return NULL;
    if (raiz->esq == NULL && raiz->dir == NULL)
    {
        NO *resp = malloc(sizeof(NOL));
        resp->chave = raiz->chave;
        resp->esq = NULL;
        resp->esq = NULL;
        return resp;
    }
    NO *resp;
    arvoreSomenteDir(raiz);
    NO *contador = raiz;
    int condicional = 0;
    NO *imprime = raiz;
    printf("ARVORE COPIADA A DIREITA: ");
    while (imprime)
    {
        printf("%i ", imprime->chave);
        imprime = imprime->dir;
    }
    printf("\n");
    ordenar(&raiz);

    NO *imprimeOrd = raiz;
    printf("ARVORE ORDENADA: ");
    while (imprimeOrd)
    {
        printf("%i ", imprimeOrd->chave);
        imprimeOrd = imprimeOrd->dir;
    }
    printf("\n");
    return raiz;
}

void ordenar(NO **listaUnida)
{
    NO *a = *listaUnida;
    NO *b = *listaUnida;
    while (a)
    {
        b = a->dir;
        while (b)
        {
            if (b->chave < a->chave)
            {
                int aux = a->chave;
                a->chave = b->chave;
                b->chave = aux;
            }
            b = b->dir;
        }
        a = a->dir;
    }
}

NOL *insercao(NOL **p, int chaveIns)
{
    NOL *aux = *p;
    NOL *ins = (NOL *)(malloc(sizeof(NOL)));
    ins->chave = chaveIns;
    ins->prox = NULL;
    if (*p == NULL)
    {
        *p = ins;
    }
    else
    {
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = ins;
    }
    return aux;
}

NO *insercaoBinaria(NO *raiz, int chaveIns)
{
    if (raiz == NULL)
    {
        return criaNO(chaveIns);
    }
    if (chaveIns < raiz->chave)
        raiz->esq = insercaoBinaria(raiz->esq, chaveIns);
    else if (chaveIns > raiz->chave)
        raiz->dir = insercaoBinaria(raiz->dir, chaveIns);
    return raiz;
}

NO *criaNO(int chave)
{
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void arvoreSomenteDir(NO *raiz)
{
    if (raiz)
    {
        if (raiz->esq == NULL && raiz->dir == NULL)
            return;

        if (raiz->esq)
        {
            arvoreSomenteDir(raiz->esq);
            NO *auxDir = raiz->dir;
            raiz->dir = raiz->esq;
            raiz->esq = NULL;
            NO *contador = raiz->dir;

            while (contador->dir != NULL)
            {
                contador = contador->dir;
            }
            contador->dir = auxDir;
        }
        arvoreSomenteDir(raiz->dir);
    }
}

int tamanhoLista(NO *raiz)
{
    NO *contador = raiz;
    int tamanho = 0;
    while (contador)
    {
        tamanho++;
        contador = contador->dir;
    }
    return tamanho;
}
//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main()
{

    // FAZER FUNCAO DE INSERCAO PARA TESTAR !

    NO *raiz = criaNO(10);
    insercaoBinaria(raiz, 15);
    insercaoBinaria(raiz, 20);
    insercaoBinaria(raiz, 25);
    insercaoBinaria(raiz, 5);
    insercaoBinaria(raiz, 6);
    insercaoBinaria(raiz, 50);
    insercaoBinaria(raiz, 4);
    insercaoBinaria(raiz, 12);
    insercaoBinaria(raiz, 22);
    insercaoBinaria(raiz, 30);

    for (int i = 0; i < 2; i++)
    {

        NO* resp = copiaCompleta(raiz);
    }

    // acrescente aqui alguns nos para criar uma arvore de teste

    // serao realizadas chamadas como esta:
    // NO* resp = copiaCompleta(raiz);
}

// por favor nao inclua nenhum código abaixo da função main()