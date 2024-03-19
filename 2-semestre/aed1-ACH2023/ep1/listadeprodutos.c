/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   094 - Prof. Luciano Antonio Digiampietri                      **/
/**                                                                 **/
/**   EP 1 - Lista Ligada de Produtos                               **/
/**                                                                 **/
/**   Victor Augusto Costa Monteiro                   8942937       **/
/**                                                                 **/
/*********************************************************************/
#include "listadeprodutos.h"

PLISTA criarLista(){
  PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
  int x;
  for (x=0;x<NUMTIPOS;x++){
    res->LISTADELISTAS[x]=(PONT) malloc(sizeof(REGISTRO));
    res->LISTADELISTAS[x]->id=-1;
    res->LISTADELISTAS[x]->quantidade=0;
    res->LISTADELISTAS[x]->valorUnitario=0;
    res->LISTADELISTAS[x]->proxProd=NULL;
  }
  return res;
}


int tamanho(PLISTA l){
  int tam = 0;
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      atual = atual->proxProd;
      tam++;
    }
  }
  return tam;
}

PONT buscarID(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual;
      atual = atual->proxProd;
    }
  }
  return NULL;
}

PONT buscarIDTipo(PLISTA l, int id, int tipo){
  if (tipo<0 || tipo>=NUMTIPOS) return NULL;
  PONT atual = l->LISTADELISTAS[tipo]->proxProd;
  while (atual) {
    if (atual->id == id) return atual;
    atual = atual->proxProd;
  }
  return NULL;
}

void exibirLog(PLISTA f){
  int numElementos = tamanho(f);
  printf("Log lista [elementos: %i]\n", numElementos);
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    printf("  #TIPO: %i -> ", x);
    atual = f->LISTADELISTAS[x]->proxProd;
    while (atual){
      printf(" [%i;%i;%i;$%i]", atual->id, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
      atual = atual->proxProd;
    }
    printf("\n");
  }
  printf("\n");
}

int consultarValorUnitario(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual->valorUnitario;
      atual = atual->proxProd;
    }
  }
  return 0;
}





bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){

  if (id<0 || quantidade<0 || valor<0) return 0;

  if (tipo>=0 && tipo<=NUMTIPOS-1) {
    PONT reg = (PONT) malloc(sizeof(REGISTRO));
    reg->id = id; 
    reg->quantidade = quantidade; 
    reg->valorUnitario = valor; 
    int valorTotalReg = quantidade * valor;
    printf("\nreg %p", reg);
    printf("\nreg->id %i", reg->id);

    PONT atual = l->LISTADELISTAS[tipo]->proxProd;
    if (atual == NULL) {
      reg->proxProd = NULL;
      atual = reg;
      printf("\nl->LISTADELISTAS[tipo]->proxProd %p\n", atual);
      return 1;
    } else {
      int valorTotalAtual = atual->quantidade * atual->valorUnitario;
      while (atual->proxProd != NULL && valorTotalAtual > valorTotalReg) {
        atual = atual->proxProd;
        valorTotalAtual = atual->quantidade * atual->valorUnitario;
      }
      if (atual->proxProd != NULL) {
        reg->proxProd = atual;
        atual->proxProd = reg;
        return 1;
      } else { 
        reg->proxProd = NULL;
        atual->proxProd = reg;
        return 1;
      }
    }
  }

  return false;
}



bool removerItensDeUmProduto(PLISTA l, int id, int quantidade){
    
  PONT reg = buscarID(l, id);

  if ( reg && quantidade<=0 && reg->quantidade<quantidade ) {
    reg->quantidade -= quantidade;
    int valorTotalNovo = reg->quantidade * reg->valorUnitario;
    
    int tipo;
    PONT atual,ant,prox;
    for (int x=0;x<NUMTIPOS;x++){
      ant = l->LISTADELISTAS[x];
      atual = l->LISTADELISTAS[x]->proxProd;
      prox = l->LISTADELISTAS[x]->proxProd->proxProd;
      while (atual) {
        if (atual->id == id) {
          tipo = x; 
          break;
        }
        ant = atual;
        atual = prox->proxProd;
        prox = atual->proxProd;
      }
    }

    int valorTotalAnt = ant->quantidade * ant->valorUnitario;
    
    if (reg->quantidade != 0) {
      if (valorTotalNovo < valorTotalAnt) {
        reg->proxProd = ant;
        ant->proxProd = prox;
      }
    } else {
      ant->proxProd = prox;
      free(reg);
    }
  }

  return false;
}


bool atualizarValorDoProduto(PLISTA l, int id, int valor){

  PONT reg = buscarID(l, id);

  if ( reg && valor>0 ) {
    reg->valorUnitario = valor;
    int valorTotalNovo = reg->quantidade * reg->valorUnitario;

    int tipo;

    PONT atual,ant,prox;
      
    for (int x=0;x<NUMTIPOS;x++){
      ant = l->LISTADELISTAS[x];
      atual = l->LISTADELISTAS[x]->proxProd;
      prox = l->LISTADELISTAS[x]->proxProd->proxProd;
      while (atual) {
        if (atual->id == id) {
          tipo = x; 
          break;
        }
        ant = atual;
        atual = prox->proxProd;
        prox = atual->proxProd;
      }
    }

    int valorTotalAnt = ant->quantidade * ant->valorUnitario;
    int valorTotalProx = prox->quantidade * prox->valorUnitario;

    if (valorTotalNovo < valorTotalAnt) {
      reg->proxProd = ant;
      ant->proxProd = prox;
    }

    if (valorTotalNovo > valorTotalProx) {
      reg->proxProd = prox->proxProd;
      ant->proxProd = prox;
      prox->proxProd = reg;
    }  
  }

  return false;
}