#include <stdio.h>

double areaTrapezio(double baseMaior, double baseMenor, double altura) {
    return ((baseMaior + baseMenor) * altura) / 2;
}

double areaRetangulo(double base, double altura){
    double area = areaTrapezio(base,base,altura);
    return area;
}

double areaQuadrado(double lado) {
    return (areaRetangulo(lado, lado));
}

int main() {
    double areaTrap = areaTrapezio(4, 5, 6);
    double areaRet = areaRetangulo(11, 27);
    double areaQuad = areaQuadrado(5);

    printf("A area do trapezio eh %.2f!\n", areaTrap);
    printf("Area do retangulo: %.2f\n", areaRet);
    printf("A area do quadrado eh %.2f!\n", areaQuad);

    return 0;
}