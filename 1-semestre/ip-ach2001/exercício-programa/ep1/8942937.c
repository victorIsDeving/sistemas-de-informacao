/*********************************************************************/
/**   ACH2001 - Introducao a Programacao                            **/
/**   EACH-USP - Primeiro Semestre de 2021                          **/
/**   T94 - Luciano Digiampietri                                    **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   Victor Augusto Costa Monteiro                8942937          **/
/**                                                                 **/
/*********************************************************************/

/*
	Caixa eletronico das Ilhas Weblands, com estoque ilimitado de cedulas
	de B$50,00, B$20,00, B$5,00 e B$1,00.
*/

#include <stdio.h>

/* Numero de cedulas de B$50,00 */
int n50;
	
/* Numero de cedulas de B$20,00 */
int n20;

/* Numero de cedulas de B$5,00 */
int n5;
	
/* Numero de cedulas de B$1,00 */
int n1;


/*
	Determina a quantidade de cada nota necessaria para totalizar
	um determinado valor de retirada, de modo a minimizar a quantidade
	de cédulas entregues.
	
	Abastece as variaveis globais n50, n20, n5 e n1 com seu respectivo
	numero de cedulas.
	
	Parametro:
		valor - O valor a ser retirado
*/
void fazRetirada(int valor) {
	n50 = 0;
	n20 = 0;
	n5 = 0;
	n1 = 0;
	
	/** 
	 * Valores pré-definidos para 0, usando a construção do if para redefinir os valores
	 * conforme se encaixa no argumento da função
	 * 
	 * Contrução de um único if considerando intervalos para cada possibilidade de valor
	 * valor < 0
	 * valor >= 50
	 * 20 <= valor < 50
	 * 5 <= valor < 20
	 * 1 <= valor < 5 
	 * valor <1
	*/
	if (valor >= 50) {
		n50 = valor / 50;
		n20 = (valor - n50*50) / 20;
		n5 = (valor - (n50*50 + n20*20)) / 5;
		n1 = (valor - (n50*50 + n20*20 + n5*5));
	} else if (valor >= 20) {
		n20 = valor / 20;
		n5 = (valor - n20*20) / 5;
		n1 = (valor - (n20*20 + n5*5));
	} else if (valor >= 5) {
		n5 = valor / 5;
		n1 = (valor - n5*5);
	} else if (valor >= 1) {
		n1 = valor;
	} else if (valor < 1) {
		n50 = -1;
		n20 = -1;
		n5 = -1;
		n1 = -1;
	}
}



/*
	Funcao main apenas para seus testes. ISSO SERA IGNORADO NA CORRECAO
*/
int main() {
	/* escreva seu codigo (para testes) aqui */

	int valor;
	/* Testes para diferentes valores */
	// valor > 50
	valor = 279;
	fazRetirada(valor);
	printf("\nValor: %i\n",valor);
	printf("Notas de 50: %i\n", n50);
	printf("Notas de 20: %i\n", n20);
	printf("Notas de 5:  %i\n", n5);
	printf("Notas de 1:  %i\n", n1);

	// valor = 50
	valor = 50;
	fazRetirada(valor);
	printf("\nValor: %i\n",valor);
	printf("Notas de 50: %i\n", n50);
	printf("Notas de 20: %i\n", n20);
	printf("Notas de 5:  %i\n", n5);
	printf("Notas de 1:  %i\n", n1);

	// 20 < valor < 50
	valor = 43;
	fazRetirada(valor);
	printf("\nValor: %i\n",valor);
	printf("Notas de 50: %i\n", n50);
	printf("Notas de 20: %i\n", n20);
	printf("Notas de 5:  %i\n", n5);
	printf("Notas de 1:  %i\n", n1);

	// valor = 20
	valor = 20;
	fazRetirada(valor);
	printf("\nValor: %i\n",valor);
	printf("Notas de 50: %i\n", n50);
	printf("Notas de 20: %i\n", n20);
	printf("Notas de 5:  %i\n", n5);
	printf("Notas de 1:  %i\n", n1);

	// 5 < valor < 20
	valor = 17;
	fazRetirada(valor);
	printf("\nValor: %i\n",valor);
	printf("Notas de 50: %i\n", n50);
	printf("Notas de 20: %i\n", n20);
	printf("Notas de 5:  %i\n", n5);
	printf("Notas de 1:  %i\n", n1);

	// valor = 5
	valor = 5;
	fazRetirada(valor);
	printf("\nValor: %i\n",valor);
	printf("Notas de 50: %i\n", n50);
	printf("Notas de 20: %i\n", n20);
	printf("Notas de 5:  %i\n", n5);
	printf("Notas de 1:  %i\n", n1);

	// 1 < valor < 5
	valor = 4;
	fazRetirada(valor);
	printf("\nValor: %i\n",valor);
	printf("Notas de 50: %i\n", n50);
	printf("Notas de 20: %i\n", n20);
	printf("Notas de 5:  %i\n", n5);
	printf("Notas de 1:  %i\n", n1);

	// valor = 1
	valor = 1;
	fazRetirada(valor);
	printf("\nValor: %i\n",valor);
	printf("Notas de 50: %i\n", n50);
	printf("Notas de 20: %i\n", n20);
	printf("Notas de 5:  %i\n", n5);
	printf("Notas de 1:  %i\n", n1);

	// valor = 0
	valor = 0;
	fazRetirada(valor);
	printf("\nValor: %i\n",valor);
	printf("Notas de 50: %i\n", n50);
	printf("Notas de 20: %i\n", n20);
	printf("Notas de 5:  %i\n", n5);
	printf("Notas de 1:  %i\n", n1);

	// valor < 0
	valor = -21;
	fazRetirada(valor);
	printf("\nValor: %i\n",valor);
	printf("Notas de 50: %i\n", n50);
	printf("Notas de 20: %i\n", n20);
	printf("Notas de 5:  %i\n", n5);
	printf("Notas de 1:  %i\n", n1);

	return 0;
}