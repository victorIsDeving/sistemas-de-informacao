#include "./basics.c"

int V = 8;

typedef struct {
    int tamanho;
    NO* inicio;
} FILA;

void inicializarFila(FILA* f) {
    f->tamanho = 0;
    f->inicio = NULL;
}

void entrarFila(FILA* f, int vertice) {
    NO* p = (NO*) malloc(sizeof(NO));
    p->adj = vertice;
    p->prox = NULL;
    if (f->tamanho == 0) {
        f->inicio = p;
    } else {
        NO* q = f->inicio;
        while (q->prox) {
            q = q->prox;
        }
        q->prox = p;
    }
    f->tamanho++;
}

int sairFila(FILA* f) {
    int i = f->inicio->adj;
    f->inicio = f->inicio->prox;
    f->tamanho--;

    return i;
}

void largura(VERTICE* g, int vertices, int origem) {
    //começar a fila de vértices
    FILA* f = (FILA*) malloc(sizeof(FILA));
    inicializarFila(f);
    NO* p = g[origem].inicio;
    printf("    %i", origem);
    entrarFila(f, origem);
    g[origem].flag = 1;
    while (f->tamanho > 0) {
        origem = sairFila(f);
        p = g[origem].inicio;
        while(p) {
            if (g[p->adj].flag == 0) {
                printf(" -> %i", p->adj);
                g[p->adj].flag = 1;
                g[p->adj].dist = g[origem].dist + 1;
                entrarFila(f,p->adj);
            }
            p = p->prox;
        }
        g[origem].flag = 2;
    }
    printf("\n");
}

int main() {
    VERTICE* g = criarGrafo(V);

    criarArestas(g, 0, 3, 10);
    criarArestas(g, 0, 1, 10);
    criarArestas(g, 0, 5, 10);
    criarArestas(g, 0, 4, 10);
    criarArestas(g, 0, 6, 10);
    criarArestas(g, 1, 2, 10);
    criarArestas(g, 3, 5, 10);
    criarArestas(g, 5, 7, 10);
    criarArestas(g, 6, 7, 10);

    zerarFlags(g, V);
    inicializarDistancias(g, 0, V);
    printf("Grafo antes da busca em largura:\n");
    imprimeComDist(g, V);

    printf("Busca em largura com a ordem de descoberta:\n");
    largura(g, V, 0);
    printf("Grafo depois da busca em largura:\n");
    imprimeComDist(g, V);

    return 1;
}