#include <stdio.h>
#include <stdlib.h>
#include "./basics.c"

//deletar lógico
void mudaCurso(FILE* origem, FILE* destino, int nusp, int novoCurso) {
    int exists = false;
    REGISTRO r;
    fseek(origem, 0, SEEK_SET);
    while (fread(&r, sizeof(REGISTRO), 1, origem) == 1) {
        if (r.NroUSP == nusp && r.valido == true) {
            r.curso = novoCurso;
        }
        fwrite(&r, sizeof(REGISTRO), 1, destino);
    }
}

int main() {
    int nusp = 11111;
    int novoCurso = 5;

    // cria ponteiro para arquivo
    FILE* arq1;
    // abre arquivo no modo de leitura
    arq1 = fopen("origem.bin", "rb");
    // verifica se o arquivo abre com sucesso
    // tratativa de erro
    if (arq1 == NULL) {
        printf("Arquivo não abriu.\n");
        exit(0);
    }

    //Visualizar o arquivo de origem
    printf("ARQUIVO DE ORIGEM\n");
    printFile(arq1);

    FILE* arq2;
    arq2 = fopen("destino.bin", "wb");
    if (arq2 == NULL) {
        printf("Arquivo não abriu.\n");
        exit(0);
    }

    mudaCurso(arq1, arq2, nusp, novoCurso);
    fclose(arq1);
    fclose(arq2);

    // Leitura para ver se o arquivo destino está certo
    FILE* f = fopen ("destino.bin", "rb");
    if (f != NULL) {
        printf("\nARQUIVO DE DESTINO\n");
        printFile(f);
        fclose (f);
    }

    return 1;
}