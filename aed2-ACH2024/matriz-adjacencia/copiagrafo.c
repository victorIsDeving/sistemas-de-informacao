#include "./basics.c"
#define V 3

void copia(int vertices, int m1[vertices][vertices], int m2[vertices][vertices]) {
    for(int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            m2[i][j] = m1[i][j];
            m1[i][j] = -1;
        }
    }
}

int main() {
    int m1[V][V];
    inicializarMatriz(V, m1);

    criarArestas(0, 0, 40, V, m1);
    criarArestas(0, 1, 5, V, m1);
    criarArestas(1, 2, 20, V, m1);
    criarArestas(2, 0, 30, V, m1);
    
    printf("Grafo Original\n");
    imprime(V, m1);

    int m2[V][V];
    copia(V, m1, m2);
    
    printf("Grafo Copiado\n");
    imprime(V, m2);
    printf("Grafo Original\n");
    imprime(V, m1);


    return 1;
}