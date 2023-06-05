#include <stdio.h>
#include <stdlib.h>
#include "./basics.c"

int main() {
    int nusp = 77777;

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

    // Criar a tabela de índices primários
    TABELA tabela[V];
    REGISTRO r;
    int prox = 0;
    fseek(arq1, 0, SEEK_SET);
    while (fread(&r, sizeof(REGISTRO), 1, arq1) == 1) {
        inserirIndice(tabela, r.NroUSP, prox);
        prox++;
    }

    int indice = buscarEndereco(tabela, nusp, V);
    if (indice == -1) {
        printf("\nRegistro %i nao existe no arquivo\n", nusp);
    } else {
        printf("\nRegistro encontrado: %i\n", indice);
        fseek(arq1, sizeof(REGISTRO) * indice, SEEK_SET);
        fread(&r, sizeof(REGISTRO), 1, arq1);
        printRegistro(&r);
    }

    fclose(arq1);

    return 1;
}