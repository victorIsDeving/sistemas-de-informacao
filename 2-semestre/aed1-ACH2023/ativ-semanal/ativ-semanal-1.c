#include <stdio.h>

// int main() {
//     int nusp = 8942937;
//     printf("Imprimindo inteiro: %i\n", nusp);
//     printf("Imprimindo numero: %d\n", nusp);
//     printf("Imprimindo float (com cast): %f\n", (float)nusp);
//     printf("Imprimindo quociente: %i\n", nusp/2);
//     printf("Imprimindo resto: %d\n", nusp%2);
//     printf("Imprimindo quadrado: %d\n", nusp*nusp);
//     return 0;
// }

int main() {
    int x = 7;
    int y = 13;
    int* z = &x;
    printf("x: %i   y: %i   z: %p\n", x, y, z);
    printf("&x: %p   &y: %p   &z: %p\n", &x, &y, &z);
    *z = x + y;
    printf("Novo valor de x: %i\n", x);    
    return 0;
}