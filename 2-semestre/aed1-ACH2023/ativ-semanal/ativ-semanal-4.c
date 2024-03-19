#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
  // outros campos...
} REGISTRO;

typedef struct tempRegistro{
  REGISTRO reg;
  struct tempRegistro *ant, *prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
  PONT inicio;
} LISTA;

/* Inicialização da lista ligada (a lista jah esta criada e eh apontada 
pelo endereco em l) */
void inicializarLista(LISTA* l){
  l->inicio = NULL;
} /* inicializarLista */

/* Exibição da lista seqüencial */
void exibirLista(LISTA* l){
  PONT end = l->inicio;
  printf("Lista: \" ");
  while (end != NULL){
    printf("%d ", end->reg.chave); // soh lembrando TIPOCHAVE = int
    end = end->prox;
  }
  printf("\"\n");
} /* exibirLista */ 

/* Busca sequencial - funcao de exclusao (retorna no endereço *ant o indice do
   elemento anterior ao elemento que está sendo buscado [ant recebe o elemento
   anterior independente do elemento buscado ser ou não encontrado]) */
PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant){
  *ant = NULL;
  PONT atual = l->inicio;
  while (atual != NULL && atual->reg.chave<ch){
    *ant = atual;
    atual = atual->prox;
  }
  if ((atual != NULL) && (atual->reg.chave == ch)) return atual;
  return NULL;
}
/* buscaSequencialExc */

/* Inserção em lista ordenada sem duplicação */
bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
  TIPOCHAVE ch = reg.chave;
  PONT ant, i;
  i = buscaSeqExc(l,ch,&ant);
  if (i != NULL)  return false;
  i = (PONT) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  if (ant == NULL) { // o novo elemento serah o 1o da lista
    i->prox = l->inicio;
    i->ant = NULL;
    if (i->prox)
    {
      i->prox->ant = i;
    }
    l->inicio = i;
  } else {  // inserção após um elemento já existente
    i->prox = ant->prox;
    ant->prox = i;
    i->ant = ant;
  }  
  return true;
} /* inserirElemListaOrd */

bool verificarListaDuplamenteLigada(LISTA* l){
  bool res = true;
  if (!l->inicio) return res;
  PONT ant;
  PONT pos = l->inicio;
  if (pos->ant){
    res = false;
    printf("Problema na verificacao (1): endereco anterior do primeiro elemento difere de NULL.\n");                
  }
  while (pos != NULL){
    ant = pos;
    pos = pos->prox;
    if (pos && pos->ant != ant){
      printf("TESTE %p x %p.\n", pos->ant, ant);    
      printf("Problema na verificacao (1): endereco anterior do elemento %i difere do endereco de %i: %p x %p.\n", pos->reg.chave, ant->reg.chave, pos->ant, ant);
      res = false;
    }
  }
  return res;
} /* verificarListaDuplamenteLigada */

void retornaEnderecos(LISTA* l) {
  PONT end = l->inicio;
  printf("\n--- Endereço dos elementos da lista\n");
  while (end != NULL){
    printf("Endereço do elemento %i: %p\n", end->reg.chave, end);
    printf("Endereço do elemento anterior: %p\n", end->ant);
    printf("Endereço do elemento posterior: %p\n\n", end->prox);
    end = end->prox;
  }
  printf("\n");
}

int main() {
  printf("\n####lista1####\n");
  LISTA lista1;
  printf("\n--Inicializacao da lista:\n");
  inicializarLista(&lista1);
  exibirLista(&lista1);
  REGISTRO reg1;
  REGISTRO reg2;
  REGISTRO reg3;
  REGISTRO reg4;
  REGISTRO reg5;
  REGISTRO reg6;
  reg1.chave=3;
  reg2.chave=4;
  reg3.chave=2;
  reg4.chave=12;
  reg5.chave=12;
  reg6.chave=1;
  inserirElemListaOrd(&lista1,reg1);
  inserirElemListaOrd(&lista1,reg2);
  inserirElemListaOrd(&lista1,reg3);
  inserirElemListaOrd(&lista1,reg4);
  inserirElemListaOrd(&lista1,reg5);
  inserirElemListaOrd(&lista1,reg6);
  printf("\n--- Lista depois da insercao dos elementos criados:\n");
  exibirLista(&lista1);

  retornaEnderecos(&lista1);

  verificarListaDuplamenteLigada(&lista1);
  return 0;
}