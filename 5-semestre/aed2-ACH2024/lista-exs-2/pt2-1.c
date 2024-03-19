// For testing
// gcc pt2-1.c -o pt2-1 && ./pt2-1

#include <stdio.h>
#include <stdlib.h>
#include "./basics.c"

int main() {
    // Resetar o bin para partir sempre do mesmo ponto
    createBin();

    REGISTRO rNovo;
    rNovo.NroUSP = 77777;
    rNovo.curso = 1;
    rNovo.estado = 10;
    rNovo.idade = 20;
    rNovo.valido = true;

    // cria ponteiro para arquivo
    FILE* fileRead;
    // abre arquivo no modo de leitura
    fileRead = fopen("origem.bin", "rb");
    // verifica se o arquivo abre com sucesso
    // tratativa de erro
    if (fileRead == NULL) {
        printf("Arquivo não abriu.\n");
        exit(0);
    }
    printf("\nARQUIVO ORIGINAL\n");
    printFile(fileRead);

    // Criar a tabela de índices primários
    TABELA tabela[V];
    REGISTRO r;
    int prox = 0;
    fseek(fileRead, 0, SEEK_SET);
    while (fread(&r, sizeof(REGISTRO), 1, fileRead) == 1) {
        inserirIndice(tabela, r.NroUSP, prox);
        prox++;
    }
    
    fclose(fileRead);

    // Aqui a resolução que importa desse exercício
    FILE* fileWrite;
    // abre arquivo no modo de append binary
    fileWrite = fopen("origem.bin", "ab");
    if (fileWrite == NULL) {
        printf("Arquivo não abriu.\n");
        exit(0);
    }

    if (buscarEndereco(tabela, rNovo.NroUSP, V) == -1) {
        fseek(fileWrite, 0, SEEK_END);
        fwrite(&rNovo, sizeof(REGISTRO), 1, fileWrite);
    } else {
        printf("\nRegistro %i ja existe no arquivo\n", rNovo.NroUSP);
    }

    fclose(fileWrite);

    // Leitura para ver se o arquivo resultado está certo
    FILE* f = fopen ("origem.bin", "rb");
    if (f != NULL) {
        printf("\nARQUIVO FINAL\n");
        printFile(f);
        fclose (f);
    }

    return 1;
}