/**
 * Função que troca o valor de variáveis usando ponteiros
*/

#include <stdio.h>

void troca (int x, int y) { // essa função não realiza a troca dos valores como o esperado
    int auxiliar = x;
    x = y;
    y = auxiliar;
}

// funcção que troca os valores da variável com o uso de ponteiros
void troca1 (int *x, int *y) {
    /**
     * int *x -> recebe um endereço de variável e define como x
    */

    int auxiliar = *x;
    /**
     * como x é um ponteiro (tem o endereço de uma variável),
     * o asterisco acessa o valor guardado no endereço guardado em x e 
     * vai definir a variável auxiliar como o valor guardado no endereço para o qual x aponta
    */
    
    *x = *y;
    /**
     * o valor guardado no endereço apontado por x
     * =
     * o valor guardado no endereço apontado por y
     * ou seja, no endereço guardado por x, agora tem o valor de y
    */

    *y = auxiliar;
    /**
     * coloca o valor da variável auxiliar no endereço apontado por y
     * ou seja, agora y tem o valor que era de x
    */
}

int main () {
    int a, b;
    a = 5;
    b = 3;

    troca(a, b);
    printf("a=%d\nb=%d\n\n", a, b); // não troca os valores

    troca1(&a, &b); // &a -> dá o endereço da variável a
    printf("a=%d\nb=%d\n", a, b); // troca os valores

    return 0;
}