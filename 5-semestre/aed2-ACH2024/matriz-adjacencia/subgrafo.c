#include "./basics.c"
#define V 3

//Função que verifica se um grafo é subgrafo de outro
//se m2 é subgrafo de m1
int subgrafo(int vertices, int m1[vertices][vertices], int m2[vertices][vertices]) {
    for(int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if(m2[i][j] != m1[i][j] && m2[i][j] != -1) {
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    //grafos
    int m1[V][V];
    inicializarMatriz(V, m1);
    int m2[V][V];
    inicializarMatriz(V, m2);
    int m3[V][V];
    inicializarMatriz(V, m3);

    //Montar Grafo 1
    criarArestas(0, 0, 40, V, m1);
    criarArestas(0, 1, 10, V, m1);
    criarArestas(1, 2, 20, V, m1);
    criarArestas(2, 0, 30, V, m1);
    printf("Grafo 1\n");
    imprime(V, m1);

    //Montar Grafo 2
    criarArestas(0, 1, 10, V, m2);
    criarArestas(1, 2, 20, V, m2);
    printf("Grafo 2\n");
    imprime(V, m2);

    //Montar Grafo 3
    criarArestas(2, 0, 15, V, m3);
    criarArestas(2, 1, 15, V, m3);
    printf("Grafo 3\n");
    imprime(V, m3);

    printf("Verificando subgrafos:\n");
    if (subgrafo(V, m1, m2)) {
        printf("G2 eh subgrafo de G1!\n");
    } else {
        printf("G2 nao eh subgrafo de G1.\n");
    }
    if (subgrafo(V, m1, m3)) {
        printf("G3 eh subgrafo de G1!\n");
    } else {
        printf("G3 nao eh subgrafo de G1.\n");
    }

    return 1;
}