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
NO* copiarLista(NO* resp);
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
        } else
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
	

	
//teste 4
	// insercao(&p1 , 1 );  insercao(&p1 , 1 ); insercao(&p1 , 1 ); insercao(&p1 , 3 ); insercao(&p1 , 5 ); insercao(&p1 , 9 ); insercao(&p1 , 10 );
	//  insercao(&p1 , 15 ); insercao(&p1 , 15 ); insercao(&p1 , 16 ); 
	// insercao(&p2 , 1); insercao(&p2 , 2); insercao(&p2 , 3); insercao(&p2 , 3); insercao(&p2 , 4); insercao(&p2 , 4); insercao(&p2 , 5);
	//  insercao(&p2 , 13); insercao(&p2 , 15); insercao(&p2 , 16); insercao(&p2 , 17); insercao(&p2 , 18);
	
//L1 1 1 1 3 5 9 10 15 15 16
//L2 1 2 3 3 4 4 5 13 15 16 17 18

//-----------------------------------------------------------

//TESTE 6

//L1 10 12 12 22 56
//L2 5 6 6 7 7 8
//Ex 5 6 7 8 10 12 22 56

//insercao(&p1 , 10 ); insercao(&p1 , 12 ); insercao(&p1 , 12 ); insercao(&p1 ,22 ); insercao(&p1 , 56 );
//insercao(&p2 , 5); insercao(&p2 , 6); insercao(&p2 , 6); insercao(&p2 , 7); insercao(&p2 , 7); insercao(&p2 , 8);

//TESTE7

//insercao(&p1 , 1 ); insercao(&p1 , 4 ); insercao(&p1 , 4 ); insercao(&p1 , 4 ); insercao(&p1 , 8 ); insercao(&p1 , 8 );
//insercao(&p2 , 2); insercao(&p2 , 5); insercao(&p2 , 5); insercao(&p2 , 5); insercao(&p2 , 10); insercao(&p2 , 10);

//L1 1 4 4 4 8 8
//L2 2 5 5 5 10 10
//Ex 1 2 4 5 8 10


//TESTE 8

// insercao(&p1 , 2 ); insercao(&p1 , 2 ); insercao(&p1 , 2 ); insercao(&p1 , 2 ); insercao(&p1 , 2 ); insercao(&p1 , 2 );
// insercao(&p2 , 2);insercao(&p2 , 2);insercao(&p2 , 2);

//L1 2 2 2 2 2 2
//L2 2 2 2
//Ex 2

//teste 10
/* insercao(&p1 , 4 ); insercao(&p1 , 4 ); insercao(&p1 , 12 ); insercao(&p1 , 30 ); 
 insercao(&p1 , 30 ); insercao(&p1 , 30 ); insercao(&p1 , 100 ); insercao(&p1 , 150 ); 
 insercao(&p1 , 3000 ); insercao(&p1 , 3000 );

 insercao(&p2 , 11); insercao(&p2 , 11); insercao(&p2 , 50); insercao(&p2 , 98); insercao(&p2 , 101);
  insercao(&p2 , 145); insercao(&p2 , 153); insercao(&p2 , 153); insercao(&p2 , 1000);
*/
//L1 4 4 12 30 30 30 100 150 3000 3000
//L2 11 11 50 98 101 145 153 153 1000
//Ex 4 11 12 30 50 98 100 101 145 150 153 1000 3000 
//-----------------------------------------------------------


	for (int i = 0; i < 5; i++)
	{
		printf("%d \n" , i);
		NO* pt = uniao(p1, p2);
		imprimir(pt);
	}

}

// por favor nao inclua nenhum código abaixo deste ponto