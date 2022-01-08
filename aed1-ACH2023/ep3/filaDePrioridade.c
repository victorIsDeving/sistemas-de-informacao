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

    printf("Lista heap:");
    for (i=0;i<f->elementosNoHeap;i++){
        atual = f->heap[i];
        printf("\n  %p",atual);
        printf(" [%i;%f;%i]", atual->id, atual->prioridade, atual->posicao);
    }

    printf("\nLista referencias:");
    for (i=0;i<f->elementosNoHeap;i++){
        atual = f->referencias[i];
        printf("\n  %p",atual);
        printf(" [%i;%f;%i]", atual->id, atual->prioridade, atual->posicao);
    }
    printf("\n\n");
}

int tamanho(PFILA f){
  return f->elementosNoHeap;
}

bool inserirElemento(PFILA f, int id, float prioridade){
    if ( id<0 || id>=MAX || f->referencias[id] ) return false;

    PONT novoElemento = (PONT) malloc(sizeof(ELEMENTO));
    f->referencias[id] = novoElemento;
    novoElemento->id = id;
    novoElemento->prioridade = prioridade;

    if ( f->elementosNoHeap==0 ) { //heap está vazio
        f->heap[0] = f->referencias[id];
        f->referencias[id]->posicao = 0;
        // f->elementosNoHeap = 1; //linha quebra com segmentation fault :(
    } else {
        PONT atual;
        int i;
        for ( i=0; i<f->elementosNoHeap; i++ ) { //encontrar posição no heap do novo elemento
            atual = f->heap[i];
            if ( atual->prioridade < f->referencias[id]->prioridade ) { //quando a prioridade do atual for menor, encontramos a posição (elementos comprioridade igual serão inseridos à direita)
                int j = f->elementosNoHeap;
                for ( j; j>=i; j-- ) { //mover elementos com id menor que o novo para a direita no heap
                    f->heap[j+1] = f->heap[j];
                    f->heap[j+1]->posicao++;
                }
                atual = f->referencias[id];
                f->referencias[id]->posicao = i;
                f->elementosNoHeap++;
            }
        }
    }

    return true;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
    if ( id<0 || id>=MAX || !f->referencias[id] ) return false;
    if ( f->referencias[id]->prioridade>=novaPrioridade ) return false; //novaPrioridade é de fato maior que a atual

    f->referencias[id]->prioridade = novaPrioridade;
    int posicao = f->referencias[id]->posicao; //posicao antes do aumento
    if ( posicao==0 ) return true; //elemento já era o primeiro na fila

    int i;
    for ( i=posicao; novaPrioridade>=f->heap[posicao-1]->prioridade; i-- ) { //trocando de posição com o elemento da esquerda se novaPrioridade for maior
        f->heap[posicao] = f->heap[posicao-1];
        f->heap[posicao-1] = f->referencias[id];
        f->heap[posicao]->posicao++;
        f->referencias[id]->posicao--;
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
    for ( i=posicao; novaPrioridade<=f->heap[posicao+1]->prioridade; i++ ) { //trocando de posição com o elemento da direita se novaPrioridade for menor
        f->heap[posicao+1] = f->heap[posicao];
        f->heap[posicao] = f->referencias[id];
        f->heap[posicao+1]->posicao--;
        f->referencias[id]->posicao++;
    }

    return true;
}

PONT removerElemento(PFILA f){
    if ( !f->heap[0] ) return NULL; //inserir || f->elementosNoHeap==0

    PONT primeiroHeap = f->heap[0];
    f->referencias[primeiroHeap->id] = NULL;

    int i = 0;
    while ( f->heap[i+1] ) { //navegar pelos elementos da esquerda para a direita, puxando o seguinte para o atual caso o seguinte exista
        f->heap[i] = f->heap[i+1];
        f->heap[i]->posicao--;
        i++;
    }

    f->elementosNoHeap--;

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
