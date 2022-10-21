#include <stdio.h>

void main() {
    int a = 2;
    int b = 2;
    int c = 0;
    int i = 0;
    for (i; i != 10; i++) {
        c = a + b;
    }

    printf("a = %i\nb = %i\nc = %i\ni = %i", a, b, c, i);
}