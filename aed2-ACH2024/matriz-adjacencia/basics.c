#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int flag;
    int dist;
} AUXILIAR;

void inicializarMatriz(int vertices, int m[vertices][vertices]) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j ++) {
            m[i][j] = -1;
        }
    }
}

void inicializarAuxiliar(AUXILIAR* aux, int vertices) {
    for (int i = 0; i < vertices; i++) {
        aux[i].dist = 1000;
        aux[i].flag = 0;
    }
}

void criarArestas(int origem, int destino, int peso, int vertices, int m[vertices][vertices]) {
    m[origem][destino] = peso;
}

void imprime(int vertices, int m[vertices][vertices]) {
    printf(" |");
    for (int i = 0; i < vertices; i++) {
        printf("  %i|", i);
    }
    printf("\n");
    for (int j = 0; j < vertices; j++) {
        printf("%i|", j);
        for (int k = 0; k < vertices; k++) {
            if (m[j][k] == -1) {
                printf(" %i|", m[j][k]);
            } else if (m[j][k] < 10) {
                printf("  %i|", m[j][k]);
            } else {
                printf(" %i|", m[j][k]);
            }
        }
        printf("\n");
    }
}

void imprimeComDist(int vertices, int m[vertices][vertices], AUXILIAR* aux) {
    printf("(d) |");
    for (int i = 0; i < vertices; i++) {
        printf("  %i|", i);
    }
    printf("\n");
    for (int j = 0; j < vertices; j++) {
        printf("(%i)%i|", aux[j].dist, j);
        for (int k = 0; k < vertices; k++) {
            if (m[j][k] == -1) {
                printf(" %i|", m[j][k]);
            } else if (m[j][k] < 10) {
                printf("  %i|", m[j][k]);
            } else {
                printf(" %i|", m[j][k]);
            }
        }
        printf("\n");
    }
}