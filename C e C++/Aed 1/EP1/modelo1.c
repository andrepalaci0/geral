#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>


// ######### ESCREVA O NROUSP AQUI
char* nroUSP() {
    return("13835534");
}


// ######### ESCREVA SEU NOME AQUI
char* nome() {
    return("Andre_Palacio_Braga_Tivo");
}

// elemento da lista
typedef struct estr {
        int valor;
        struct estr* prox;
} NO;



// funcao principal
NO* uniao(NO* p1, NO* p2);
NO* juntar(NO** p1, NO** p2);
NO* insercao(NO**  p, int chaveIns);
NO* copiarLista(NO* p);
void removerRep(NO** listaOrdenada);
void ordenar(NO** listaUnida);
void imprimir(NO* p);
//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO* uniao(NO* p1, NO* p2) {

	NO* resp = NULL;
	NO* auxp1 = copiarLista(p1);
	NO* auxp2 = copiarLista(p2);
	
	if(auxp1 == NULL && auxp2 == NULL)
	{
		return resp;
	}
	else if(auxp1 == NULL && auxp2 != NULL)
	{
		juntar(&auxp2, &auxp1);
		resp = auxp2;
	}
	else
	{
		juntar(&auxp1, &auxp2);
		resp = auxp1;	
	}
	ordenar(&resp);
	removerRep(&resp);
	return resp;
}

NO *copiarLista (NO *p) {
    NO *resp = NULL;
    NO *contador = p;
    NO *ant = NULL;
    while (contador) 
	{
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->valor = contador->valor;
        
        if (!resp)
		{
            resp = novo;
        }
		else
		{
            ant->prox = novo;
            novo->prox = NULL;    
        }
        ant = novo;
        contador = contador->prox;
    }
    
    return resp;
}

void removerRep(NO** listaOrdenada)
{
	NO* atual;
	NO* comparado = *listaOrdenada;
	NO* contador = *listaOrdenada;
	while (contador)
	{
		contador = contador->prox;
		if(atual == NULL)
		{
			atual = *listaOrdenada;
			comparado = comparado->prox;
			continue;
		}
		else
		{
			if(atual->valor == comparado->valor)
			{
				atual->prox = comparado->prox;
				free(comparado);
				comparado = contador;
			}
			else
			{
				atual = atual->prox;
				comparado = comparado->prox;
			}
		}
	}
}

NO* juntar(NO** p1, NO** p2) //a p1 nao pode ser nula, enquanto a p2 pode. Deve ser feita a condicional ANTES da funcao ser aplicada, para evitar erros
{
	NO* list1 = *p1;
	NO* lista2 = *p2;
	NO* ultimo;
	
	while(list1 != NULL)
	{
		ultimo = list1;
		list1 = list1->prox;
	}
	ultimo->prox = lista2;
	
	return *p1;
}


void imprimir(NO* p)
{
	while(p != NULL)
	{
		printf("%i " , p->valor);
		p = p->prox;
	}
	printf("\n");
}

NO* insercao(NO** p, int chaveIns)
{
	NO* aux = *p;
	NO* ins = (NO*)(malloc(sizeof(NO))); 
	ins->valor = chaveIns;
	ins->prox = NULL;
	if(*p == NULL)
	{	
		*p = ins;
	}else{
		while(aux->prox != NULL)
		{
			aux = aux->prox;
		}
		aux->prox = ins;
	}
	return aux;
}

void ordenar(NO** listaUnida)
{
	NO* a = *listaUnida;
	NO* b = *listaUnida;
	while(a)
	{
		b = a->prox;
		while (b)
		{	
			if(b->valor < a->valor)
			{
				int aux = a->valor;
				a->valor = b->valor;
				b->valor = aux; 
				
			}
			b = b->prox;
			
		}
		a = a->prox;
		}	
}


//----------------------------------------------------------------
// use main() apenas para fazer chamadas de teste ao seu programa
//----------------------------------------------------------------
int main() {

	
	NO* p1 = NULL;
	NO* p2 = NULL;
	

	// aqui vc pode incluir codigo para inserir elementos
// de teste nas listas p1 e p2

	// o EP sera testado com chamadas deste tipo
	NO* teste = NULL;
	int n = 0;
	insercao(&p1 ,1 );
	insercao(&p1 , 2);
	insercao(&p1 , 3);
	insercao(&p1 , 3);
	insercao(&p1 , 3);
	insercao(&p1 , 99);
	insercao(&p2 , 10);
	insercao(&p2 , 10);
	insercao(&p2 , 77);

	for (int i = 0; i < 5; i++)
	{
		printf("%d \n" , i);
		NO* pt = uniao(p1, p2);
		imprimir(pt);
	}

}

// por favor nao inclua nenhum código abaixo deste ponto