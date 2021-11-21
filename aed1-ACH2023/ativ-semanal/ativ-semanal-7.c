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

typedef struct aux {
  REGISTRO reg;
  struct aux* prox;
} ELEMENTO, *PONT;;

typedef struct {
  PONT cabeca;
  PONT fim;
} FILA;

/* Inicialização da fila ligada (a fila jah esta criada e eh apontada 
pelo endereco em f) */
void inicializarFila(FILA* f){
  f->cabeca = (PONT) malloc(sizeof(ELEMENTO));
  f->cabeca->prox = NULL;
  f->fim = f->cabeca;
} /* inicializarFila */

/* Inserção no fim da fila */
bool inserirNaFila(FILA* f,REGISTRO reg) {
  PONT novo = (PONT) malloc(sizeof(ELEMENTO));
  novo->reg = reg;
  novo->prox = NULL;
  if (f->cabeca->prox==NULL){
     f->cabeca->prox = novo;
  }else{
     f->fim->prox = novo;
  }
  f->fim = novo;
  return true;
} /* inserir */

/* Excluir  */
bool excluirDaFila(FILA* f, REGISTRO* reg) {
  if (f->cabeca->prox==f->cabeca){
    return false;                     
  }
  *reg = f->cabeca->prox->reg;
  PONT apagar = f->cabeca->prox;
  f->cabeca->prox = f->cabeca->prox->prox;
  free(apagar);
  if (f->cabeca->prox == NULL){
    f->fim = NULL;
  }
  return true;
} /* excluirDaFila */

/* Exibição da fila sequencial */
void exibirFila(FILA* f){
  PONT end = f->cabeca->prox;
  printf("Fila: \" ");
  while (end != NULL){
    printf("%d ", end->reg.chave); // soh lembrando TIPOCHAVE = int
    end = end->prox;
  }
  printf("\"\n");
} /* exibirFila */

void retornaEnderecos(FILA* f) {
  PONT end = f->cabeca;
  printf("- Endereço dos elementos da fila\n");
  while (end != NULL){
    printf("Endereço do elemento %i: %p\n", end->reg.chave, end);
    printf("Endereço do elemento posterior: %p\n", end->prox);
    end = end->prox;
  }
  printf("\n");
}

int main() {
    
    FILA line1;
    inicializarFila(&line1);
    printf("\n--- Fila %s recém incializada\n", getName(line1));
    exibirFila(&line1);

    REGISTRO reg1;
    REGISTRO reg2;
    REGISTRO reg3;
    REGISTRO reg4;
    REGISTRO reg5;
    REGISTRO reg6;
    REGISTRO reg7;
    reg1.chave=3;
    reg2.chave=11;
    reg3.chave=21;
    reg4.chave=23;
    reg5.chave=24;
    reg6.chave=30;
    reg7.chave=32;

    inserirNaFila(&line1, reg1);
    printf("\n--- Fila %s depois de uma inserção\n", getName(line1));
    exibirFila(&line1);

    inserirNaFila(&line1, reg2);
    printf("\n--- Fila %s depois de uma inserção\n", getName(line1));
    exibirFila(&line1);

    inserirNaFila(&line1, reg3);
    printf("\n--- Fila %s depois de uma inserção\n", getName(line1));
    exibirFila(&line1);

    inserirNaFila(&line1, reg4);
    printf("\n--- Fila %s depois de uma inserção\n", getName(line1));
    exibirFila(&line1);

    inserirNaFila(&line1, reg5);
    printf("\n--- Fila %s depois de uma inserção\n", getName(line1));
    exibirFila(&line1);

    inserirNaFila(&line1, reg6);
    printf("\n--- Fila %s depois de uma inserção\n", getName(line1));
    exibirFila(&line1);

    inserirNaFila(&line1, reg7);
    printf("\n--- Fila %s depois de uma inserção\n", getName(line1));
    exibirFila(&line1);
    retornaEnderecos(&line1);

    REGISTRO exclusao1;
    REGISTRO exclusao2;
    REGISTRO exclusao3;
    REGISTRO exclusao4;
    REGISTRO exclusao5;
    REGISTRO exclusao6;
    REGISTRO exclusao7;
    
    excluirDaFila(&line1, &exclusao1);
    printf("\n--- Fila %s depois da exclusão\n", getName(line1));
    exibirFila(&line1);

    excluirDaFila(&line1, &exclusao2);
    printf("\n--- Fila %s depois da exclusão\n", getName(line1));
    exibirFila(&line1);

    excluirDaFila(&line1, &exclusao3);
    printf("\n--- Fila %s depois da exclusão\n", getName(line1));
    exibirFila(&line1);

    excluirDaFila(&line1, &exclusao4);
    printf("\n--- Fila %s depois da exclusão\n", getName(line1));
    exibirFila(&line1);

    excluirDaFila(&line1, &exclusao5);
    printf("\n--- Fila %s depois da exclusão\n", getName(line1));
    exibirFila(&line1);
    retornaEnderecos(&line1);

    excluirDaFila(&line1, &exclusao6);
    printf("\n--- Fila %s depois da exclusão\n", getName(line1));
    exibirFila(&line1);
    retornaEnderecos(&line1);

    excluirDaFila(&line1, &exclusao7);
    printf("\n--- Fila %s depois da exclusão\n", getName(line1));
    exibirFila(&line1);
    retornaEnderecos(&line1);

    printf("\n--- Teste retorno dos elementos nos registros de exclusao\n");
    printf("Registro de exclusao %s com a chave %i\n(esperado é o %s com a chave %i)\n", getName(exclusao1), exclusao1, getName(reg1), reg1);
    printf("Registro de exclusao %s com a chave %i\n(esperado é o %s com a chave %i)\n", getName(exclusao2), exclusao2, getName(reg2), reg2);
    printf("Registro de exclusao %s com a chave %i\n(esperado é o %s com a chave %i)\n", getName(exclusao3), exclusao3, getName(reg3), reg3);
    printf("Registro de exclusao %s com a chave %i\n(esperado é o %s com a chave %i)\n", getName(exclusao4), exclusao4, getName(reg4), reg4);
    printf("Registro de exclusao %s com a chave %i\n(esperado é o %s com a chave %i)\n", getName(exclusao5), exclusao5, getName(reg5), reg5);
    printf("Registro de exclusao %s com a chave %i\n(esperado é o %s com a chave %i)\n", getName(exclusao6), exclusao6, getName(reg6), reg6);
    printf("Registro de exclusao %s com a chave %i\n(esperado é o %s com a chave %i)\n", getName(exclusao7), exclusao7, getName(reg7), reg7);

    return 0;
}