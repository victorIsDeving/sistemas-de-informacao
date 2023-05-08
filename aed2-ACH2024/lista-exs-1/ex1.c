#include "../lista-adjacencia/basics.c"
#define V 6

int detectLoop(VERTICE* g, int vertices) {
    int counter = 0;
    for(int i = 0; i < vertices; i++) {
        NO* n = (NO*) malloc(sizeof(NO));
        n = g[i].inicio;
        while(n) {
            if(n->adj == i) {
                counter++;
            }
            n = n->prox;
        }
    }

    return counter;
}

void removeLoops(VERTICE* g, int vertices) {
    for(int i = 0; i < vertices; i++) {
        NO* ant = (NO*) malloc(sizeof(NO));
        NO* n = (NO*) malloc(sizeof(NO));
        NO* prox = (NO*) malloc(sizeof(NO));
        ant = NULL;
        n = g[i].inicio;
        prox = g[i].inicio->prox;
        while(n) {
            if(n->adj == i) {
                if (!ant && !prox) {
                    g[i].inicio = NULL;
                    n = NULL;
                } else if (!ant) { //primeiro adjacente é um laço
                    g[i].inicio = prox;
                    n = prox;
                    prox = prox->prox;
                } else if (!prox) { //último adjacente é um laço
                    ant->prox = prox;
                    n = prox;
                } else { //adjacente tá no meio da fila
                    ant->prox = prox;
                    n = prox;
                    prox = prox->prox;
                }
            } else {
                if (!prox) {
                    ant = n;
                    n = prox;
                } else {
                    ant = n;
                    n = prox;
                    prox = prox->prox;
                }
            }
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

    int loops = detectLoop(g, V);

    printf("Grafo:\n");
    imprime(g, V);
    printf("O grafo possui %i loops\n", loops);

    removeLoops(g, V);

    loops = detectLoop(g, V);
    printf("Grafo:\n");
    imprime(g, V);
    printf("O grafo possui %i loops\n", loops);    

    return 1;
}