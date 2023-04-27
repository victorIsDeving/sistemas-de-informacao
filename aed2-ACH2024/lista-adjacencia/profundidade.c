#include "./basics.c"

int V = 7;

//Busca em profundidade básica usando recursividade
// vai até onde dá por um caminho e faz rollback quando chegar
// em um vértice sem filhos
void profundidade(VERTICE* g, int vertices, int origem) {
    g[origem].flag = 1;
    printf("%i", origem);
    NO* no = g[origem].inicio;
    while(no) {
        if (g[no->adj].flag == 0) {
            printf(" -> ");
            profundidade(g, vertices, no->adj);
        }
        no = no->prox;
    }
    g[origem].flag = 2;
}

int main() {
    VERTICE* grafo = criarGrafo(V);

    criarArestas(grafo, 0, 1, 10);
    criarArestas(grafo, 0, 2, 20);
    criarArestas(grafo, 0, 3, 15);
    criarArestas(grafo, 1, 2, 20);
    criarArestas(grafo, 1, 6, 15);
    criarArestas(grafo, 2, 1, 20);
    criarArestas(grafo, 2, 6, 15);
    criarArestas(grafo, 3, 2, 20);
    criarArestas(grafo, 3, 4, 10);
    criarArestas(grafo, 4, 4, 15);
    criarArestas(grafo, 4, 5, 15);
    criarArestas(grafo, 5, 6, 20);
    criarArestas(grafo, 5, 3, 10);
    criarArestas(grafo, 6, 6, 10);
    criarArestas(grafo, 6, 5, 20);

    printf("Grafo:\n");
    imprime(grafo, V);

    printf("Busca em profundidade com a ordem de descoberta:\n");
    zerarFlags(grafo, V);
    profundidade(grafo, V, 0);

    return 1;
}