#include <stdio.h>
#include "./basics.c"

int main() {
    REGISTRO r1;
    r1.NroUSP = 11111;
    r1.curso = 0;
    r1.estado = 10;
    r1.idade = 20;
    r1.valido = true;
    REGISTRO r2;
    r2.NroUSP = 33333;
    r2.curso = 0;
    r2.estado = 13;
    r2.idade = 23;
    r2.valido = true;
    REGISTRO r3;
    r3.NroUSP = 22222;
    r3.curso = 1;
    r3.estado = 12;
    r3.idade = 22;
    r3.valido = true;

    /* Create the file */
    FILE *fh = fopen ("origem.bin", "wb");
    if (fh != NULL) {
        fwrite (&r1, sizeof (REGISTRO), 1, fh);
        fwrite (&r2, sizeof (REGISTRO), 1, fh);
        fwrite (&r3, sizeof (REGISTRO), 1, fh);
        fclose (fh);
    }

    return 0;
}
