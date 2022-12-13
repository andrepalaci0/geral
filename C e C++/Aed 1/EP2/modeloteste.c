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
NOL *arvorePraLista(NO *raiz);
NOL *insercao(NOL **p, int chaveIns);
NO *insercaoBinaria(NO *p, int chaveIns);
NO *criaNO(int chave);
void arvoreSomenteDir(NO *raiz);

//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------

NO *copiaCompleta(NO *raiz)
{
    // raiz = raizOriginal (NAO UTILIZAR);
    NO *novaArvore = (NO *)malloc(sizeof(NO));
    novaArvore = copiaOriginalPraManipulavel(raiz);
    NO *transformarEmLista = copiaOriginalPraManipulavel(novaArvore);

    NOL *listaLigada = (NOL *)malloc(sizeof(NOL));

    listaLigada = arvorePraLista(transformarEmLista);
}

NO *copiaOriginalPraManipulavel(NO *raizOriginal)
{
    // Arrumar erro segmentation fault
    // Motivo???
    // Problema na relacao com a raizManipulavel e o nodulo novo
    // Repensar lógica ?
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

NOL *arvorePraLista(NO *raiz)
{
    if (!raiz)
        return NULL;
    if (raiz->esq == NULL && raiz->dir == NULL)
    {
        NOL *resp = malloc(sizeof(NOL));
        resp->chave = raiz->chave;
        return resp;
    }
    NOL *resp = malloc(sizeof(NOL));
    // arvoreSomenteDir(raiz);
    NO *contador = raiz;
    int condicional = 0;
    NO *imprime = raiz;
    printf("ARVORE COPIADA: ");
    while (imprime)
    {
        printf("%i ", imprime->chave);
        imprime = imprime->dir;
    }
    printf("\n");

    /*while (contador != NULL)
    {
        if (condicional == 0)
        {
            printf("cond1");
            condicional = 1;
            resp->chave = contador->chave;
            resp->prox = NULL;
            contador = contador->dir;
        }
        printf("fora if");
        contador = contador->dir;
        insercao(&resp, contador->chave);
    }
    printf("fora while");
    NOL *aux = resp;
    while (aux != NULL)
    {
        printf("%i", aux->chave);
        aux = aux->prox;
    } */
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
            printf("giba");
            while (contador->dir != NULL)
            {
                contador = contador->dir;
            }
            contador->dir = auxDir;
        }
        arvoreSomenteDir(raiz->dir);
    }
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
    insercaoBinaria(raiz, 30);
    printf("%i\n", raiz->chave);
    printf("%i\n", raiz->esq->chave);
    printf("%i\n", raiz->dir->chave);
    printf("\n");

    copiaCompleta(raiz);

    // acrescente aqui alguns nos para criar uma arvore de teste

    // serao realizadas chamadas como esta:
    // NO* resp = copiaCompleta(raiz);
}

// por favor nao inclua nenhum código abaixo da função main()