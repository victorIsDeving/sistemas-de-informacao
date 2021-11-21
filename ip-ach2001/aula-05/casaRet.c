
/**
 * Programa para calcular a área de uma casa com 3 cômodos:
 * uma sala de 10x10 cada
 * um quarto e um banheiro 5x7m cada
*/

#include <stdio.h>

// stdio é uma lib com funções para usar

int main() {

    printf("Programa para o cálculo da área de uma casa\n");
    printf("A área da sala é %i metros quadrados\n", 10*10);
    printf("A área do quarto é %i metros quadrados\n", 5*7);
    printf("A área do banheiro é %i metros quadrados\n", 5*7);
    printf("A área total é de %i metros quadrados\n", 10*10 + 5*7*2);

    return 0;
}