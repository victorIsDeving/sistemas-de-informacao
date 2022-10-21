#include <stdio.h>

void main() {
    int a = 0;
    int i = 0;
    int v[] = {0,1,2,3,4};
    
    for (i; i < 5; i++) {
        a = a + v[i];
    }

    printf("a = %i\ni = %i", a, i);
}