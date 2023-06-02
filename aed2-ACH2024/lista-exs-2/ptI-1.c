#include <stdio.h>
#include <stdlib.h>
#include "./basics.c"

void copiaArquivo(FILE* origem, FILE* destino) {
    REGISTRO r;
    fseek(origem, 0, SEEK_SET);
    while (fread(&r, sizeof(REGISTRO), 1, origem) == 1) {
        fwrite(&r, sizeof(REGISTRO), 1, destino);
    }
}

int main() {
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

    copiaArquivo(arq1, arq2);
    fclose(arq1);
    fclose(arq2);

    // Leitura para ver se o arquivo destino está certo
    FILE* f = fopen ("destino.bin", "rb");
    if (f != NULL) {
        printf("ARQUIVO DE DESTINO\n");
        printFile(f);
        fclose (f);
    }

    return 1;
}