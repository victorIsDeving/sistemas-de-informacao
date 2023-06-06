#include <stdio.h>
#include <stdlib.h>
#include "./basics.c"

int main() {
    int cursoAlvo = 0;
    int cursoNovo = 5;

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

    // Criar a tabela de índices primários
    TABELA tabela[V];
    REGISTRO r;
    int prox = 0;
    fseek(arq1, 0, SEEK_SET);
    while (fread(&r, sizeof(REGISTRO), 1, arq1) == 1) {
        inserirIndice(tabela, r.curso, prox);
        prox++;
    }
    
    // Escrever no arquivo de destino os registros
    for (int i = 0; i < prox; i++) {
        fseek(arq1, sizeof(REGISTRO) * tabela[i].end, SEEK_SET);
        fread(&r, sizeof(REGISTRO), 1, arq1);
        if (tabela[i].chave == cursoAlvo) {
            r.curso = cursoNovo;
        }
        fwrite(&r, sizeof(REGISTRO), 1, arq2);
    }

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