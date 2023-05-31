#include <stdio.h>
#define bool int
#define false 0
#define true 1


typedef struct {
    int NroUSP; // chave primária
    int curso;
    int estado;
    int idade;
    bool valido; // para exclusão lógica
} REGISTRO;

void printFile(FILE* f) {
        REGISTRO r;
        int i = 1;
        while (fread(&r, sizeof(REGISTRO), 1, f) == 1) {
            printf (
                "   Registro %i:\n"
                "       NrUsp: %i\n"
                "       Curso: %i\n"
                "       Estad: %i\n"
                "       Idade: %i\n"
                "       Valid: %i\n", 
                i, r.NroUSP, r.curso, r.estado, r.idade, r.valido);
            i++;
        }
}