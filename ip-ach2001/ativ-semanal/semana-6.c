#include <stdio.h>

int cor (int identificador) {

    switch (identificador) {
        case 1: 
            return printf("verde\n");
            break;
        case 2: 
            return printf("amarelo\n");
            break;
        case 3: 
            return printf("azul\n");
            break;
        case 4: 
            return printf("branco\n");
            break;
        default: printf("Valor nao identificado\n");
    }

    return 0;
};

void conjecturaDeCollatz(int n){
    printf("Imprimindo sequencia iniciando em %i\n", n);
    while (n>1){
        if (n % 2 == 0) n = n/2;
        else n = 3*n + 1;
        printf("%i\n",n);
    }
}

int main() {
    // meu número usp é 8942937
    
    conjecturaDeCollatz(38);

    return 0;
};