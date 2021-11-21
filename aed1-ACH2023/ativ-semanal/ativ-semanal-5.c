#include <stdio.h>
#define getName(var)  #var
#define true 1
#define false 0
#define MAX 50

typedef int bool;

typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
} REGISTRO;

typedef struct {
  int topo;
  REGISTRO A[MAX];
} PILHA;

/* Inicialização da PILHA (a PILHA jah esta criada e eh apontada 
pelo endereco em p) */
void inicializarPilha(PILHA* p){
    p->topo = -1;
} /* inicializarPILHA */

/* Exibição da pilha */
void exibirPilha(PILHA* p){
    printf("Pilha: \" ");
    int i;
    for (i=p->topo;i>=0;i--){
        printf("%i ", p->A[i].chave); // soh lembrando TIPOCHAVE = int
    }
    printf("\"\n");
} /* exibirPilha */

/* inserirElementoPilha - insere elemento no fim da pilha   */
bool inserirElementoPilha(PILHA* p, REGISTRO reg){
    if (p->topo+1>= MAX) return false;
    p->topo = p->topo+1;
    p->A[p->topo] = reg;
    return true;
} /* inserirElementoPILHA* /

/* Exibição da pilha (da base para o topo) */
void exibirPilhaInvertida(PILHA* p){
    printf("Pilha (da base para o topo): \" ");

    for (int i = 0; i <= p->topo; i++) {
        printf("%i ", p->A[i].chave);
    }
    
    printf("\"\n");
} /* exibirPilhaInvertida */ 

/* Exibição da pilha */
void exibirPilhaVertical(PILHA* p){
    printf("Pilha:\n\"\n");
    int i;
    for (i=p->topo;i>=0;i--){
        printf("%i\n", p->A[i].chave); // soh lembrando TIPOCHAVE = int
    }
    printf("\"\n");
} /* exibirPilha */

/* Exibição da pilha (da base para o topo) */
void exibirPilhaVerticalInvertida(PILHA* p){
    printf("Pilha (da base para o topo):\n\"\n");

    for (int i = 0; i <= p->topo; i++) {
        printf("%i\n", p->A[i].chave);
    }
    
    printf("\"\n");
} /* exibirPilhaInvertida */ 

int main() {
    PILHA pilha1;
    inicializarPilha(&pilha1);
    printf("\n--- Pilha inicializada %s\n", getName(pilha1));
    exibirPilha(&pilha1);

    REGISTRO reg1;
    REGISTRO reg2;
    REGISTRO reg3;
    REGISTRO reg4;
    REGISTRO reg5;
    reg1.chave=3;
    reg2.chave=4;
    reg3.chave=2;
    reg4.chave=12;
    reg5.chave=1;

    inserirElementoPilha(&pilha1, reg1);
    inserirElementoPilha(&pilha1, reg2);
    inserirElementoPilha(&pilha1, reg3);
    inserirElementoPilha(&pilha1, reg4);
    inserirElementoPilha(&pilha1, reg5);

    printf("--- Exibição da pilha (topo->base)\n");
    exibirPilha(&pilha1);

    printf("--- Exibição da pilha (base->topo)\n");
    exibirPilhaInvertida(&pilha1);

    printf("\n--- Exibição da pilha verticalmente (topo->base)\n");
    exibirPilhaVertical(&pilha1);
    
    printf("--- Exibição da pilha verticalmente (base->topo)\n");
    exibirPilhaVerticalInvertida(&pilha1);

    return 0;
}