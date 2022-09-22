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
NO* removeRepEntreList(NO** p1, NO** p2);
void imprimir(NO* p);
//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO* uniao(NO* p1, NO* p2) {

	NO* resp = NULL;



	return resp;
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
		printf("SAIU DO WHILE B");
		a = a->prox;
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

	for (int i = 0; i < 5; i++)
	{
		int l;
		scanf("%i" , &l );
		insercao(&p1, l);
		
	}
	imprimir(p1);

	for (int j = 0; j < 5; j++)
	{
		int h;
		scanf("%i" , &h );
		insercao(&p2, h);
		
	}
	
	//imprimir(p1);
	//imprimir(p2);
	NO* pt = juntar(&p1, &p2);
	printf("Lista unida porem nao organizada nem filtrada\n\n");
	//imprimir(pt);
	ordenar(&pt);
	printf("\nOrdenada:\n");
	imprimir(pt);
	

}

// por favor nao inclua nenhum código abaixo deste ponto