#include "./basics.c"

int V = 3;

//Função que cria um grafo transposto
//inverte o sentido das arestas do grafo original
//deixa apenas a lista de vértices na variável original, esvazia o grafo original
VERTICE* transposto(VERTICE* g) {
    VERTICE* gt = (VERTICE*) malloc(sizeof(VERTICE) * V);
    int i = 0;
    for(i = 0; i < V; i++) gt[i].inicio = NULL;
    for(i = 0; i < V; i++) {
        NO* p = g[i].inicio;
        while(p) {
            NO* seguinte = p->prox;
            g[i].inicio = seguinte;
            p->prox = gt[p->adj].inicio;
            gt[p->adj].inicio = p;
            p->adj = i;
            p = seguinte;
        }
    }
    return gt;
}

int main() {
    
    VERTICE* g = criarGrafo(V);

    criarArestas(g, 0, 0, 40);
    criarArestas(g, 0, 1, 10);
    criarArestas(g, 1, 2, 20);
    criarArestas(g, 2, 0, 30);

    printf("Grafo Original\n");
    imprime(g, V);

    VERTICE* gt = transposto(g);

    printf("Grafo Transposto\n");
    imprime(gt, V);

    printf("Grafo Original\n");
    imprime(g, V);

    return 0;
}