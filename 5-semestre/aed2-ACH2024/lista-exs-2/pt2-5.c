//Teste
// gcc pt2-5.c -o pt2-5 && ./pt2-5

#include <stdio.h>
#include <stdlib.h>
#include "./basics.c"

int main() {
    createBin();

    int nuspAlvo = 22222;
    int nuspNovo = 88888;

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

    //Visualizar o arquivo ORIGINAL
    printf("ARQUIVO ORIGINAL\n");
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

    fclose(arq1);

    FILE* arq2;
    arq2 = fopen("origem.bin", "rb+");
    if (arq2 == NULL) {
        printf("Arquivo não abriu.\n");
        exit(0);
    }
    
    // Verificar os registros pela tabela de indices primários
    int indice = buscarEndereco(tabela, nuspAlvo, V);
    if (indice == -1) {
        printf("\nRegistro %i nao existe no arquivo\n", nuspAlvo);
    } else {
        printf("\nRegistro encontrado na posicao %i\n", indice);
        fseek(arq2, sizeof(REGISTRO) * indice, SEEK_SET);
        fread(&r, sizeof(REGISTRO), 1, arq2);
        fseek(arq2, -sizeof(REGISTRO), SEEK_CUR);
        r.NroUSP = nuspNovo;
        fwrite(&r, sizeof(REGISTRO), 1, arq2);
    }

    fclose(arq2);

    // Leitura para ver se o arquivo destino está certo
    FILE* f = fopen ("origem.bin", "rb");
    if (f != NULL) {
        printf("\nARQUIVO FINAL\n");
        printFile(f);
        fclose (f);
    }

    return 1;
}