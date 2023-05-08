#include "../lista-adjacencia/basics.c"
#include "../matriz-adjacencia/basics.c"
#define V 3

//Função que verifica se um grafo é subgrafo de outro
//se m (grafo em matriz de adjacência) 
// é subgrafo de g (grafo em lista de adjacência)
int subgrafo(VERTICE* g, int vertices,  int m[vertices][vertices]) {
    int i;
    for(i = 0; i < vertices; i++) {
        NO* p = g[i].inicio;
        while(p) {
            if(m[i][p->adj] != p->peso && m[i][p->adj] != -1) {
                return 0;
            }
            p = p->prox;
        }
    }
    return 1;
}

int main() {
    //grafos
    VERTICE* g1 = criarGrafoLista(3);
    int m2[V][V];
    inicializarMatriz(V, m2);
    int m3[V][V];
    inicializarMatriz(V, m3);

    //Montar Grafo 1
    criarArestasLista(g1, 0, 0, 40);
    criarArestasLista(g1, 0, 1, 10);
    criarArestasLista(g1, 1, 2, 20);
    criarArestasLista(g1, 2, 0, 30);
    printf("Grafo 1\n");
    imprimeLista(g1, V);

    //Montar Grafo 2
    criarArestasMatriz(0, 1, 10, V, m2);
    criarArestasMatriz(1, 2, 20, V, m2);
    printf("Grafo 2\n");
    imprimeMatriz(V, m2);

    //Montar Grafo 3
    criarArestasMatriz(2, 0, 15, V, m3);
    criarArestasMatriz(2, 1, 15, V, m3);
    printf("Grafo 3\n");
    imprimeMatriz(V, m3);

    printf("Verificando subgrafos:\n");
    if (subgrafo(g1, V, m2)) {
        printf("M2 eh subgrafo de G1!\n");
    } else {
        printf("M2 nao eh subgrafo de G1.\n");
    }
    if (subgrafo(g1, V, m3)) {
        printf("M3 eh subgrafo de G1!\n");
    } else {
        printf("M3 nao eh subgrafo de G1.\n");
    }

    return 1;
}