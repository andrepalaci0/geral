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

void comparaERemov(NO** p1, NO** p2)
{
	NO* auxp1 = *p1;
	NO* auxp2 = *p2;
	NO* auxiliar1;
	NO* auxiliar2;
	while(auxp2->prox != NULL)
	{
		while(auxp1->prox != NULL)
		{
			if(auxp1->valor == auxp2->valor) //criar variavel auxiliar anterior
			{
				auxiliar2 = auxp2;
				auxp2->prox = auxp2->prox->prox;
				free(auxiliar2);
			}
			auxp1 = auxp1->prox;
		}
		auxp2 = auxp2->prox;
	}
}

NO* removeRepEntreList(NO** pontPrimList, NO** pontSegnList)
{
	NO* auxPrimList = *pontPrimList;
	NO* auxSegnList = *pontSegnList;
	NO* antPrim = (NO*)malloc(sizeof(NO));
	NO* antSegund = (NO*)malloc(sizeof(NO));
	while(true)
	{
		if(auxPrimList->prox ==  NULL && auxSegnList->prox == NULL) break; //finaliza a funcao quando o proximo das duas nao existir (ou seja, é o ultimo termo)

		
		if(antPrim->valor == NULL && antSegund->valor == NULL){
			if(auxPrimList->valor == auxSegnList->valor){

			}
		}
		
		if(auxPrimList->prox != NULL)
		{
			antPrim = auxPrimList;
			auxPrimList = auxPrimList->prox;
		}else{
			continue;
		}if(auxSegnList->prox != NULL)
		{
			antSegund = auxSegnList;
			auxSegnList = auxSegnList->prox;	
		}else{
			continue;
		}
		
	}

	free(antPrim);
	free(antSegund);
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

	for (int i = 0; i < 10; i++)
	{
		int l;
		scanf("%i" , &l );
		insercao(&p1, l);
		
	}
	imprimir(p1);

	
	teste = uniao(p1,p2);
}

// por favor nao inclua nenhum código abaixo deste ponto