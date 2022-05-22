#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

// ######### ESCREVA O NRO DO SEU GRUPO AQUI CONFORME CADASTRADO EM
// https://docs.google.com/spreadsheets/d/1_wy0Uko3vX8GE07G1WP4X6X6-yRdu6eCpLdmmRvU7EM/edit?usp=sharing

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

//-------------------------------------------

// nos das listas de adjacencias
// usados no grafo, e para uso tambem na lista de resposta
typedef struct adj {
	int v;
	int custo;
	struct adj* prox;
} NO;

// vertices
typedef struct {
	int tipo;
	NO* inicio;
} VERTICE;



//vvvvv ------------------- FUNÇÕES E ESTRUTURAS PARA TESTES ------------------- vvvvv
//grafo
typedef struct grafo {
	int vertices;
	int arestas;
	VERTICE *adj;
} GRAFO;

GRAFO *criaGrafo (int v) {
	GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
	g->vertices = v;
	g->arestas = 0;
	g->adj = (VERTICE *) malloc(v*sizeof(VERTICE));
	int i;
	for (i=0; i<v; i++) g->adj[i].inicio = NULL;
	
	return g;
}

NO *criaAdj (int v, int peso) {
	NO *temp = (NO *) malloc(sizeof(NO));
	temp->v = v;
	temp->custo = peso;
	temp->prox = NULL;
	
	return(temp);
}

int criaAresta(GRAFO *gr, int vi, int vf, int p) {
	if (!gr) return 0;
	if ( (vf<0) || (vf >= gr->vertices) ) return 0;
	if ( (vi<0) || (vi >= gr->vertices) ) return 0;
	NO *novo = criaAdj(vf,p);
	novo->prox = gr->adj[vi].inicio;
	gr->adj[vi].inicio = novo;
	gr->arestas++;
	
	return(1);
}

int atribuiTipo(GRAFO *gr, int vertice, int tipo) {
	gr->adj[vertice].tipo = tipo;
}

void imprime(GRAFO *gr) {
	printf("Vértices: %d. Arestas: %d.\n", gr->vertices, gr->arestas);
	printf("vértice(tipo): vértice(custo)\n");
	int i;
	for (i=0; i<gr->vertices; i++) {
		printf("	v%d(%i): ", i, gr->adj[i].tipo);
		NO *ad = gr->adj[i].inicio;
		while (ad) {
			printf("v%d(%d) ", ad->v, ad->custo);
			ad = ad->prox;
		}
		printf("\n");
	}
	printf("\n");
}

void printListaCustos(int* listaCustos, int V) {
	printf("lista custos\n	");
	for (int i=0; i<V; i++) {
		if (listaCustos[i] == 1000000000) {
			printf("10^9 ");
		} else {
			printf("%d ", listaCustos[i]);
		}
	}
	printf("\n");
}

void printListaAbertos(int* listaAbertos, int V) {
	printf("lista abertos\n	");
	for (int i=0; i<V; i++) {
		printf("%d ", listaAbertos[i]);
	}
	printf("\n");
}

void printListaPredecessores(int* listaPredecessores, int V) {
	printf("lista predecessores\n	");
	for (int i=0; i<V; i++) {
		printf("%d ", listaPredecessores[i]);
	}
	printf("\n");

}

void printListaDistancias(int* listaDistancias, int V) {
	printf("lista distâncias (em arestas)\n	");
	for (int i=0; i<V; i++) {
		printf("%d ", listaDistancias[i]);
	}
	printf("\n");

}

void printListaTiposT(int* listaTipos, int V) {
	printf("lista tipos buscados\n	");
	for (int i=0; i<V; i++) {
		printf("%d ", listaTipos[i]);
	}
	printf("\n");

}
//^^^^^ ------------------- FUNÇÕES E ESTRUTURAS PARA TESTES ------------------- ^^^^^



//vvvvv ------------------- FUNÇÃO PRINCIPAL E AUXILIARES ------------------- vvvvv
// funcao principal (assinatura exigida por alguns compiladores)
NO* EncontrarCaminho(VERTICE* g, int V, int v1, int t);

//função auxiliar 1 - inicializar as listas paralelas
int inicializaListasParalelas(int verticesGrafo, int* listaCustos, int* listaAbertos, int* listaPredecessores, int* listaDistancias, int* listaTipos, int verticeRaiz) {
	int i;
	
	//custo 10^9 é a custo ainda não definido
	for (i = 0; i<verticesGrafo; i++) listaCustos[i] = 1000000000; 
	listaCustos[verticeRaiz] = 0; //custo da raiz para a raiz é zero
	/**
	* Tentei colocar um número bem alto para a comparação da função auxiliar menorCusto()
	* O ideal seria colocar INT_MAX, da biblioteca <limits.h>
	* mas não sei se daria problema nos algoritmos de correção do EP
	*/


	// 0=fechado e 1=aberto
	for (i = 0; i<verticesGrafo; i++) listaAbertos[i] = 1;

	//predecessor -1 é o que não está definido ainda
	for (i=0; i<verticesGrafo; i++)	listaPredecessores[i] = -1; 


	//distancias, em arestas, do vértice raiz definidas como 0 no início
	for (i = 0; i<verticesGrafo; i++) listaDistancias[i] = 0;

	// todos os tipos definidos como 0
	for( int m=0; m<verticesGrafo; m++) listaTipos[m] = 0;

	return 1;
}

//função auxiliar 2 - relaxamento da distância do vértice, de u1 para u2
void relaxa(VERTICE *g, int *custos, int *predecessores, int u1, int u2) {
	NO *no = g[u1].inicio;
	while (no && (no->v != u2)) no = no->prox;
	if (no) {
		if (custos[u2] > custos[u1]+no->custo) {
			custos[u2] = custos[u1] + no->custo;
			predecessores[u2] = u1;
		}
	}
}

//função auxiliar 3 - verifica se existem nós abertos na lista paralela abertos
int existeAberto(int verticesGrafo, int *abertos) {
	int i;
	for (i=0; i<verticesGrafo; i++) if(abertos[i]) return(1);
	return 0;
}

//função auxiliar 4 - busca o nó aberto com menor distância nas listas paralelas abertos e custos
int menorCusto(int verticesGrafo, int *abertos, int *custos) {
	int i;
	for (i=0; i<verticesGrafo; i++) if(abertos[i]) break;
	if (i==verticesGrafo) return(-1);
	int menor = i;
	for (i=menor+1; i<verticesGrafo; i++)
		if (abertos[i] && (custos[menor]>custos[i]))
			menor = i;
	return(menor);
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO* EncontrarCaminho(VERTICE* g, int V, int v1, int t) {
	NO* caminho = (NO *) malloc(sizeof(NO));
	caminho->v = v1;
	caminho->custo = 0;
	caminho->prox = NULL;
	
	int custos[V]; //lista paralela para controle dos custos do vértice raiz para os vértices restantes
	int abertos[V]; //lista paralela para controle de vértices visitados/não visitados/totalmente explorados
	int predecessores[V]; //lista paralela do predecessor que tem o caminho mais curto para o vértice, partindo da raiz definida como v1 na função
	int distancias[V]; //lista paralela da distância (em arestas) do vértice raiz até os vértices restantes
	int tiposT[V]; //lista paralela que marca o índice do vértice com 1 se for do tipo procurado
	inicializaListasParalelas(V, custos, abertos, predecessores, distancias, tiposT, v1);

	// printf("\n");
	// printListaCustos(custos, V);
	// printListaAbertos(abertos, V);
	// printListaPredecessores(predecessores, V);
	// printListaDistancias(distancias, V);
	// printListaTiposT(tiposT, V);
	// printf("\n");

	// printf("Djikstra rolando\n");

	while (existeAberto(V,abertos)) {
		int u = menorCusto(V, abertos, custos);
		abertos[u] = 0;
		NO *no = g[u].inicio;
		while (no) {
			relaxa(g, custos, predecessores, u, no->v);
			if( g[no->v].tipo == t ) tiposT[no->v] = 1;
			no = no->prox;
		}
		// int s = 0;
		// for(s; s<V; s++) {
		// 	if(tiposT[s] == 1) break;
		// }
		// if (s!=V) break;
	}

	//definir as distâncias do vértice raiz
	int j = 1;
	for(int i =0; i<V; i++) {
		if (i==v1) {
			distancias[i] = 0;
		} else {
			int k = predecessores[i];
			while (k != v1) {
				j++;
				k = predecessores[k];
			}
			distancias[i] = j;
			j=1;
		}		
	}
	// printf("\n");

	
	// printf("\n");
	// printListaCustos(custos, V);
	// printListaAbertos(abertos, V);
	// printListaPredecessores(predecessores, V);
	// printListaDistancias(distancias, V);
	// printListaTiposT(tiposT, V);
	// printf("\n");

	int p,q,dist2;
	NO* v2 = (NO*) malloc(sizeof(NO));
	v2->v = -1;
	v2->custo = -1;
	v2->prox = NULL;
	for(p=0; p<V; p++) {
		if( tiposT[p]==1 && p!=v1 ) {
			v2->v = p;
			dist2 = distancias[p];
			v2->custo = custos[p];
			for(q=p+1; q<V; q++) {
				if (tiposT[q]==1 && q!=v1 && dist2>distancias[q] && v2->custo>custos[q]) {
					v2->v = q;
					dist2 = distancias[q];
					v2->custo = custos[q];
				}
			}
		}
	}

	//condicional para o caso de não ter o tipo alvo no grafo
	if (v2->v == -1) return caminho;

	caminho->prox = v2;
	return caminho;

}
//^^^^^ ------------------- FUNÇÃO PRINCIPAL E AUXILIARES ------------------- ^^^^^



//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
// mas nao entregue o codido de main() nem inclua nada
// abaixo deste ponto
//---------------------------------------------------------
int main()
{
	if (nroUSP1()==0) printf("\n\nNro USP do primeiro integrante nao informado!!!\n\n");
	// if (grupo()==0) printf("\n\nNro do grupo nao informado!!!\n\n");

	// crie um grafo de teste aqui
	// chame a funcao implementada e armazena a lista em uma variavel NO*
	// verifique se a lista retornada está correta
	int vertices = 10;
	GRAFO *gr = criaGrafo(vertices);
	atribuiTipo(gr,0,1);
	atribuiTipo(gr,1,1);
	atribuiTipo(gr,2,1);
	atribuiTipo(gr,3,2);
	atribuiTipo(gr,4,3);
	atribuiTipo(gr,5,3);
	atribuiTipo(gr,6,4);
	atribuiTipo(gr,7,4);
	atribuiTipo(gr,8,5);
	atribuiTipo(gr,9,6);

	criaAresta(gr,0,1,4);
	criaAresta(gr,0,2,2);
	criaAresta(gr,0,3,1);
	criaAresta(gr,2,1,3);
	criaAresta(gr,3,2,3);
	criaAresta(gr,3,4,4);
	criaAresta(gr,3,5,2);
	criaAresta(gr,4,0,2);
	criaAresta(gr,5,6,3);
	criaAresta(gr,5,7,3);
	criaAresta(gr,6,8,5);
	criaAresta(gr,6,9,5);
	criaAresta(gr,7,8,1);

	imprime(gr);
	int verticeRaiz = 0;
	int tipoAlvo = 6;
	NO* caminho = EncontrarCaminho(gr->adj, vertices, verticeRaiz, tipoAlvo);

	printf("\n");
	printf("caminho de v%i até tipo %i\n", verticeRaiz, tipoAlvo);
	while(caminho) {
		printf("v%i(%i)", caminho->v, caminho->custo);
		caminho = caminho->prox;
		if(caminho) printf(" -> ");
	}

}
