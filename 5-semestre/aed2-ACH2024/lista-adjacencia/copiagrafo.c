#include "./basics.c"

int V = 3;

//Função que copia o grafo para uma nova variável
//Sem alterar o original
VERTICE* copia(VERTICE * g) {
    //grafo que será retornado como resposta
    VERTICE * resp = (VERTICE*) malloc(sizeof(NO) * V);
    int i;
    for(i = 0; i < V; i++) {
        resp[i].inicio = NULL;
        NO* p = g[i].inicio;
        while(p) {
            NO* novo = (NO*) malloc(sizeof(NO));
            novo->adj = p->adj;
            novo->peso = p->peso;
            novo->prox = resp[i].inicio;
            resp[i].inicio = novo;
            p = p->prox;
        }
    }
    return resp;
}

int main() {
    VERTICE* g = criarGrafo(V);

    //Montar Grafo 
    criarArestas(g, 0, 0, 40);
    criarArestas(g, 0, 1, 10);
    criarArestas(g, 1, 2, 20);
    criarArestas(g, 2, 0, 30);
    printf("Grafo Original\n");
    imprime(g, V);

    VERTICE* gc = copia(g);

    printf("Grafo Copiado\n");
    imprime(gc, V);
    printf("Grafo Original\n");
    imprime(g, V);

    return 1;
}