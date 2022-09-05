#include <stdio.h>
#include <stdbool.h>

/* 

Não há a necessidade de que a ordem física dos elementos na memória seja a mesma da ordem lógica

São necessárias ligações que levem de um elemento ao próximo e a passagem do índice do elemento que será o primeiro a ser consultado

Como lidar com as posições vazias -> Ter uma lista "fantasma" que guarda as posições disponíveis (alocação estática de memória)

ex: início -> 10 -> 20 -> 30 -> 40 -> 50 -> saída... (cada -> é uma indicação leva ao próximo elemento)

*/


// estrutura de um registro de lista ligada

const int max = 100;

typedef struct {
    int chave;
    int proximo; 
} REGISTRO;

//estrutura de uma lista ligada

typedef struct {
    int inicio;
    int disponivel; //indicador de inicio da lista de disponíveis
    REGISTRO A[100]; //max é arbitrário
} LISTA_LIG_EST; // = lista ligada estaticamente

void inicializar(LISTA_LIG_EST * l) {

    l -> inicio = -1; //indice inválido -> indica lista vazia
    l -> disponivel = 0; 
    //qualquer valor seria válido, já que todos as casas da lista estão disponíveis 
    int i;
    for(i = 0; i < max - 1; i++) { //indexa todos os registros com o índice do próximo registro
        l -> A[i].proximo = i + 1;
    }
    l -> A[max - 1].proximo = -1; // a última posição indica que acabou

}

void exibir(LISTA_LIG_EST * l) { //exibe todas as chaves que existem

    int i = l -> inicio;
    while(i != -1) { // se a lista for vazia, inicio já vale -1
        printf("%i\n", l -> A[i].chave);
        i = l -> A[i].proximo; //passa para o próximo elemento indexado àquela chave analizada
    }
}


int busca(LISTA_LIG_EST * l, int ch, int * anterior) { 
    //anterior será o endereço da memória que poderá ser acessado na main -> passado por referência
    //Será necessário para inserção
    *anterior = -1; //não há elemento anterior ao inicial
    int i = l -> inicio;
    while(i != -1) {
        if( l -> A[i].chave >= ch) break;
        *anterior = i;
        i = l -> A[i].proximo;
    }
    if(l -> A[i].chave == ch) return(i);
    return(-1); //não achou a chave
}

int ultimo(LISTA_LIG_EST * l) {
    int i = l -> inicio;
    while(i != -1) {
        if(l -> A[i].proximo == -1) return(i);
        else i = l -> A[i].proximo;
    }
    return(-1);
}

void devolverNo(LISTA_LIG_EST * l, int i) { 
    l -> A[i].proximo = l -> disponivel;
    l -> disponivel = i;
}

bool excluir(LISTA_LIG_EST * l, int ch) { 
    //exclusão da elemento e devolução daquela posição para lista de disponíveis
    int ant;
    int atual = busca(l, ch, &ant); //encontra a posição da chave atual na lista l
    if(atual == -1) return(false); //elemento não encontrado
    if(ant != -1) { //se tem elemento anterior ao atual
        l -> A[ant].proximo = l -> A[atual].proximo; 
        //proximo do anterior passa a ser o proximo do atual
        //A ideia é linkar o elemento anterior ao seguinte do elemento que será excluido
    } else { //é o primeiro elemento
        l -> inicio = l -> A[atual].proximo; //o inicio passa a ser o proximo valor
    }
    devolverNo(l, atual);
    return(true);
}

int obterNo(LISTA_LIG_EST * l) { //pega o nó disponível e retira sua disponibilidade
    if(l -> disponivel == -1) return(-1);
    int resposta = l -> disponivel;
    l -> disponivel = l -> A[l -> disponivel].proximo;
    return(resposta);
}

bool inserir(LISTA_LIG_EST * l, int ch) { //inserindo um novo elemento na lista ligada
    int ant;
    int atual = busca(l, ch, &ant); 
    //confere se a chave já está na lista e devolve o local que será inserido
    if(atual != -1) return(false); //Já existe
    atual = obterNo(l);
    if(atual == -1) return(false); //caso de vetor cheio
    l -> A[atual].chave = ch; //pegou o endereço disponível
    if(ant != -1) { //está no meio da lista ou no final
        l -> A[atual].proximo = l -> A[ant].proximo;
        l -> A[ant].proximo = atual;
    } else { //está no começo da lista
        l -> A[atual].proximo = l -> inicio;
        l -> inicio = atual;
    }
    return(true);
}

bool listasIguais(LISTA_LIG_EST * l1, LISTA_LIG_EST * l2 ) {
    int i = l1 -> inicio;
    int j = l2 -> inicio;
    while( i != -1 && j != -1) {
        if(l1 -> A[i].chave != l2 -> A[j].chave) return(false); //elementos diferentes
        i = l1 -> A[i].proximo;
        j = l2 -> A[j].proximo;
    }
    if( i == -1 && j == -1) return(true); //tem os mesmos elementos e mesmo tamanho
    return(false); //tamanhos diferentes

}

int main() {

    LISTA_LIG_EST l;

    inicializar(&l);
    inserir(&l , 14);
    inserir(&l, 64);

    exibir(&l);

}