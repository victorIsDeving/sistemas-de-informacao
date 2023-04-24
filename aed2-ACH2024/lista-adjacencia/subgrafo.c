#include "./basics.c"

//Função que verifica se um grafo é subgrafo de outro
//se g2 é subgrafo de g1
int subgrafo(VERTICE* g1, VERTICE* g2, int vertices) {
    int i;
    for(i = 0; i < vertices; i++) {
        NO* p = g2[i].inicio;
        while(p) {
            int achou = 0;
            NO* q = g1[i].inicio;
            while(q) {
                if(p->adj == q-> adj) {
                    achou = 1;
                    break;
                }
                q = q->prox;
            }
            if (!achou) return 0;
            if (p->peso != q->peso) return 0;
            p = p->prox;
        }
    }
    return 1;
}

int main() {
    //Variável para a quantidade de vértices
    int V = 3;

    //grafos
    VERTICE* g1 = criarGrafo(3);
    VERTICE* g2 = criarGrafo(3);
    VERTICE* g3 = criarGrafo(3);

    //Montar Grafo 1
    criarArestas(g1, 0, 0, 40);
    criarArestas(g1, 0, 1, 10);
    criarArestas(g1, 1, 2, 20);
    criarArestas(g1, 2, 0, 30);
    printf("Grafo 1\n");
    imprime(g1, V);

    //Montar Grafo 2
    criarArestas(g2, 0, 1, 10);
    criarArestas(g2, 1, 2, 20);
    printf("Grafo 2\n");
    imprime(g2, V);

    //Montar Grafo 3
    criarArestas(g3, 2, 0, 15);
    criarArestas(g3, 2, 1, 15);
    printf("Grafo 3\n");
    imprime(g3, V);

    printf("Verificando subgrafos:\n");
    if (subgrafo(g1, g2, V)) {
        printf("G2 eh subgrafo de G1!\n");
    } else {
        printf("G2 nao eh subgrafo de G1.\n");
    }
    if (subgrafo(g1, g3, V)) {
        printf("G3 eh subgrafo de G1!\n");
    } else {
        printf("G3 nao eh subgrafo de G1.\n");
    }

    return 1;
}