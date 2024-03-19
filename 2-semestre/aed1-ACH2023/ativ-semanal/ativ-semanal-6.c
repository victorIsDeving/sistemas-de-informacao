#include <stdio.h>
#include <malloc.h>
#define getName(var)  #var
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
  // outros campos...
} REGISTRO;


typedef struct auxElem {
  REGISTRO reg;
  struct auxElem* ant;
  struct auxElem* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
  PONT cabeca;
} DEQUE;

/* Inicialização do deque (o deque jah esta criado e eh apontado pelo endereco em d) */
void inicializarDeque(DEQUE* d){
  d->cabeca = (PONT) malloc(sizeof(ELEMENTO));
  d->cabeca->prox = d->cabeca;
  d->cabeca->ant = d->cabeca;
} /* inicializarDeque */

/* Exibição do DEQUE a partir do inicio1 */
void exibirDequeInicio(DEQUE* d){
  PONT end = d->cabeca->prox;
  printf("Deque partindo do início: \" ");
  while (end != d->cabeca){
    printf("%i ", end->reg.chave); // soh lembrando TIPOCHAVE = int
    end = end->prox;
  }
  printf("\"\n");
} /* exibirDequeInicio */

/* Inserção no deque, entrada 1 */
bool inserirDequeInicio(DEQUE* d,REGISTRO reg) {
  PONT i = (PONT) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  i->ant = d->cabeca;
  i->prox = d->cabeca->prox;
  d->cabeca->prox = i;
  i->prox->ant = i;
  return true;
} /* inserirDequeInicio */

/* encontrarMax - copia a maior chave dentro do DEQUE para o
   endereco apontado por max passado como parametro e retorna true.
   Se o DEQUE estiver vazio, deve retornar false. */
bool encontrarMax(DEQUE* d, int* max) {
  bool resposta = false;
  if (d->cabeca->prox == d->cabeca) return resposta;

  resposta = true;
  PONT elemAtual = d->cabeca->prox;
  int iteracoes = 0;
  *max = elemAtual->reg.chave;
  while (elemAtual->prox != d->cabeca) {
    if (*max < elemAtual->prox->reg.chave) *max = elemAtual->prox->reg.chave;
    elemAtual = elemAtual->prox;
    iteracoes++;
  }
  printf("Iteracoes totais %i\n", iteracoes);
  return resposta;
} /* encontrarMax */

int main() {
  DEQUE deck1;

  inicializarDeque(&deck1);
  printf("\n--- Deque %s recém inicializado\n", getName(deck1));
  exibirDequeInicio(&deck1);

  REGISTRO reg1;
  REGISTRO reg2;
  REGISTRO reg3;
  REGISTRO reg4;
  REGISTRO reg5;
  reg1.chave=5;
  reg2.chave=16;
  reg3.chave=20;
  reg4.chave=18;
  reg5.chave=19;

  inserirDequeInicio(&deck1, reg1);
  printf("\n--- Elementos de %s \n", getName(deck1));
  exibirDequeInicio(&deck1);
  printf("- Maior chave dos elementos válidos de %s\n", getName(deck1));
  int varMax;
  encontrarMax(&deck1, &varMax);
  printf("Maior chave encontrada foi %i\n", varMax);
  
  inserirDequeInicio(&deck1, reg2);
  printf("\n--- Elementos de %s \n", getName(deck1));
  exibirDequeInicio(&deck1);
  printf("- Maior chave dos elementos válidos de %s\n", getName(deck1));
  encontrarMax(&deck1, &varMax);
  printf("Maior chave encontrada foi %i\n", varMax);
  
  inserirDequeInicio(&deck1, reg3);
  printf("\n--- Elementos de %s \n", getName(deck1));
  exibirDequeInicio(&deck1);
  printf("- Maior chave dos elementos válidos de %s\n", getName(deck1));
  encontrarMax(&deck1, &varMax);
  printf("Maior chave encontrada foi %i\n", varMax);
  
  inserirDequeInicio(&deck1, reg4);
  printf("\n--- Elementos de %s \n", getName(deck1));
  exibirDequeInicio(&deck1);
  printf("- Maior chave dos elementos válidos de %s\n", getName(deck1));
  encontrarMax(&deck1, &varMax);
  printf("Maior chave encontrada foi %i\n", varMax);

  inserirDequeInicio(&deck1, reg5);
  printf("\n--- Elementos de %s \n", getName(deck1));
  exibirDequeInicio(&deck1);
  printf("- Maior chave dos elementos válidos de %s\n", getName(deck1));
  encontrarMax(&deck1, &varMax);
  printf("Maior chave encontrada foi %i\n", varMax);

  int var = 4/5;
  printf("\n\n\n%i", var);

  return 0;
}