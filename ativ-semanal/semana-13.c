#include <stdio.h>

typedef struct aux{
  float baseMenor;
  float baseMaior;
  float altura;
} TRAPEZIO;

float areaTrapezio1(TRAPEZIO t1) {

    return ((t1.baseMenor + t1.baseMaior) * t1.altura / 2);
}

float areaTrapezio2(TRAPEZIO* r1) {
    TRAPEZIO aux = *r1;

    return ((aux.baseMenor + aux.baseMaior) * aux.altura / 2);
}


int main() {
  TRAPEZIO trap;
  trap.baseMenor = 3.5;
  trap.baseMaior = 4.5;
  trap.altura = 2.125;
  printf("Area do trapezio: %.2f\n",areaTrapezio1(trap));
  printf("Area do trapezio: %.2f\n\n",areaTrapezio2(&trap));

  TRAPEZIO trap2;
  trap2.baseMenor = 3.5 * 2;
  trap2.baseMaior = 4.5 * 2;
  trap2.altura = 2.125 * 2;
  printf("Area do trapezio: %.2f\n",areaTrapezio1(trap2));
  printf("Area do trapezio: %.2f\n\n",areaTrapezio2(&trap2));

  TRAPEZIO trap3;
  trap3.baseMenor = 3.5 / 2;
  trap3.baseMaior = 4.5 / 2;
  trap3.altura = 2.125 / 2;
  printf("Area do trapezio: %.2f\n",areaTrapezio1(trap3));
  printf("Area do trapezio: %.2f\n\n",areaTrapezio2(&trap3));
  
  return 0;
}


/* SAIDA
Area do trapezio: 8.50
Area do trapezio: 8.50
*/