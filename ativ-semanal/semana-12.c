#include <stdio.h>
#include <stdlib.h>

int palindromo(char* texto, int n) {

    int contador = 0;

    for (int i = 0; i <= (n/2 - 1); i++) {
        if (texto[i] == texto[n-(1 + i)]) {
            contador++;
        }
    }

    if (contador == n/2 ) {
        return 1;
    } else {
        return 0;
    }

}

int main() {
  char* p1 = (char*) malloc(sizeof(char)*5);
  p1[0] = 'r';
  p1[1] = 'a';
  p1[2] = 'd';
  p1[3] = 'a';
  p1[4] = 'r';

  if(palindromo(p1,5)){
    printf("radar eh palindromo!\n");
  }else{
    printf("radar nao eh palindromo!\n");
  }

  if(palindromo(p1,4)){
    printf("rada eh palindromo!\n");
  }else{
    printf("rada nao eh palindromo!\n");
  }

  printf("\n");
  
  char* p2 = (char*) malloc(sizeof(char)*4);
  p2[0] = 'o';
  p2[1] = 's';
  p2[2] = 's';
  p2[3] = 'o';

  if(palindromo(p2,4)){
    printf("osso eh palindromo!\n");
  }else{
    printf("osso nao eh palindromo!\n");
  }

  if(palindromo(p2,3)){
    printf("oss eh palindromo!\n");
  }else{
    printf("oss nao eh palindromo!\n");
  }

  printf("\n");
  
  char* p3 = (char*) malloc(sizeof(char)*3);
  p3[0] = 'o';
  p3[1] = 'v';
  p3[2] = 'o';

  if(palindromo(p3,3)){
    printf("ovo eh palindromo!\n");
  }else{
    printf("ovo nao eh palindromo!\n");
  }

  if(palindromo(p3,2)){
    printf("ov eh palindromo!\n");
  }else{
    printf("ov nao eh palindromo!\n");
  }
  
  return 0;
}


/* SAIDA
radar eh palindromo!
rada nao eh palindromo!
*/