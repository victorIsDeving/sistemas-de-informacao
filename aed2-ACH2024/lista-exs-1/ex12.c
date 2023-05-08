#include "../lista-adjacencia/basics.c"
#define V 6
#define BOOL int
#define true 1
#define false 0

//Recebe um grafo e retorna um booleano 
// para o caminho entre dois vértices especificados
BOOL caminhoProfundidade(int origem, int destino, VERTICE* g) {
    g[origem].flag = 1;
    BOOL achou = false;
    if(origem == destino) {
        achou = true;
        return achou;
    }
    // printf("%i", origem);
    NO* no = g[origem].inicio;
    while(no) {
        if (g[no->adj].flag == 0) {
            // printf(" -> ");
            achou = caminhoProfundidade(no->adj, destino, g);
            if (achou) {
                return achou;
            }
        }
        no = no->prox;
    }
    g[origem].flag = 2;

    return achou;
}

//Recebe um grafo e retorna um booleano 
// para o caminho entre dois vértices especificados
// e um contador para a quantidade de vértices no caminho
int caminhoProfundidadeTamanho(int origem, int destino, VERTICE* g) {
    g[origem].flag = 1;
    if(origem == destino) {
        return 1;
    }
    // printf("%i", origem);
    NO* no = g[origem].inicio;
    while(no) {
        if (g[no->adj].flag == 0) {
            // printf(" -> ");
            int i = caminhoProfundidadeTamanho(no->adj, destino, g);
            if (i > 0) {
                return i + 1;
            }
        }
        no = no->prox;
    }
    g[origem].flag = 2;

    return 0;
}

int main() {
    VERTICE* g = (VERTICE*) malloc(sizeof(VERTICE) * V);
    g = criarGrafoLista(V);
    criarArestasLista(g, 0, 1, 30);
    criarArestasLista(g, 0, 4, 15);
    criarArestasLista(g, 1, 2, 30);
    criarArestasLista(g, 2, 5, 20);
    criarArestasLista(g, 4, 3, 25);
    criarArestasLista(g, 5, 4, 30);
    printf("Grafo g Lista:\n");
    imprimeLista(g, V);

    int origem = 0;
    int destino = 4;
    int counter;
    zerarFlagsLista(g, V);
    BOOL path = caminhoProfundidade(origem, destino, g);
    zerarFlagsLista(g, V);
    counter = caminhoProfundidadeTamanho(origem, destino, g);
    if(path) {
        printf("Existe um caminho entre %i e %i, com %i nos", origem, destino, counter);
    } else {
        printf("Nao existe um caminho entre %i e %i, com %i nos", origem, destino, counter);
    }
    
    return 1;
}