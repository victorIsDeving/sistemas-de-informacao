#include <stdio.h>

void main() {
    int A = 0; //$s1
    int B = 0; //$s2
    int i = 0; //$t1
    int temp = 0;  //$t2

    while ( i < 0) {
        i--;
        B += 2;
    }

    printf("B = %i\ni = %i", B, i);
}