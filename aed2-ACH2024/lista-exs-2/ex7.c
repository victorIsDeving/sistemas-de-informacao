#include <stdio.h>
#include <stdlib.h>
#include "./basics.c"

// Função principal de ordenação
void keySort(FILE* origem, FILE* destino) {
    // Criar a tabela de índices primários
    TABELA tabela[V];

    // Registro para leitura e escrita nos arquivos 
    REGISTRO r;

    // Variável para controle do endereço dos registros
    // no arquivo original
    int prox = 0;

    // Colocar o ponteiro do arquivo no início para leitura
    fseek(origem, 0, SEEK_SET);

    // Ler os registros um a um no arquivo de origem
    // e inserir chave primária e endereço na tabela
    while (fread(&r, sizeof(REGISTRO), 1, origem) == 1) {
        inserirIndice(tabela, r.NroUSP, prox);
        
        // prox é o endereço que será associado ao registro
        // na tabela de índices primários 
        prox++;
    }

    // Ordenar a tabela de índices primários
    quickSort(tabela, 0, 3);

    // Escrever no arquivo de destino os registros ordenados
    for (int i = 0; i < prox; i++) {
        // Colocar ponteiro do arquivo origem no registro
        // para ler registro a registro na ordem
        fseek(origem, sizeof(REGISTRO) * tabela[i].end, SEEK_SET);

        fread(&r, sizeof(REGISTRO), 1, origem);
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

    keySort(arq1, arq2);
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