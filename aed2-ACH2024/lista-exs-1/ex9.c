#include "../lista-adjacencia/basics.c"
#define V 6
#define BOOL int
#define true 1
#define false 0

//Recebe dois grafos, g1 e g2, como parâmetros e 
// Retorna um grafo g3 apenas com as arestas excluisvas de g1
VERTICE* graphExclusive(int v1, int v2, VERTICE* g1, VERTICE* g2) {
    VERTICE* resp = (VERTICE*) malloc(sizeof(VERTICE) * v1);
    resp = criarGrafoLista(v1);
    for(int i = 0; i < v1; i++) {
        NO* n = (NO*) malloc(sizeof(NO));
        n = g1[i].inicio;
        while(n) {
            NO* p = (NO*) malloc(sizeof(NO));
            p = g2[i].inicio;
            int has = false;
            while(p) {
                if (n->adj == p->adj && n->peso == p->peso) {
                    has = true;
                    break;
                }
                p = p->prox;
            }
            if (!has) {
                NO* q = (NO*) malloc(sizeof(NO));
                q->adj = n->adj;
                q->peso = n->peso;
                q->prox = resp[i].inicio;
                resp[i].inicio = q;
            }
            n = n->prox;
        }
    }
    return resp;
}

int main() {
    VERTICE* g1 = (VERTICE*) malloc(sizeof(VERTICE) * V);
    g1 = criarGrafoLista(V);
    criarArestasLista(g1, 0, 1, 30);
    criarArestasLista(g1, 0, 4, 15);
    criarArestasLista(g1, 1, 2, 30);
    criarArestasLista(g1, 2, 5, 20);
    criarArestasLista(g1, 4, 3, 25);
    criarArestasLista(g1, 5, 4, 30);
    printf("Grafo g1 Lista:\n");
    imprimeLista(g1, V);

    VERTICE* g2 = (VERTICE*) malloc(sizeof(VERTICE) * V);
    g2 = criarGrafoLista(V);
    criarArestasLista(g2, 0, 1, 30);
    criarArestasLista(g2, 0, 4, 30);
    criarArestasLista(g2, 1, 2, 30);
    criarArestasLista(g2, 4, 3, 25);
    criarArestasLista(g2, 4, 5, 30);
    printf("Grafo g2 Lista:\n");
    imprimeLista(g2, V);

    VERTICE* g3 = (VERTICE*) malloc(sizeof(VERTICE) * V);
    g3 = graphExclusive(V, V, g2, g1);
    printf("Grafo g3 Lista (exclusivos g2):\n");
    imprimeLista(g3, V);
    
    return 1;
}