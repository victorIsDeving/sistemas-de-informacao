#include "../lista-adjacencia/basics.c"
#define V 6
#define BOOL int
#define true 1
#define false 0

//Retira do grafo as arestas com custo maior que o especificado
// Retorna um grafo só com as arestas retiradas
VERTICE* retiraCustoMaior(int vertices, VERTICE* g, int c) {
    VERTICE* resp = (VERTICE*) malloc(sizeof(VERTICE) * vertices);
    resp = criarGrafoLista(V);
    for(int i = 0; i < vertices; i++) {
        NO* ant = (NO*) malloc(sizeof(NO));
        NO* n = (NO*) malloc(sizeof(NO));
        NO* prox = (NO*) malloc(sizeof(NO));
        ant = NULL;
        n = g[i].inicio;
        prox = g[i].inicio->prox;
        while(n) {
            if(n->peso > c) { //caso alvo
                n->prox = resp[i].inicio;
                resp[i].inicio = n;
                if (!ant && !prox) { //primeiro adjacente mas só tem um
                    g[i].inicio = NULL;
                    n = NULL;
                } else if (!ant) { //primeiro adjacente
                    g[i].inicio = prox;
                    n = prox;
                    prox = prox->prox;
                } else if (!prox) { //último adjacente
                    ant->prox = prox;
                    n = prox;
                } else { //adjacente tá no meio da fila
                    ant->prox = prox;
                    n = prox;
                    prox = prox->prox;
                }
            } else {
                if (!prox) { //evitar o segmentation fault no último elemento da fila
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
    return resp;
}

int main() {
    VERTICE* g1 = (VERTICE*) malloc(sizeof(VERTICE) * V);
    g1 = criarGrafoLista(V);
    criarArestasLista(g1, 0, 1, 30);
    criarArestasLista(g1, 1, 0, 30);
    criarArestasLista(g1, 0, 4, 15);
    criarArestasLista(g1, 4, 0, 15);
    criarArestasLista(g1, 1, 2, 30);
    criarArestasLista(g1, 2, 1, 30);
    criarArestasLista(g1, 2, 5, 20);
    criarArestasLista(g1, 5, 2, 20);
    criarArestasLista(g1, 4, 3, 25);
    criarArestasLista(g1, 3, 4, 25);
    criarArestasLista(g1, 5, 4, 30);
    criarArestasLista(g1, 4, 5, 30);
    printf("Grafo g1 Lista:\n");
    imprimeLista(g1, V);

    VERTICE* g2 = (VERTICE*) malloc(sizeof(VERTICE) * V);
    g2 = retiraCustoMaior(V, g1, 26);
    printf("Grafo g2 Lista:\n");
    imprimeLista(g2, V);
    printf("Grafo g1 Lista:\n");
    imprimeLista(g1, V);
    
    return 1;
}