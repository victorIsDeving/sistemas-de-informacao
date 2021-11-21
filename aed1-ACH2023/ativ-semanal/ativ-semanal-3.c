#include <stdio.h>
#define MAX 50
#define ERRO -1
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct{
TIPOCHAVE chave;
} REGISTRO;

typedef struct {
REGISTRO A[MAX+1];
int nroElem;
} LISTA;

void inicializarLista(LISTA* l){
  l->nroElem = 0;
}

void exibirLista(LISTA* l){
  int i;
  printf("Lista: \" ");
  for (i=1; i < l->nroElem; i++)
  printf("%i ", l->A[i].chave);
  printf("\"\n");
}

bool inserirElemLista(LISTA* l, REGISTRO reg, int i) {
  int j;
  if ((l->nroElem >= MAX) || (i < 0) || (i > l->nroElem)) 
    return(false);
  for (j = l->nroElem; j > i; j--) l->A[j] = l->A[j-1];
  l->A[i] = reg;
  l->nroElem++;
  return true;
}

void ordenarBubbleSort(LISTA* l, int tam) {
  int ult, i, aux;
  for (ult = tam-1; ult>0; ult--) {
    for (i=1; i<ult; i++) {
      if (l->A[i].chave > l->A[i+1].chave) {
        aux = l->A[i].chave;
        l->A[i].chave = l->A[i+1].chave;
        l->A[i+1].chave = aux;
      }
    }
  }
}

int main() {
  printf("\n####lista1####\n");
  LISTA lista1;
  inicializarLista(&lista1);
  exibirLista(&lista1);
  REGISTRO reg;
  inserirElemLista(&lista1,reg,0);
  reg.chave=3;
  inserirElemLista(&lista1,reg,1);
  reg.chave=4;
  inserirElemLista(&lista1,reg,2);
  reg.chave=1;
  inserirElemLista(&lista1,reg,3);
  reg.chave=12;
  inserirElemLista(&lista1,reg,4);
  exibirLista(&lista1);

  ordenarBubbleSort(&lista1, lista1.nroElem);
  printf("Depois do BubbleSort\n");
  exibirLista(&lista1);

  return 0;
}