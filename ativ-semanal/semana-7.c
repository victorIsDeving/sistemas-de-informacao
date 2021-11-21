#include <stdio.h>

int retangulo (int largura, int altura) {

    printf("\n");
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}

int main () {
    retangulo(2, 2);

    retangulo(4, 7);

    retangulo(7, 4);

    return 0;
}