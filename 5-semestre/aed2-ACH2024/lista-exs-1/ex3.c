#include "../lista-adjacencia/basics.c"
#define V 6

void emptyGraph(VERTICE* g, int vertices) {
    for(int i = 0; i < vertices; i++) {
        NO* n = (NO*) malloc(sizeof(NO));
        n = g[i].inicio;
        while(n) {
            g[i].inicio = n->prox;
            free(n);
            n = g[i].inicio;
        }
    }
}

int main() {
    VERTICE* g = (VERTICE*) malloc(sizeof(VERTICE) * V);
    g = criarGrafo(V);

    criarArestas(g, 0, 1, 1);
    criarArestas(g, 0, 0, 1);
    criarArestas(g, 0, 4, 1);
    criarArestas(g, 1, 2, 1);
    criarArestas(g, 2, 2, 1);
    criarArestas(g, 2, 4, 1);
    criarArestas(g, 3, 3, 1);
    criarArestas(g, 4, 3, 1);
    criarArestas(g, 5, 4, 1);
    criarArestas(g, 5, 5, 1);

    printf("Grafo:\n");
    imprime(g, V);

    emptyGraph(g, V);

    printf("Grafo:\n");
    imprime(g, V); 

    return 1;
}