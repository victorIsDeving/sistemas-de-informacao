/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   094 - Prof. Luciano Antonio Digiampietri                      **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   Victor Augusto Costa Monteiro                8942937          **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"
#define MAX 5

PFILA criarFila(){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->referencias = (PONT*) malloc(sizeof(PONT)*MAX);
  res->heap = (PONT*) malloc(sizeof(PONT)*MAX);
  int i;
  for (i=0;i<MAX;i++) {
    res->referencias[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}


bool exibirLog(PFILA f){

  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;

  int i;
  for (i=0;i<f->elementosNoHeap;i++){
    atual = f->heap[i];
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
  }
  printf("\n\n");
}

int tamanho(PFILA f){
  return f->elementosNoHeap;
}

bool inserirElemento(PFILA f, int id, float prioridade){
    if ( id<0 || id>=MAX || f->referencias[id] || f->elementosNoHeap==MAX ) return false;

    PONT novoElemento = (PONT) malloc(sizeof(ELEMENTO));
    f->referencias[id] = novoElemento;
    novoElemento->id = id;
    novoElemento->prioridade = prioridade;
    int i = f->elementosNoHeap;
    novoElemento->posicao = i;

    if ( f->elementosNoHeap==0 ) { //heap está vazio
        f->heap[0] = f->referencias[id];
    } else { //heap não vazio
        f->heap[i] = novoElemento;
        PONT pai = f->heap[ (i-1)/2 ];
        while ( pai->prioridade < prioridade) {
            f->heap[i] = pai;
            f->heap[ (i-1)/2 ] = novoElemento;
            pai->posicao = i;
            novoElemento->posicao = (i-1)/2;
            i=(i-1)/2;
            pai = f->heap[ (i-1)/2 ];
        }
    }

    f->elementosNoHeap++;
    return true;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
    if ( id<0 || id>=MAX || f->referencias[id]==NULL ) return false;
    if ( f->referencias[id]->prioridade>=novaPrioridade ) return false; //novaPrioridade é maior que a atual

    f->referencias[id]->prioridade = novaPrioridade;
    if ( f->referencias[id]->posicao==0 ) return true; //elemento já era o primeiro na fila
    int posicao = f->referencias[id]->posicao; //posicao antes do aumento

    PONT elemento = f->referencias[id];
    PONT pai = f->heap[ (posicao-1)/2 ];
    while ( pai->prioridade < novaPrioridade) {
        f->heap[posicao] = pai;
        f->heap[ (posicao-1)/2 ] = elemento;
        pai->posicao = posicao;
        elemento->posicao = (posicao-1)/2;
        posicao=(posicao-1)/2;
        pai = f->heap[ (posicao-1)/2 ];
    }

    return true;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
    if ( id<0 || id>=MAX || !f->referencias[id] ) return false;
    if ( f->referencias[id]->prioridade<=novaPrioridade ) return false; //novaPrioridade é de fato menor que a atual

    f->referencias[id]->prioridade = novaPrioridade;
    int posicao = f->referencias[id]->posicao; //posicao antes da diminuição
    if ( posicao==0 || posicao==f->elementosNoHeap-1) return true; //elemento sozinho na fila ou já é o último

    int i;
    for ( i=posicao; novaPrioridade<=f->heap[posicao+1]->prioridade; i++ ) {
        f->heap[posicao+1] = f->heap[posicao];
        f->heap[posicao] = f->referencias[id];
        f->heap[posicao+1]->posicao--;
        f->referencias[id]->posicao++;
    }

    return true;
}

PONT removerElemento(PFILA f){
    if ( !f->heap[0] ) return NULL; //não dá para excluir se o heap estiver vazio

    PONT primeiroHeap = f->heap[0];
    f->referencias[primeiroHeap->id] = NULL;

    f->heap[0] = f->heap[f->elementosNoHeap-1]; //colocando último elemento em primeiro
    
    if( f->elementosNoHeap>1 ) { //existem filhos para fazer o ajuste
        int i = 0;
        while ( 2*i+1 <= f->elementosNoHeap-1 || 2*i+2 <= f->elementosNoHeap-1 ) { 
            PONT pai = f->heap[i];
            PONT filhoEsquerda = f->heap[ 2*i+1 ];
            PONT filhoDireita = f->heap[ 2*i+2 ];
            if ( f->heap[i]->prioridade < f->heap[ 2*i+1 ]->prioridade ) { //troca com o filho da esquerda
                f->heap[i] = filhoEsquerda;
                f->heap[ 2*i+1 ] = pai;
                pai->posicao = 2*i+1;
                filhoEsquerda->posicao = i;
                i=2*i+1;
            } else if (f->heap[i]->prioridade < f->heap[ 2*i+2 ]->prioridade) { //troca com o filho da direita
                f->heap[i] = filhoDireita;
                f->heap[ 2*i+1 ] = pai;
                pai->posicao = 2*i+2;
                filhoDireita->posicao = i;
                i=2*i+2;
            } else { //elemento pai tem prioridade menor que ambos os filhos
                if ( f->heap[ 2*i+1 ]->prioridade >= f->heap[ 2*i+2 ]->prioridade ) { //filho esquerda tem prioridade maior ou igual que o filho da direita
                    f->heap[i] = filhoEsquerda;
                    f->heap[ 2*i+1 ] = pai;
                    pai->posicao = 2*i+1;
                    filhoEsquerda->posicao = i;
                    i=2*i+1;
                } else { //filho da direita tem prioridade maior que o filho da esquerda
                    f->heap[i] = filhoDireita;
                    f->heap[ 2*i+1 ] = pai;
                    pai->posicao = 2*i+2;
                    filhoDireita->posicao = i;
                    i=2*i+2;
                }
            }
        }
    }

    f->elementosNoHeap--;
    f->heap[f->elementosNoHeap] = NULL;

    return primeiroHeap;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
    if ( id<0 || id>MAX ) return false;
    if ( f->referencias[id] ) {
        *resposta = f->referencias[id]->prioridade;
        return true;
    } else {
        return false;
    }
}
