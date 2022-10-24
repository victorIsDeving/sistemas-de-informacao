#include <stdio.h>

void main() {
    int a = 1;
    int b = 5;
    int c = 0;
    int d = 0;
    int v[10];
    v[10] = 20;
    
    if (a > c) {
        b = b + 5;
        v[10] = b;
    } else {
        d = a * b * 2;
        v[10] = v[10] / d;
    }

    printf("a = %i\n", a);
    printf("b = %i\n", b);
    printf("c = %i\n", c);
    printf("d = %i\n", d);
    printf("v[10] = %i", v[10]);
}