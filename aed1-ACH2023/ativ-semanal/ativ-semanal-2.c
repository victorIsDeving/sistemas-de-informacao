#include <stdlib.h>
#include <stdio.h>

typedef struct aux {

    int id;
    struct aux* mae;
    struct aux* pai;

} PESSOA;

PESSOA* inicializar(int id){

    PESSOA* alocar = (PESSOA*) malloc(sizeof(PESSOA));
    alocar->id = id;
    alocar->mae = NULL;
    alocar->pai = NULL;

    printf("Endereco da pessoa com id %i eh %p\n", alocar->id, alocar);

    return alocar;
}

void registrar(PESSOA* filho, PESSOA* mae, PESSOA* pai){

    filho->mae = mae;
    filho->pai = pai;
  
}

int main(){
  PESSOA* m = inicializar(1);   
  PESSOA* p = inicializar(2);
  PESSOA* f = inicializar(3);

  registrar(f, m, p);
  
  printf("%p %p %p\n", f, f->mae, f->pai);    

  return 0;
}