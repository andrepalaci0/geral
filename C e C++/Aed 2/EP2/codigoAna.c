// importando pacotes

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>

// definindo grau minimo, maximo de filhos, maximo de chaves e tipo da chave

#define t 3
#define MAX_FILHOS 2 * t
#define MAX_CHAVES 2 * t - 1
#define TIPO_CHAVE int

// criando estrutura do arvore b mais

typedef struct str
{
  TIPO_CHAVE* chaves; // vetor que guarda as chaves de um no
  struct str** filhos; // vetor que guarda os filhos de um no
  bool folha; // booleano que informa se e no folha ou nao (true folha, false interno)
  int numChaves; // quantidade de chaves que tem no no
  struct str* prox; // no prox

} NO;

// definindo funcoeS

NO* criaNo(); 
NO* criaArvore();
NO* buscaNo(NO* p, TIPO_CHAVE ch);
NO* divideNo(NO* noComEspaco, int ind, NO* noSemEspaco); 
NO* divideFilho(NO* pai, int ind) ; 
NO* insereNoComEspaco(NO* p, TIPO_CHAVE ch); 

void imprimeArvore(NO* p, int ind);
void liberaArvore(NO* p);
void removeFolha(NO* p, int ind);
void redistribuiIrmaoDir(NO* p, int ind);
void redistribuiIrmaoEsq(NO* p, int ind);
void fundeNos(NO* p, int ind);
void removeNo(NO* p, TIPO_CHAVE ch);
void removeInterno(NO* p, int ind);
void removeNoDaArvore(NO* p, TIPO_CHAVE ch);

bool insereNo(NO** raiz, TIPO_CHAVE ch);

int indFilho(NO* p, int ind);

TIPO_CHAVE chaveIrmaoDir(NO* node, int ind);
TIPO_CHAVE chaveIrmaoEsq(NO* node, int ind);

// implementando funcoes

NO* criaNo() 
{
  NO* novo = (NO*) malloc(sizeof(NO)); // alocando memoria para o no
  
  if(novo == NULL) // nao foi possivel alocar memoria
  {
    fprintf(stderr, "Erro ao alocar memoria para o novo no\n");
    return (NULL);
  }

  novo->filhos = (NO**) malloc(sizeof(NO *) * MAX_FILHOS); // alocando espaco para o vetor de filhos
  novo->chaves = (int*) malloc(sizeof(int) * MAX_CHAVES); // alocando espaco para o vetor de chaves
  
  if((!novo->chaves) || (!novo->filhos)) 
  {
    free(novo->chaves);
    free(novo->filhos);
    free(novo);
    return (NULL);
  }

  novo->prox = NULL; // setando prox
  novo->numChaves = 0; // setando qtd de ch
  novo->folha = true; // informando que e folha

  for(int i = 0; i < MAX_FILHOS; i++) novo->filhos[i] = NULL; // setando filhos
  
  return (novo); // retornando no novo
  
}

NO* criaArvore() 
{ 
  return criaNo(); 
  
}

NO* buscaNo(NO* p, TIPO_CHAVE ch) 
{
  if (!p) return (NULL); // o no e vazio, nao tem como procurar
  
  int i = 0; // indice da suposta chave sucessora de ch no vetor
  while ((i <= p->numChaves) && (ch > p->chaves[i])) i++; // procurando esse indice
  
  if ((i <= p->numChaves) && (p->folha) && (ch == p->chaves[i])) return (p); // achou no, retornando ele
  if (p->folha) return (NULL); // nao acho no e ja chegou na folha, retornando NULL

  if (p->chaves[i] == ch) i++;
  return (buscaNo(p->filhos[i], ch)); // nao achou mas ainda nao chegou na folha, continua procurando
  
}

NO* divideNo(NO* noComEspaco, int ind, NO* noSemEspaco) 
{
  NO* novo = criaNo(); // criando um no para fazer a divisao
  
  if(!novo) return (NULL); // deu erro na criacao, retorna NULL
  
  novo->folha = noSemEspaco->folha; // definindo se e folha ou nao com base no no cheio

  int pivo = t - 1; // passando 'metade' das folhas para o novo no na divisao (nao e bem a metade)

  if(!noSemEspaco->folha) // se o no sem espaco nao e folha
  {
    novo->numChaves = pivo; // setando numero de chaves

    for(int i = 0; i < pivo; i++) novo->chaves[i] = noSemEspaco->chaves[i + t]; // transferindo as chaves
    
    for(int i = 0; i < t; i++) // setando os filhos
    {
      novo->filhos[i] = noSemEspaco->filhos[i + t]; 
      noSemEspaco->filhos[i + t] = NULL; 
    }
    
  } else { // se o no sem espaco e folha
    
    novo->numChaves = t; // setando o numero de chaves

    for(int i = 0; i < t; i++) novo->chaves[i] = noSemEspaco->chaves[i + pivo]; // transferindo as chaves
    
    noSemEspaco->prox = novo; // setando o prox
    
  }

  noSemEspaco->numChaves = pivo; // setando o numero de chaves

  for(int i = noComEspaco->numChaves; i > ind - 1; i--) // arrumando os filhos 
  {
    noComEspaco->filhos[i + 1] = noComEspaco->filhos[i]; 
  }

  noComEspaco->filhos[ind] = novo;
  
  for(int i = noComEspaco->numChaves; i > ind - 1; i--) // arrumando as chaves 
  {
    noComEspaco->chaves[i] = noComEspaco->chaves[i - 1];
  }

  noComEspaco->chaves[ind - 1] = noSemEspaco->chaves[pivo]; 
  noComEspaco->numChaves++; // arrumando a qtd de chaves

  return (noComEspaco); // retornando a arvore pos divisao
  
}

NO* divideFilho(NO* pai, int ind) 
{
  NO* filho = pai->filhos[ind]; // armazena filho sem espaco
  NO* novo = criaNo(); // aloca novo no para fazer a divisao
  
  if(!novo) return (NULL); // erro de alocacao, retorna NULL
  
  novo->folha = filho->folha; // define se novo no e folha com base no filho sem espaco
  pai->filhos[ind + 1] = novo; // adiciona novo no como novo filho do no pai

  int pivo = t - 1;
  pai->chaves[ind] = filho->chaves[pivo]; // arrumando chave do pai
  pai->numChaves++; // arrumando qtd de chaves do pai
  novo->numChaves = pivo; // definindo qtd de chaves do novo filho
  filho->numChaves = pivo; // arrumando qtd de chaves do filho que estava sem espaco
  
  for(int i = 0; i < pivo; i++) novo->chaves[i] = filho->chaves[i + t]; // transferindo chs para o novo filho

  if(!novo->folha) // arrumando filhos do novo filho caso ele nao seja uma folha
  {
    for(int i = 0; i < pivo + 1; i++) 
    {
      novo->filhos[i] = filho->filhos[i + t];
      filho->filhos[i + t] = NULL;
    }
    
  }

  return (novo);
  
}

NO* insereNoComEspaco(NO* p, TIPO_CHAVE ch) 
{
  int i = p->numChaves - 1; // indice da ultima chave do vetor de chaves

  if(p->folha) // no p e folha
  {
    while(i >= 0 && (ch < p->chaves[i])) // organizando espaco no vetor
    {
      p->chaves[i + 1] = p->chaves[i];
      i--;
    }

    p->chaves[i + 1] = ch; // arrumando a chave
    p->numChaves++; // atualizando a qtd de chaves

    return (p); // retornando p pos insercao na folha
    
  }

  while(i >= 0 && (ch < p->chaves[i])) i--; // achando indice da chave suposta chave sucessora de ch no vetor
  i++;

  if(p->filhos[i]->numChaves == MAX_CHAVES) // filho do p esta cheio
  {
    p = divideNo(p, i + 1, p->filhos[i]);
    if(ch > p->chaves[i]) i++;
    
  }

  p->filhos[i] = insereNoComEspaco(p->filhos[i], ch); // fazendo a insercao para o filho do p
  
  return (p); // retornando p pos arrumar ele e seus filhos
  
}

bool insereNo(NO** raiz, TIPO_CHAVE ch) 
{
  if(buscaNo(*raiz, ch)) return (false); // chave ja existe, nao insere nada

  if(!(*raiz)) // raiz NULL, faz primeira insercao
  {
    *raiz = criaNo();
    
    if(!*raiz) return (false);

    (*raiz)->chaves[0] = ch;
    (*raiz)->numChaves = 1;
    
    return (true);
    
  }

  bool raizCheia = (*raiz)->numChaves == MAX_CHAVES;
  
  if(raizCheia) // raiz esta cheia, precisa fazer a divisao para poder fazer a insercao
  {
    NO* novaRaiz = criaNo(); // criando nova raiz
    
    if(!novaRaiz) return (false); // erro na criacao, nao deu pra inserir
    
    novaRaiz->folha = false; // informa que e no interno
    novaRaiz->filhos[0] = *raiz; // arruma o filho
    novaRaiz = divideNo(novaRaiz, 1, *raiz); // divide as chaves com o filho
    novaRaiz = insereNoComEspaco(novaRaiz, ch); // faz a insercao da nova chave
    *raiz = novaRaiz; // seta a nova raiz
    
    return (true); // insercao ocorreu perfeitamente
    
  }

  *raiz = insereNoComEspaco(*raiz, ch); // raiz tem espaco, so insere normalmente
  
  return (true); // insercao ocorreu perfeitamente
  
}

void imprimeArvore(NO* p, int ind) 
{
  if(p) 
  {
    if(p->numChaves == 0) 
    {
      fprintf(stdout, "Vazia");
      return;
    }

    int i;
    
    fprintf(stdout, "(");
    
    for(i = 0; i <= p->numChaves - 1; i++) 
    {
      imprimeArvore(p->filhos[i], (ind + 1));

      if((i != 0) && (i == p->numChaves - 1 || i != p->numChaves)) 
      {
        fprintf(stdout, " ");
        
      } else if((i <= ind) && (!p->folha)) fprintf(stdout, " ");

      fprintf(stdout, "%d", p->chaves[i]);

      if(!p->folha) fprintf(stdout, " ");
      
    }
    
    imprimeArvore(p->filhos[i], (ind + 1));
    
    fprintf(stdout, ")");
    
  }
  
}

void liberaArvore(NO* p)
{
  if(p) // so da free caso nao ja nao seja NULL
  {
    if(!p->folha) // se nao e no folha da free nos filhos tbm
    {
      for(int i = 0; i < p->numChaves - 1; i++) liberaArvore(p->filhos[i]);
      free(p->filhos);
      
    }
    
    free(p->chaves); // da free no vetor de chaves
    free(p); // da free no no p
    
  }
  
}

void removeFolha(NO* p, int ind)
{
  for(int i = ind + 1; i < p->numChaves; i++) p->chaves[i - 1] = p->chaves[i]; // arruma o vetor de chaves
  p->numChaves--; // arruma a qtd de chaves
  
}

void redistribuiIrmaoDir(NO* p, int ind) 
{
  NO* irmaoDir = p->filhos[ind + 1]; // armazena o irmao direito do filho de p
  NO* filho = p->filhos[ind]; // armazena o filho de p

  filho->chaves[filho->numChaves] = p->chaves[ind]; // arruma chave do filho de p
  p->chaves[ind] = irmaoDir->chaves[0]; // arruma chave do pai (no p)

  for(int i = 1; i < irmaoDir->numChaves; i++) 
  {
    irmaoDir->chaves[i - 1] = irmaoDir->chaves[i]; // arruma o vetor de chaves do irmao direito
  }

  if(!irmaoDir->folha) // se o irmao direito nao e folha
  {
    for(int i = 1; i < irmaoDir->numChaves + 1; i++) 
    {
      irmaoDir->filhos[i - 1] = irmaoDir->filhos[i]; // a arruma os filhos do irmao direito
    }
    
  }

  irmaoDir->numChaves--; // arruma a qtd de chaves do irmao direito
  filho->numChaves++; // arruma a qts de chaves do filho de p
  
}

void redistribuiIrmaoEsq(NO* p, int ind) 
{
  NO* irmaoEsq = p->filhos[ind - 1]; // armazena o irmao esquerdo do filho de p
  NO* filho = p->filhos[ind]; // armazena o filho de p

  for(int i = filho->numChaves - 1; i >= 0; i--)
  {
    filho->chaves[i + 1] = filho->chaves[i]; // arruma vetor de chaves do filho
  }
  
  filho->chaves[0] = irmaoEsq->chaves[irmaoEsq->numChaves - 1]; // arruma chave do filho
  p->chaves[ind - 1] = irmaoEsq->chaves[irmaoEsq->numChaves - 1]; // arruma chave do pai (no p)

  irmaoEsq->numChaves--; // arruma qtd de chaves do irmao esquerdo
  filho->numChaves++; // arruma qtd de chaves do filho de p
  
}

void fundeNos(NO* p, int ind) 
{
  NO* irmaoDir = p->filhos[ind + 1]; // armazena irmao direito do filho do p
  NO* filho = p->filhos[ind]; // armazena filho do p

  filho->chaves[t - 1] = p->chaves[ind]; // arruma chave do filho do p

  for(int i = 0; i < irmaoDir->numChaves; i++) 
  {
    filho->chaves[i + t - 1] = irmaoDir->chaves[i]; // arruma vetor de chaves do filho de p
  }

  if(!filho->folha) // se o filho de p nao e no folha
  {
    for(int i = 0; i < irmaoDir->numChaves + 1; i++) 
    {
      filho->filhos[i + t] = irmaoDir->filhos[i]; // arruma vetor de filhos do filho de p
    }
    
  }

  for(int i = ind + 1; i < p->numChaves; i++) 
  {
    p->chaves[i - 1] = p->chaves[i]; // arruma chaves do pai (no p)
    p->filhos[i] = p->filhos[i + 1]; // arruma filhos do pai (no p)
  }

  filho->numChaves += irmaoDir->numChaves; // arruma qutd de chaves do filho de p
  p->numChaves--; // arruma qtd de chaves do pai (no p)

  free(irmaoDir); // libera irmao direito
  
}

int indFilho(NO* p, int ind) 
{
  NO* filho = p->filhos[ind];

  if(ind != 0 && p->filhos[ind - 1]->numChaves >= t) 
  {
    redistribuiIrmaoEsq(p, ind);
    return (ind);
    
  } else if(ind != p->numChaves && p->filhos[ind + 1]->numChaves >= t) {
    
    redistribuiIrmaoDir(p, ind);
    return (ind);
    
  } else if(ind != 0) {
    
    fundeNos(p, ind - 1);
    return (ind - 1);
    
  } else {
    
    fundeNos(p, ind);
    return (ind);
    
  }
  
}

void removeNo(NO* p, TIPO_CHAVE ch) 
{
  int ind = 0;
  
  while(ind < p->numChaves && ch > p->chaves[ind]) ind++;
  
  if(ind < p->numChaves && ch == p->chaves[ind]) 
  {
    if(p->folha) removeFolha(p, ind);
    else removeInterno(p, ind);
    
  } else {
    
    if(p->folha) return; // ch not found

    NO* filho = p->filhos[ind];
    bool ultimaCh = ind == p->numChaves;
    
    if(filho->numChaves < t) indFilho(p, ind);
    
    if(ultimaCh && ind > p->numChaves) removeNo(p->filhos[ind - 1], ch);
    else removeNo(p->filhos[ind], ch);
    
  }
  
}

TIPO_CHAVE chaveIrmaoDir(NO* node, int ind) 
{
  NO* p = node->filhos[ind + 1];
  while(!p->folha) p = p->filhos[0];
  
  return (p->chaves[0]);
  
}

TIPO_CHAVE chaveIrmaoEsq(NO* node, int ind) 
{
  NO* p = node->filhos[ind];
  while(!p->folha) p = p->filhos[p->numChaves];
  
  return (p->chaves[p->numChaves - 1]);
  
}

void removeInterno(NO* p, int ind) 
{
  TIPO_CHAVE ch = p->chaves[ind];
  NO* irmaoDir = p->filhos[ind + 1];
  NO* irmaoEsq = p->filhos[ind];

  if(irmaoEsq->numChaves >= t) 
  {
    if(irmaoEsq->folha)
    {
      p->chaves[ind] = irmaoEsq->chaves[irmaoEsq->numChaves - 1];
      irmaoDir->chaves[0] = irmaoEsq->chaves[irmaoEsq->numChaves - 1];
      irmaoEsq->numChaves--;
      
    } else {
      
      TIPO_CHAVE chIrmaoEsq = chaveIrmaoEsq(p, ind);
      p->chaves[ind] = chIrmaoEsq;
      removeNo(irmaoEsq, chIrmaoEsq);
      
    }
    
  } else if(irmaoDir->numChaves >= t) {
    
    if(irmaoDir->folha) 
    {
      removeFolha(irmaoDir, 0);
      p->chaves[ind] = irmaoDir->chaves[0];
      

    } else {
      
      int chIrmaoDir = chaveIrmaoDir(p, ind);
      p->chaves[ind] = chIrmaoDir;
      removeNo(irmaoDir, chIrmaoDir);
      
    }
    
  } else {
    
    fundeNos(p, ind);
    removeNo(irmaoEsq, ch);
    
  }
  
}

void removeNoDaArvore(NO* p, TIPO_CHAVE ch) 
{
  int i = 0;

  while(i < p->numChaves && ch >= p->chaves[i]) i++;

  if(p->folha) 
  {
    if(i > 0 && ch == p->chaves[i - 1]) removeFolha(p, i - 1);
    else return; // nao encontrou a chave
    
    return;
    
  } else if(i > 0 && ch == p->chaves[i - 1]) {
    
    removeInterno(p, i - 1);
    return;
    
  }

  if(!p->folha && p->filhos[i]->numChaves < t) i = indFilho(p, i);
  
  removeNoDaArvore(p->filhos[i], ch);
  
  return;
  
}

bool leEntrada(FILE* arq, NO* p) 
{
  TIPO_CHAVE ch;
  char op;

  if(arq == NULL) 
  {
    printf("Erro: nao foi possivel ler o arquivo!\n");
    return (false);
    
  }

  while(fscanf(arq, "%c %d", &op, &ch) != EOF) 
  {

    if(op == 'i')
    {
      insereNo(&p, ch); 
      
    }
    
    if(op == 'p')
    {
      imprimeArvore(p, 0);
      fprintf(stdout, "\n");
     
    }
    
    if(op == 'r')
    {
      removeNoDaArvore(p, ch);
      
    }
    
    if(op == 'f')
    {
      liberaArvore(p);
      fclose(arq);
      return (true);
      
    }

  }

  fclose(arq);
  
  return (true);
  
}

// funcao main

int main(int argc, char *argv[]) 
{
  NO* raizDaArvore = criaNo();

  stdin = fopen(argv[1], "r");
  stdout = fopen(argv[2], "w");

  leEntrada(stdin, raizDaArvore);

  return (0);
  
}
