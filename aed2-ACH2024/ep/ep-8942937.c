//--------------------------------------------------------------
// NOMES DOS RESPONSAVEIS: Victor Augusto Costa Monteiro
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define BOOL int
#define true 1
#define false 0

int grupo() {
  return 0;
}

// ######### ESCREVA O NROUSP AQUI
int nroUSP1() {
    return 8942937;
}

int nroUSP2() {
    return 0;
}

// elemento das listas de adjacencia e de resposta - NAO ALTERE ESTA DEFINICAO
typedef struct estr 
{
      int adj; // elemento
      int peso; // custo (nao precisa ser usado na resposta)
      struct estr *prox;
} NO;

// vertices do grafo (salas) - use este tipo ao criar o grafo  - NAO ALTERE ESTA DEFINICAO
typedef struct 
{
       int flag; // para uso na busca em largura e profundidade, se necessario
       BOOL aberto; // vale true se a sala em questao esta aberta
       int via; // use este campo se precisar computar algum caminho etc.
       int dist; // use este campo se precisar computar alguma distancia etc.
       NO* inicio;
} VERTICE;


// funcao principal
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave);

//Imprimir o grafo com distâncias para uma origem
//origem determinada na busca em largura
void imprimeListaCompleta(VERTICE* g, int vertices) {
    // printf("Lista de Adjacencia\n");
    printf("|F|A|V|Dis|V|:ListaAdjacencia\n");
    for (int i = 0; i < vertices; i++) {
        printf("|%i|%i|", g[i].flag, g[i].aberto);
        if (g[i].via == -1) {
            printf("n|");
        } else {
            printf("%i|", g[i].via);
        }
        if (g[i].dist == 2147483647) {
            printf("inf|");
        } else {
            if (g[i].dist == 0) {
                printf("000|");
            } else if (g[i].dist < 100) {
                printf("0%i|", g[i].dist);
            } else {
                printf("%i|", g[i].dist);
            }
        }
        printf("%i|", i + 1);
        NO* n = g[i].inicio;
        while (n) {
            printf(" -> (v:%i, p:%i)", n->adj, n->peso);
            n = n->prox;
        }
        printf("\n");
    }
}

// inicializar flags do grafo como desconhecidos = 0
void inicializaFlag(VERTICE* g, int N) {
    for (int i = 0; i < N; i++) {
        g[i].flag = 0;
    }
}

// inicializar vias do grafo como desconhecidas = -1
void inicializaVia(VERTICE* g, int N) {
    for (int i = 0; i < N; i++) {
        g[i].via = -1;
    }
}

// inicializar distancias do grafo como desconhecidas = máximo int em c
void inicializaDist(VERTICE* g, int N) {
    for (int i = 0; i < N; i++) {
        g[i].dist = 2147483647; //int máximo
    }
}

// inicializar vertices como aberto ou fechado do grafo
void inicializaAberto(VERTICE* g, int N, int* aberto) {
    for (int i = 0; i < N; i++) {
        g[i].aberto = aberto[i];
    }
}

//cria um grafo em lista de adjacência a partir de vértices, arestas e suas conexões
VERTICE* grafoListaAdjacencia(int N, int A, int* ijpeso) {
    VERTICE* resp = (VERTICE*) malloc(sizeof(VERTICE) * N);
    //ijpeso no formato origem, destino, peso
    for (int i = 0; i < N; i++) {
        resp[i].inicio = NULL;
    }
    int j = 0;
    while (j < 3*A) {
        // grafo não dirigido, então cria-se dois nós
        NO* n1 = (NO*) malloc(sizeof(NO));
        n1->peso = ijpeso[j + 2];
        n1->adj = ijpeso[j + 1];
        n1->prox = resp[ijpeso[j] - 1].inicio;
        resp[ijpeso[j] - 1].inicio = n1;

        NO* n2 = (NO*) malloc(sizeof(NO));
        n2->peso = ijpeso[j + 2];
        n2->adj = ijpeso[j];
        n2->prox = resp[ijpeso[j + 1] - 1].inicio;
        resp[ijpeso[j + 1] - 1].inicio = n2;
        
        j = j + 3;
    }

    return resp;
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{
	NO* resp;
	resp = NULL;

	// montar grafo em lista de adjacência
    VERTICE* g = grafoListaAdjacencia(N, A, ijpeso);
    // inicializar campos da estrutura do grafo
    inicializaFlag(g, N);
    inicializaVia(g, N);
    inicializaDist(g, N);
    g[inicio - 1].dist = 0; //distância da origem para si mesmo é zero
    inicializaAberto(g, N, aberto);

    imprimeListaCompleta(g, N);

	return resp;
}


//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {
	// aqui vc pode incluir codigo de teste

	// exemplo de teste trivial
    printf("Teste 1\n");
	int N1=3; // grafo de 3 vertices numerados de 1..3
	int aberto1[] = {1,1,1}; // todos abertos
	int inicio1=1;
	int fim1=3;
	int chave1=2;
	int ijpeso1[]={
        1,2,10, 
        2,3,20, 
        3,1,10
    };

	// o EP sera testado com uma serie de chamadas como esta
	NO* teste1 = NULL;
	teste1 = caminho(N1, 3, ijpeso1, aberto1, inicio1, fim1, chave1);
    printf("    ");
    while(teste1) {
        printf("%i", teste1->adj);
        teste1 = teste1->prox;
        if(teste1) {
            printf(" -> ");
        }
    }
    printf("\n");

	// exemplo de teste no enunciado do ep
    printf("Teste 2\n");
	int N2 = 9;
	int aberto2[] = {0,1,1,1,1,1,1,1}; 
	int inicio2 = 7;
	int fim2 = 4;
	int chave2 = 6;
	int ijpeso2[] = {
        1,2,30, 
        1,3,20, 
        2,6,20, 
        2,7,30, 
        3,4,20,
        3,7,80,
        4,9,80,
        5,8,10,
        6,7,10,
        7,9,80
    };

	NO* teste2 = NULL;
	teste2 = caminho(N2, 10, ijpeso2, aberto2, inicio2, fim2, chave2);
    printf("    ");
    while(teste2) {
        printf("%i", teste2->adj);
        teste2 = teste2->prox;
        if(teste2) {
            printf(" -> ");
        }
    }
    printf("\n");
	
    return 1;
}

// por favor nao inclua nenhum codigo abaixo da funcao main()
