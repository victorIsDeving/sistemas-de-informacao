#include <stdio.h>

int main () {
    int x = 6;

    if ( ( ( (20-x) > 5 ) && ((4/x) == 1) ) || ((16-x) > 10) ) printf("passou\n");
        else printf("nao passou\n");

    return 0;
}

/**
 * Precedência dos operadores em ordem decrescente
 * 
 * 1    !
 * 2    * / %
 * 3    + -
 * 4    == != > < >= <=
 * 5    &&
 * 6    ||
 * 7    =
 * 
*/
 