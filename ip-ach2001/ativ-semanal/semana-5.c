#include <stdio.h>

void calculoDoValorDePi(int iteracoes){
    double meuPI = 4; // valor inicial de pi ("primeira iteracao")
    int sinal = -1;
    double divisor = 3;

    for (int i=2;i<=iteracoes;i++){
      meuPI += sinal * 4.0/divisor; // atualiza o valor de pi
      divisor += 2; // incrementa o valor do divisor
      sinal *= -1; // inverte o sinal da variavel sinal
    }
    
    printf("(%i) pi: %f\n", iteracoes, meuPI);
}

int main() {

    calculoDoValorDePi(1);
    calculoDoValorDePi(2);
    calculoDoValorDePi(3);
    calculoDoValorDePi(4);
    calculoDoValorDePi(5);
    calculoDoValorDePi(10);
    calculoDoValorDePi(1000);

    return 0;
}