//--------------------------------------------------------------
// NOME: escreva aqui o seu nome
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// ######### ESCREVA SEU NROUSP AQUI
const char *nroUSP()
{
	return ("0000000");
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

//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------
NO *copiaCompleta(NO *raiz)
{

	// seu codigo AQUI
}

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main()
{

	NO *raiz = NULL;

	// acrescente aqui alguns nos para criar uma arvore de teste

	// serao realizadas chamadas como esta:
	// NO* resp = copiaCompleta(raiz);
}

// por favor nao inclua nenhum código abaixo da função main()