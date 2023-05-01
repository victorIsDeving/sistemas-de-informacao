#include "./basics.c"
#define V 8

typedef struct n {
    int vertice;
    struct n* prox;
} NO;

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
    p->vertice = vertice;
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
    int i = f->inicio->vertice;
    f->inicio = f->inicio->prox;
    f->tamanho--;

    return i;
}

void largura(int vertices, int origem, int m[vertices][vertices], AUXILIAR* aux) {
    //começar a fila de vértices
    FILA* f = (FILA*) malloc(sizeof(FILA));
    inicializarFila(f);
    entrarFila(f, origem);
    aux[origem].dist = 0;
    aux[origem].flag = 1;
    printf("%i", origem);
    while(f->tamanho > 0) {
        origem = sairFila(f);
        for(int j = 0; j < vertices; j++) {
            if(m[origem][j] != -1 && aux[j].flag == 0) {
                aux[j].flag = 1;
                aux[j].dist = aux[origem].dist + 1;
                printf(" -> %i", j);
                entrarFila(f, j);
            }
        }
        aux[origem].flag = 2;
    }
    printf("\n");
}

int main() {
    int m[V][V];
    inicializarMatriz(V, m);

    criarArestas(0, 3, 10, V, m);
    criarArestas(0, 1, 10, V, m);
    criarArestas(0, 5, 10, V, m);
    criarArestas(0, 4, 10, V, m);
    criarArestas(0, 6, 10, V, m);
    criarArestas(1, 2, 10, V, m);
    criarArestas(3, 5, 10, V, m);
    criarArestas(5, 7, 10, V, m);
    criarArestas(6, 7, 10, V, m);

    AUXILIAR* aux = (AUXILIAR*) malloc(sizeof(AUXILIAR) * V);
    inicializarAuxiliar(aux, V);
    printf("Grafo com distâncias antes da busca em largura:\n");
    imprimeComDist(V, m, aux);

    printf("Busca em largura com a ordem de descoberta:\n");
    largura(V, 0, m, aux);
    printf("Grafo com distâncias depois da busca em largura:\n");
    imprimeComDist(V, m, aux);

    return 1;
}