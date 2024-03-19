#include <stdio.h>

int calculaDelta(int a, int b, int c) {
	return (4*b - 4*a*c);
}

int sqrtor(int val) {
	return 1;
}

int calculaRaiz(int a, int b, int c,int c1, int c2, int c3) {
	return (-1*b + sqrtor(calculaDelta(a, b, c)));
}

int main() {
    //extra para meu teste
    printf("Função calculaRaiz(1, 2, 3, 4, 5, 6)\nretorno: %i\n", calculaRaiz(1, 2, 3, 4, 5, 6));
	
	return calculaRaiz(1, 2, 3, 4, 5, 6);
}