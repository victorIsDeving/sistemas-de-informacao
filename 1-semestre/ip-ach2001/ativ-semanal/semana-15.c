#include <stdio.h>

typedef struct {
  int nusp;
  float nota;
} ALUNO;

typedef struct {
  ALUNO A[5];
} TURMA;

void imprimir(TURMA* t){
  int i;
  for (i=0;i<5;i++){
    printf("NUSP: %5i, nota: %5.2f\n", t->A[i].nusp, t->A[i].nota);
  }
}

void ordenar(TURMA* t){

  int ult, i, aux;
  for (ult = 4; ult>0; ult--) {
    for (i=0; i<ult; i++) {
      if (t->A[i].nota > t->A[i+1].nota) {
            aux = t->A[i].nota;
            t->A[i].nota = t->A[i+1].nota;
            t->A[i+1].nota = aux;
        }
    }
  }

}



int main() {
  TURMA T04;
  T04.A[0].nusp = 012;
  T04.A[1].nusp = 111;
  T04.A[2].nusp = 222;
  T04.A[3].nusp = 333;
  T04.A[4].nusp = 444;

  T04.A[0].nota = 4.5;
  T04.A[1].nota = 6;
  T04.A[2].nota = 10;
  T04.A[3].nota = 7;
  T04.A[4].nota = 7.5;

  imprimir(&T04);

  printf("\nOrdenando:\n");
  ordenar(&T04);

  imprimir(&T04);
  
  return 0;
}


/* SAIDA
NUSP:    10, nota:  4.50
NUSP:   111, nota:  6.00
NUSP:   222, nota: 10.00
NUSP:   333, nota:  7.00
NUSP:   444, nota:  7.50

Ordenando:
NUSP:    10, nota:  4.50
NUSP:   111, nota:  6.00
NUSP:   333, nota:  7.00
NUSP:   444, nota:  7.50
NUSP:   222, nota: 10.00
*/