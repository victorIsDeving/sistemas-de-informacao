// Teste
// gcc pt2-3.c -o pt2-3 && ./pt2-3

#include <stdio.h>
#include <stdlib.h>
#include "./basics.c"

int main() {
    createBin();
    int curso = 0;

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

    //Visualizar o arquivo original
    printf("ARQUIVO ORIGINAL\n");
    printFile(arq1);

    // Criar a tabela de índices primários
    TABELA tabela[V];
    REGISTRO r;
    int prox = 0;
    fseek(arq1, 0, SEEK_SET);
    while (fread(&r, sizeof(REGISTRO), 1, arq1) == 1) {
        inserirIndice(tabela, r.curso, prox);
        prox++;
    }

    fclose(arq1);

    // Aqui a resolução que importa desse exercício
    FILE* fileWrite;
    // abre arquivo no modo de append binary
    fileWrite = fopen("origem.bin", "rb+");
    if (fileWrite == NULL) {
        printf("Arquivo não abriu.\n");
        exit(0);
    }
    
    // Exclusão lógica
    for (int i = 0; i < prox; i++) {
        if (tabela[i].chave == curso) {
            int indice = excluirIndice(tabela, curso, V);
            tabela[i].chave = -1;
            tabela[i].end = -1;
            fseek(fileWrite, sizeof(REGISTRO) * indice, SEEK_SET);
            fread(&r, sizeof(REGISTRO), 1, fileWrite);
            r.valido = -1;
            fseek(fileWrite, -sizeof(REGISTRO), SEEK_CUR);
            fwrite(&r, sizeof(REGISTRO), 1, fileWrite);
        }
    }

    fclose(fileWrite);

    // Leitura para ver se o arquivo destino está certo
    FILE* f = fopen ("origem.bin", "rb");
    if (f != NULL) {
        printf("\nARQUIVO FINAL\n");
        printFile(arq1);
        fclose (f);
    }

    return 1;
}