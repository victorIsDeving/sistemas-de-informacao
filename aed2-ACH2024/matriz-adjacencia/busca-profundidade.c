#include "./basics.c"
#define V 7

//Busca em profundidade básica usando recursividade
// vai até onde dá por um caminho e faz trackback quando chegar
// em um vértice sem filhos
void profundidade(int vertices, int origem, AUXILIAR* aux, int m[vertices][vertices]) {
    aux[origem].flag = 1;
    printf("%i", origem);
    for(int i = 0; i < vertices; i++) {
        if(m[origem][i] != -1 && aux[i].flag == 0) {
            printf(" -> ");
            profundidade(vertices, i, aux, m);
        }
    }
    aux[origem].flag = 2;
}

int main() {
    int m[V][V];
    inicializarMatriz(V, m);

    criarArestas(0, 1, 9, V, m);
    criarArestas(0, 2, 9, V, m);
    criarArestas(0, 3, 9, V, m);
    criarArestas(1, 2, 9, V, m);
    criarArestas(1, 6, 9, V, m);
    criarArestas(2, 1, 9, V, m);
    criarArestas(2, 6, 9, V, m);
    criarArestas(3, 2, 9, V, m);
    criarArestas(3, 4, 9, V, m);
    criarArestas(4, 4, 9, V, m);
    criarArestas(4, 5, 9, V, m);
    criarArestas(5, 6, 9, V, m);
    criarArestas(5, 3, 9, V, m);
    criarArestas(6, 6, 9, V, m);
    criarArestas(6, 5, 9, V, m);

    printf("Grafo:\n");
    imprime(V, m);

    printf("Busca em profundidade com a ordem de descoberta:\n");
    AUXILIAR* aux = (AUXILIAR*) malloc(sizeof(AUXILIAR) * V);
    inicializarAuxiliar(aux, V);
    profundidade(V, 0, aux, m);

    return 1;
}