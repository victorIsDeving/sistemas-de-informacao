#include <stdio.h>

void main() {
    int a, b, c, d, i;
    a = 0;
    b = 0;
    c = 1;
    d = 3;
    i = 0;
    int l = 5;
    int v[l];

    for (int j = 0; j <= l; j++) {
        v[j] = 1;
    }
    
    for (i; i < l; i++) {
        v[i] = v[i] + 1;
        if ( v[i] != 10 ) {
            a++;
        }
        b = c * 2 + d;
    }

    printf("a = %i\n", a);
    printf("b = %i\n", b);
    printf("c = %i\n", c);
    printf("d = %i\n", d);
    printf("i = %i\n", i);
    int k = 15;
    printf("v[%i] = %i\n", k, v[k]);
}