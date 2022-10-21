#include <stdio.h>

void main() {
    int a = 2;
    int b = 2;
    int c = 0;
    while (a != 0) {
        c = a + b;
        a--;
    }

    printf("a = %i\nb = %i\nc = %i", a, b, c);
}