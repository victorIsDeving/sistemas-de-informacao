#include "../lista-adjacencia/basics.c"
#define V 6
#define BOOL int
#define true 1
#define false 0

//Descosidera loops
// para considerar loops basta comentar o if da linha 15
BOOL arvoreEnraizada(int vertices, VERTICE* g) {
    for(int i = 0; i < vertices; i++) {
        int grau = 0;
        for(int j = 0; j < vertices; j++) {
            NO* n = (NO*) malloc(sizeof(NO));
            n = g[j].inicio;
            if(i != j) {
                while(n) {
                    if (n->adj == i) {
                        grau++;
                    }
                    n = n->prox;
                }
            }
        }
        if (grau == 0) {
            return true;
        }
    }

    return false;
}

int main() {
    VERTICE* g1 = (VERTICE*) malloc(sizeof(VERTICE) * V);
    g1 = criarGrafoLista(V);
    criarArestasLista(g1, 0, 1, 1);
    criarArestasLista(g1, 0, 0, 1);
    criarArestasLista(g1, 0, 4, 1);
    criarArestasLista(g1, 1, 2, 1);
    criarArestasLista(g1, 2, 2, 1);
    criarArestasLista(g1, 2, 5, 1);
    criarArestasLista(g1, 3, 3, 1);
    criarArestasLista(g1, 4, 3, 1);
    criarArestasLista(g1, 5, 4, 1);
    criarArestasLista(g1, 5, 5, 1);
    printf("Grafo g1 Lista:\n");
    imprimeLista(g1, V);

    VERTICE* g2 = (VERTICE*) malloc(sizeof(VERTICE) * V);
    g2 = criarGrafoLista(V);
    criarArestasLista(g2, 0, 1, 1);
    criarArestasLista(g2, 0, 4, 1);
    criarArestasLista(g2, 1, 2, 1);
    criarArestasLista(g2, 1, 0, 1);
    criarArestasLista(g2, 2, 2, 1);
    criarArestasLista(g2, 2, 5, 1);
    criarArestasLista(g2, 3, 3, 1);
    criarArestasLista(g2, 4, 3, 1);
    criarArestasLista(g2, 5, 4, 1);
    criarArestasLista(g2, 5, 5, 1);
    printf("Grafo g2 Lista:\n");
    imprimeLista(g2, V);  

    if (arvoreEnraizada(V, g1)) {
        printf("O Grafo g1 eh enraizado!\n");
    } else {
        printf("O Grafo g1 nao eh enraizado!\n");
    }

    if (arvoreEnraizada(V, g2)) {
        printf("O Grafo g2 eh enraizado!\n");
    } else {
        printf("O Grafo g2 nao eh enraizado!\n");
    }

    return 1;
}