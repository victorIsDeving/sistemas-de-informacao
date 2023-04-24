#include <stdio.h>
#include <stdlib.h>

//Implementação de grafo para uma lista de adjacências
//Algumas funções de uso geral

//Nós que representam a adjacência na lista de vértices
typedef struct NO {
    int adj;
    int peso;
    struct NO* prox;
} NO;

//Estrutura que monta um vetor de listas de adjacência
typedef struct {
    NO* inicio;
} VERTICE;
//Cada índice do vetor representa um vértice do grafo
//A lista ligada de adjacências são os vértices que tem uma aresta apontando do vértice índice 
// para o vértice indicado na estrura NO que compõe a lista ligada de adjacências

//Cria o grafo com a estrutura VERTICE com V vértives
VERTICE* criarGrafo(int V) {
    VERTICE* g = (VERTICE*) malloc(sizeof(VERTICE) * V);
    for (int i = 0; i < V; i++) {
        g[i].inicio = NULL;
    }
    return g;
}

//Cria as conexões no grafo
void criarArestas(VERTICE* g, int origem, int destino, int peso) {
    //Cria o novo NO para adicionar na lista ligada de adjacências
    NO* n = (NO*) malloc(sizeof(NO));
    n->adj = destino;
    n->peso = peso;
    //Adiciona a nova conexão no início da lista ligada
    n->prox = g[origem].inicio;
    g[origem].inicio = n;
}

//Imprimir o grafo
void imprime(VERTICE* g, int vertices) {
    // printf("Lista de Adjacencia\n");
    for (int i = 0; i < vertices; i++) {
        printf("%i:", i);
        NO* n = g[i].inicio;
        while (n) {
            printf(" -> (v: %i, p:%i)", n->adj, n->peso);
            n = n->prox;
        }
        printf("\n");
    }
}