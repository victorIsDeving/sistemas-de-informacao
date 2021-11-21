/**
 * Programa para calcular a área de uma casa com piscina, conforme
 * projeto específico.
 * No conteÃºdo da aula de hoje vários condicionais são adicionados ao código.
*/

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define false 0
#define true 1

typedef int bool; // usar o tipo int como booleano para facilitar a leitura do código
int valorM2 = 1500;

void areaCasa(float lateral, float cquarto){
   float areaq;
   float areas;
   float areat;
   if ( lateral<0 || cquarto<0 ) printf("Erro: lateral da sala < 0\n");
   else {
        printf("Programa para calculo da area da casa\n");
        areas = lateral*lateral;
        printf("A area da sala eh %f\n", areas);
        areaq = cquarto*(lateral/2);
        printf("A area do quarto eh %f\n", areaq);
        printf("A area do banheiro eh %f\n", areaq);
        areat = areas + 2*areaq;
        printf("A area total eh %f\n", areat);
    }
}


double areaPiscina(double raio){
   if (raio >= 0) return M_PI * raio*raio;
   return -1;
}

double valor(double area) {
   if (area >= 0) {
      return(valorM2*area);
   }
   return(-1);
}

int main() {
   double preco;
   bool valorOK = false;

   preco = valor(20);
   valorOK = preco >= 0;

   areaCasa(10,15);

   printf("O valor da construcao ");
   if (valorOK) printf("eh %f\n",preco);
   else printf("não foi obtido: area negativa\n");

   return 0;
}
