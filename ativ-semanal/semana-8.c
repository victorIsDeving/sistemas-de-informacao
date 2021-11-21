#include <stdio.h>

int contagem1 (int* valores, int n, int x) {
    int j = 0;

    for(int i=0;i<n;i++) {
        if (valores[i] == x) {
            j++;
        }
    }

    printf("O valor %i se repete %ix no arranjo\n", x, j);

    return 0;
}

int main () {

    int valores[] = {1,2,4,5,7,7,3,3,3,9,4,7,3};
    printf("Endereço/ponteiro do arranjo valores: %p\n",valores);
    int n = 13;
    printf("Existem %i elementos no arranjo\n", n);

    contagem1(valores, n, 4);
    contagem1(valores, n, 7);
    contagem1(valores, n, 3);

    return 0;
}