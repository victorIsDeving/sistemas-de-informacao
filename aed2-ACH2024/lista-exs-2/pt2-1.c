#include <stdio.h>
#include <stdlib.h>
#include "./basics.c"

// Função principal de ordenação
int buscarEndereco(TABELA tabela[], int nusp, int size) {
    for (int i = 0; i < V; i++) {
        if (tabela[i].chave == nusp) {
            return i;
        }
    }

    return -1;
}

int main() {
    REGISTRO rNovo;
    rNovo.NroUSP = 66666;
    rNovo.curso = 1;
    rNovo.estado = 10;
    rNovo.idade = 20;
    rNovo.valido = true;

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
        inserirIndice(tabela, r.NroUSP, prox);
        prox++;
    }
    
    // Escrever no arquivo de destino os registros
    for (int i = 0; i < prox; i++) {
        // Colocar ponteiro do arquivo origem no registro
        // para ler registro a registro na ordem
        fseek(arq1, sizeof(REGISTRO) * tabela[i].end, SEEK_SET);
        fread(&r, sizeof(REGISTRO), 1, arq1);
        fwrite(&r, sizeof(REGISTRO), 1, arq2);
    }

    if (buscarEndereco(tabela, rNovo.NroUSP, V) == -1) {
        fwrite(&rNovo, sizeof(REGISTRO), 1, arq2);
    } else {
        printf("\nRegistro %i ja existe no arquivo\n", rNovo.NroUSP);
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