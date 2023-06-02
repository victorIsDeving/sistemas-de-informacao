#include <stdio.h>
#include <stdlib.h>
#include "./basics.c"

void retornaRegistro(FILE* origem, FILE* destino, REGISTRO* novo) {
    int exists = false;
    REGISTRO r;
    fseek(origem, 0, SEEK_SET);
    while (fread(&r, sizeof(REGISTRO), 1, origem) == 1) {
        if (r.NroUSP == novo->NroUSP && r.valido == true) {
            exists = true;
        }
        fwrite(&r, sizeof(REGISTRO), 1, destino);
    }

    if (!exists) {
        fwrite(novo, sizeof(REGISTRO), 1, destino);
    }
}

int main() {
    REGISTRO r;
    r.NroUSP = 44444;
    r.curso = 2;
    r.estado = 14;
    r.idade = 24;
    r.valido = true;

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

    retornaRegistro(arq1, arq2, &r);
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