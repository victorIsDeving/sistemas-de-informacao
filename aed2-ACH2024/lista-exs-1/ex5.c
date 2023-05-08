#include "../lista-adjacencia/basics.c"
#include "../matriz-adjacencia/basics.c"
#define V 6

VERTICE* matrizLista(int vertices, int m[vertices][vertices]) {
    VERTICE* resp = (VERTICE*) malloc(sizeof(VERTICE) * vertices);
    resp = criarGrafoLista(V);

    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            if (m[i][j] != -1) {
                NO* n = (NO*) malloc(sizeof(NO));
                n->adj = j;
                n->peso = m[i][j];
                n->prox = resp[i].inicio;
                resp[i].inicio = n;
            }
        }
    }

    return resp;
}

int main() {
    int m[V][V];
    inicializarMatriz(V, m);

    criarArestasMatriz(0, 1, 10, V, m);
    criarArestasMatriz(0, 0, 10, V, m);
    criarArestasMatriz(0, 4, 10, V, m);
    criarArestasMatriz(1, 2, 10, V, m);
    criarArestasMatriz(2, 2, 10, V, m);
    criarArestasMatriz(2, 4, 10, V, m);
    criarArestasMatriz(3, 3, 10, V, m);
    criarArestasMatriz(4, 3, 10, V, m);
    criarArestasMatriz(5, 4, 10, V, m);
    criarArestasMatriz(5, 5, 10, V, m);

    printf("Grafo Matrix:\n");
    imprimeMatriz(V, m);  

    VERTICE* g = (VERTICE*) malloc(sizeof(VERTICE) * V);
    g = matrizLista(V, m);
    printf("Grafo Lista:\n");
    imprimeLista(g, V);  


    return 1;
}