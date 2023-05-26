//--------------------------------------------------------------
// NOMES DOS RESPONSAVEIS: Victor Augusto Costa Monteiro
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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
       int aberto; // vale 1 se a sala em questao esta aberta
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
                printf(" %i|", g[i].dist);
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
	NO* path1;
    path1 = NULL;
	NO* path2;
    path2 = NULL;
    int hasKey = 0;

	// montar grafo em lista de adjacência
    VERTICE* g = grafoListaAdjacencia(N, A, ijpeso);
    // inicializar campos da estrutura do grafo
    // na lista, o vertice 1 ocupa a posição 0 e assim por diante
    inicializaFlag(g, N);
    inicializaVia(g, N);
    inicializaDist(g, N);
    g[inicio - 1].dist = 0; //distância da origem para si mesmo é zero
    inicializaAberto(g, N, aberto);

    // Método para resolução
    // Faz um Djikstra até o final sem passar por vértices fechados - path1
    // Faz um Djikstra até o vértice com a chave e depois um djikstra até o final - path2
    // Compara os dois e escolhe o caminho mais barato

    // DJIKSTRA ATÉ O FINAL CONTORNANDO OS VÉRTICES FECHADOS
    // define o primeiro vertice que será explorado
    int z = inicio - 1;
    NO* n = g[z].inicio;
    //iterar pelos adjacentes
    while(n) {
        if (g[n->adj - 1].aberto == 1) { // o vértice deve estar aberto
            //faz a comparação da distância atual dos adjacentes com a nova distância 
            if ( (g[n->adj - 1].dist) > (g[z].dist + n->peso) ) {
                    g[n->adj - 1].dist = g[z].dist + n->peso;
                    g[n->adj - 1].via = z + 1;
            }
            if (n->adj == fim) break;
            //passa para o próximo adjacente
            n = n->prox;
            //se acabou os adjacentes, busca pelo próximo vértice a ser estudado
            if (!n) {
                //termina o vértice pai
                g[z].flag = 1;
                //variável para controle do vértice com menor distância
                int shorter = 2147483647;
                for (int i = 0; i < N; i++) {
                    //o próximo vértice será o que não foi terminado E tem a menor distância atual
                    if (g[i].flag != 1 && shorter > g[i].dist) {
                        shorter = g[i].dist;
                        z = i;
                    }
                }
                //se teve alteração na controle é porque existe vértice alcançável
                if (shorter != 2147483647) {
                    n = g[z].inicio;
                }
                //se não teve alteração o n já é NULL e vai quebrar o laço while
            }
        } else { // se está fechado
            //passa para o próximo adjacente
            n = n->prox;
            //se acabou os adjacentes, busca pelo próximo vértice a ser estudado
            if (!n) {
                //termina o vértice pai
                g[z].flag = 1;
                //variável para controle do vértice com menor distância
                int shorter = 2147483647;
                for (int i = 0; i < N; i++) {
                    //o próximo vértice será o que não foi terminado E tem a menor distância atual
                    if (g[i].flag != 1 && shorter > g[i].dist) {
                        shorter = g[i].dist;
                        z = i;
                    }
                }
                //se teve alteração na controle é porque existe vértice alcançável
                if (shorter != 2147483647) {
                    n = g[z].inicio;
                }
                //se não teve alteração o n já é NULL e vai quebrar o laço while
            }
        }
    }

    // imprimeListaCompleta(g, N);
    
    //montar retorno e soma da distância
    int dist1 = g[fim - 1].dist;
    int v = fim;
    while (v != -1) {
        NO* r = (NO*) malloc(sizeof(NO));
        r->adj = v;
        r->prox = path1;
        path1 = r;
        v = g[v - 1].via;
    }

    // DIJKSTRA ATÉ O VÉRTICE CHAVE E DEPOIS ATÉ O FINAL
    // Reinicializar campos da estrutura do grafo
    // na lista, o vertice 1 ocupa a posição 0 e assim por diante
    inicializaFlag(g, N);
    inicializaVia(g, N);
    inicializaDist(g, N);
    g[inicio - 1].dist = 0; //distância da origem para si mesmo é zero
    //define o primeiro vertice que será explorado
    z = inicio - 1;
    n = g[z].inicio;
    //iterar pelos adjacentes
    while(n) {
        if (g[n->adj - 1].aberto == 1) { // o vértice deve estar aberto
            //faz a comparação da distância atual dos adjacentes com a nova distância 
            if ( (g[n->adj - 1].dist) > (g[z].dist + n->peso) ) {
                    g[n->adj - 1].dist = g[z].dist + n->peso;
                    g[n->adj - 1].via = z + 1;
            }
            if (n->adj == chave) break;
            //passa para o próximo adjacente
            n = n->prox;
            //se acabou os adjacentes, busca pelo próximo vértice a ser estudado
            if (!n) {
                //termina o vértice pai
                g[z].flag = 1;
                //variável para controle do vértice com menor distância
                int shorter = 2147483647;
                for (int i = 0; i < N; i++) {
                    //o próximo vértice será o que não foi terminado E tem a menor distância atual
                    if (g[i].flag != 1 && shorter > g[i].dist) {
                        shorter = g[i].dist;
                        z = i;
                    }
                }
                //se teve alteração na controle é porque existe vértice alcançável
                if (shorter != 2147483647) {
                    n = g[z].inicio;
                }
                //se não teve alteração o n já é NULL e vai quebrar o laço while
            }
        } else { // se está fechado
            //passa para o próximo adjacente
            n = n->prox;
            //se acabou os adjacentes, busca pelo próximo vértice a ser estudado
            if (!n) {
                //termina o vértice pai
                g[z].flag = 1;
                //variável para controle do vértice com menor distância
                int shorter = 2147483647;
                for (int i = 0; i < N; i++) {
                    //o próximo vértice será o que não foi terminado E tem a menor distância atual
                    if (g[i].flag != 1 && shorter > g[i].dist) {
                        shorter = g[i].dist;
                        z = i;
                    }
                }
                //se teve alteração na controle é porque existe vértice alcançável
                if (shorter != 2147483647) {
                    n = g[z].inicio;
                }
                //se não teve alteração o n já é NULL e vai quebrar o laço while
            }
        }
    }
    //montar retorno e soma da distância
    int dist2 = g[chave - 1].dist;
    v = chave;
    while (v != -1) {
        NO* r = (NO*) malloc(sizeof(NO));
        r->adj = v;
        r->prox = path2;
        path2 = r;
        v = g[v - 1].via;
    }

    //outro djikstra partindo da chave
    inicializaFlag(g, N);
    inicializaVia(g, N);
    inicializaDist(g, N);
    g[chave - 1].dist = 0; //distância da origem para si mesmo é zero
    z = chave - 1;
    n = g[z].inicio;
    //iterar pelos adjacentes
    while(n) { //todos os vértices estão abertos agora
        //faz a comparação da distância atual dos adjacentes com a nova distância 
        if ( (g[n->adj - 1].dist) > (g[z].dist + n->peso) ) {
                g[n->adj - 1].dist = g[z].dist + n->peso;
                g[n->adj - 1].via = z + 1;
        }
        if (n->adj == fim) break;
        //passa para o próximo adjacente
        n = n->prox;
        //se acabou os adjacentes, busca pelo próximo vértice a ser estudado
        if (!n) {
            //termina o vértice pai
            g[z].flag = 1;
            //variável para controle do vértice com menor distância
            int shorter = 2147483647;
            for (int i = 0; i < N; i++) {
                //o próximo vértice será o que não foi terminado E tem a menor distância atual
                if (g[i].flag != 1 && shorter > g[i].dist) {
                    shorter = g[i].dist;
                    z = i;
                }
            }
            //se teve alteração na controle é porque existe vértice alcançável
            if (shorter != 2147483647) {
                n = g[z].inicio;
            }
            //se não teve alteração o n já é NULL e vai quebrar o laço while
        }
    }
    //montar retorno e soma da distância
    dist2 += g[fim - 1].dist;
    NO* aux1 = NULL;
    v = fim;
    while (v != -1) {
        if (v != chave) { 
            NO* r = (NO*) malloc(sizeof(NO));
            r->adj = v;
            r->prox = aux1;
            aux1 = r;
        }
        v = g[v - 1].via;
    }
    NO* aux2 = path2;
    while (aux2->prox) {
        aux2 = aux2->prox;
    }
    aux2->prox = aux1;

    if (dist1 <= dist2) {
        resp = path1;
    } else {
        resp = path2;
    }

	return resp;
}


//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {
	// aqui vc pode incluir codigo de teste

    // teste 1
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

	// teste 2
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

	// teste 3
    // enunciado do ep com uma diferença no vetor de vértices abertos
    printf("Teste 3\n");
	int N3 = 9;
	int aberto3[] = {1,1,0,1,1,1,1,1}; 
	int inicio3 = 7;
	int fim3 = 4;
	int chave3 = 6;
	int ijpeso3[] = {
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

	NO* teste3 = NULL;
	teste3 = caminho(N3, 10, ijpeso3, aberto3, inicio3, fim3, chave3);
    printf("    ");
    while(teste3) {
        printf("%i", teste3->adj);
        teste3 = teste3->prox;
        if(teste3) {
            printf(" -> ");
        }
    }
    printf("\n");

	// teste 4
    // teste 3 com diferença no peso de algumas arestas
    printf("Teste 4\n");
	int N4 = 9;
	int aberto4[] = {1,1,0,1,1,1,1,1}; 
	int inicio4 = 7;
	int fim4 = 4;
	int chave4 = 6;
	int ijpeso4[] = {
        1,2,30, 
        1,3,20, 
        2,6,20, 
        2,7,30, 
        3,4,20,
        3,7,80,
        4,9,80,
        5,8,10,
        6,7,10,
        7,9,10
    };

	NO* teste4 = NULL;
	teste4 = caminho(N4, 10, ijpeso4, aberto4, inicio4, fim4, chave4);
    printf("    ");
    while(teste4) {
        printf("%i", teste4->adj);
        teste4 = teste4->prox;
        if(teste4) {
            printf(" -> ");
        }
    }
    printf("\n");

	// teste 5
    // teste 3 com diferença no peso de algumas arestas
    printf("Teste 5\n");
	int N5 = 9;
	int aberto5[] = {1,1,0,1,1,1,1,1}; 
	int inicio5 = 7;
	int fim5 = 4;
	int chave5 = 6;
	int ijpeso5[] = {
        1,2,30, 
        1,3,20, 
        2,6,20, 
        2,7,10, 
        3,4,20,
        3,7,80,
        4,9,80,
        5,8,10,
        6,7,10,
        7,9,80
    };

	NO* teste5 = NULL;
	teste5 = caminho(N5, 10, ijpeso5, aberto5, inicio5, fim5, chave5);
    printf("    ");
    while(teste5) {
        printf("%i", teste5->adj);
        teste5 = teste5->prox;
        if(teste5) {
            printf(" -> ");
        }
    }
    printf("\n");

	// teste 6
    // novo grafo
    printf("Teste 6\n");
	int N6 = 5;
	int aberto6[] = {1,1,0,1,1}; 
	int inicio6 = 5;
	int fim6 = 1;
	int chave6 = 4;
	int ijpeso6[] = {
        1,2,80,
        1,3,80,
        2,4,20,
        2,5,80,
        3,4,10,
        4,5,10,
    };

	NO* teste6 = NULL;
	teste6 = caminho(N6, 6, ijpeso6, aberto6, inicio6, fim6, chave6);
    printf("    ");
    while(teste6) {
        printf("%i", teste6->adj);
        teste6 = teste6->prox;
        if(teste6) {
            printf(" -> ");
        }
    }
    printf("\n");

    return 1;
}

// por favor nao inclua nenhum codigo abaixo da funcao main()
