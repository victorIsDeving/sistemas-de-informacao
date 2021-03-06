/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   094 - Prof. Luciano Antonio Digiampietri                      **/
/**                                                                 **/
/**   EP 2 - Fila Preferencial                                      **/
/**                                                                 **/
/**   Victor Augusto Costa Monteiro             8942937             **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->ehPreferencial = false;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->ant;
	}
	printf("\n\n");
}


bool consultarPreferencial(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->ehPreferencial;
		atual = atual->prox;
	}
	return -1;
}



bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial){
	if ( id<0 || buscarID(f, id) ) return false;

	PONT novoId = (PONT) malloc(sizeof(ELEMENTO));
	novoId->id = id;
	novoId->ehPreferencial = ehPreferencial;

	if (novoId->ehPreferencial) { //novo id eh preferencial
		PONT ultPreferencial = f->cabeca->prox;
		if ( ultPreferencial == f->inicioNaoPref ) { //a fila preferencial est?? vazia
			f->cabeca->prox = novoId;
			f->inicioNaoPref->ant = novoId;
			novoId->ant = f->cabeca;
			novoId->prox = f->inicioNaoPref;
		} else { //fila preferencial n??o vazia
			while (ultPreferencial->prox != f->inicioNaoPref) {
				ultPreferencial = ultPreferencial->prox;
			}
			ultPreferencial->prox = novoId;
			f->inicioNaoPref->ant = novoId;
			novoId->ant = ultPreferencial;
			novoId->prox = f->inicioNaoPref;
		}
	} else { //novoId nao eh preferencial
		PONT ultNaoPreferencial = f->inicioNaoPref;
		if ( ultNaoPreferencial == f->cabeca ) { //fila n??o preferencial est?? vazia
			f->inicioNaoPref = novoId;
			f->cabeca->ant->prox = novoId;
			novoId->ant = f->cabeca->ant;
			novoId->prox = f->cabeca;
			f->cabeca->ant = novoId;
		} else { //fila n??o preferencial n??o est?? vazia
			f->cabeca->ant->prox = novoId;
			novoId->ant = f->cabeca->ant;
			novoId->prox = f->cabeca;
			f->cabeca->ant = novoId;
		}
	}

	return true;
}

bool atenderPrimeiraDaFila(PFILA f, int* id){
	if ( f->cabeca->prox == f->cabeca ) return false;
	
	PONT primeiro = f->cabeca->prox;
	*id = primeiro->id;

	f->cabeca->prox = primeiro->prox;
	primeiro->prox->ant = f->cabeca;

	if(!primeiro->ehPreferencial) {
		f->inicioNaoPref = primeiro->prox;
	}

	free(primeiro);

	return true;
}


bool desistirDaFila(PFILA f, int id){
	PONT elemento = buscarID(f, id);
	
	if ( id>0 && elemento ) {
		PONT anterior = elemento->ant;
		PONT proximo = elemento->prox;

		anterior->prox = proximo;
		proximo->ant = anterior;

		if ( elemento == f->inicioNaoPref ) f->inicioNaoPref = elemento->prox;
		
		free(elemento);
		
		return true;
	}

	return false;
}
