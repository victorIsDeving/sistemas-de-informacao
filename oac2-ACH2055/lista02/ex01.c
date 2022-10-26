#include <stdio.h>

void main() {
    int i = 0;
    int result = 0;
    int MemArray[100];
    for ( int j = 0; j < 100; j++ ) {
        MemArray[j] = j;
    }

    for ( i; i < 100; i++ ) {
        result = result + MemArray[i];
    }

    printf("i = %i\nresult = %i", i, result);
}