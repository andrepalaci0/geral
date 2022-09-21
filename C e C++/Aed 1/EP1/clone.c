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

/*void ordenar(NO** listaUnida)
{
	NO* atual = *listaUnida;
	NO* comparado = atual->prox;
	NO* contadorFora = atual;
	NO* contadorDentro = contadorFora->prox;
	while(contadorFora->prox != NULL){
		while (contadorDentro->prox != NULL)
		{
			//printf("\nentrou no while\n");
			if(contadorFora->valor >= contadorDentro->valor){
				printf("entrou no if\n");
				NO* aux1 = comparado;
				NO* aux2 = atual;
				comparado->valor = aux2->valor;
				atual->valor = aux1->valor;
				aux1 = NULL;
				aux2 = NULL;
			}
			contadorDentro = contadorDentro->prox;
		}
		contadorFora = contadorFora->prox;
	}
}*/

void ordenar(NO** listaUnida)
{
	NO* a = *listaUnida;
	NO* b = a->prox;
	while(a != NULL)
	{
		while (b != NULL)
		{
			if(a->valor >= b->valor)
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

NO* juntar(NO** p1, NO** p2) //a p1 nao pode ser nula, enquanto a p2 pode. Deve ser feita a condicional ANTES da funcao ser aplicada, para evitar erros
{
	NO* list1 = *p1;
	NO* lista2 = *p2;
	NO* ultimo;
	printf("criou l1 e l1");
	while(list1 != NULL)
	{
		printf("Entrou no while do juntar");
		ultimo = list1;
		list1 = list1->prox;
	}
	ultimo->prox = lista2;
	return *p1;
}


/*NO* removeRepEntreList(NO** pontPrimList, NO** pontSegnList)
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
}*/

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
	
	imprimir(p1);
	imprimir(p2);
	NO* pt = juntar(&p1, &p2);
	printf("Lista unida porem nao organizada nem filtrada\n\n");
	imprimir(pt);
	ordenar(&pt);
	printf("\nOrdenada:\n");
	imprimir(pt);
	

}

// por favor nao inclua nenhum código abaixo deste ponto