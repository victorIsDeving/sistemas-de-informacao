#include <stdio.h> // lib para funções gerais e úteis
#define _USE_MATH_DEFINES
#include <math.h> // lib para matemática

void areaCasa(double lateral, double compQuarto) { // void -> função sem retorno definido
    float areaQuarto; // aloca o espaço na memória
    float areaSala; // define o tipo de dado da variável
    float areaTotal;

    printf("Programa para o cálculo da área de uma casa\n");

    areaSala = lateral*lateral; // define um valor para o espaço que foi alocado anteriormente
    printf("A área da sala é de %f metros quadrados\n", areaSala);

    areaQuarto = compQuarto * (lateral/2);
    printf("A área do quarto é de %f metros quadrados\n", areaQuarto);
    printf("A área do banheiro é de %f metros quadrados\n", areaQuarto);

    areaTotal = areaSala + 2*areaQuarto;
    printf("A área total é de %f metros quadrados\n", areaTotal);
}

double areaPiscina(double raio) {
    return (M_PI * pow(raio, 2));
}

int main(void) {

    double piscininhaAmo;
    areaCasa(11, 7);

    piscininhaAmo = areaPiscina(2);
    printf("A área da piscina é de %f metros quadrados \n", piscininhaAmo);

    return 0;
}