/*********************************************************************/
/**   ACH2001 - Introducao a Programacao                            **/
/**   EACH-USP - Primeiro Semestre de 2021                          **/
/**   94 - Luciano Digiampietri                                     **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   Victor Augusto Costa Monteiro              8942937            **/
/**                                                                 **/
/*********************************************************************/

/*
	Calculo para raiz quadrada
*/

#include <stdio.h>

/*
	Calcula a raiz quadrada de um valor, com uma determinada
	precisao. Retorna esse valor, ou -1 quando:
	
	* a < 0
	* epsilon <= 0
	* epsilon >= 1
	
	Parametro:
		a - valor cuja raiz quadrada sera calculada
		epsilon - precisao do calculo
*/
double raizQuadrada(double a, double epsilon) {
	double resposta;
    double valor = a/2; // valor inicial x0
    double valorSeguinte; // valor x(i+1)
    double diferenca;
    // int iteracoes = 0; // variavel para calculo de iteracoes feitas para chegar no resultado

	if ( a >= 0 && epsilon < 1 && epsilon > 0 )  {

        do {
            valorSeguinte = 0.5*(valor + a/valor); // formula para calculo do x(i+1)

            /**
             * O if abaixo é para o módulo da diferença |x(i+1)-x(i)|
             * caso x(i+1)>=x(i) então o módulo é x(i+1)-x(i)
             * se não, ou seja, x(i)>x(i+1), então o módulo é -x(i+1)+x(i) = x(i)-x(i+1)
            */ 
            if( valorSeguinte >= valor ) {
                diferenca = valorSeguinte - valor;
            } else {
                diferenca = valor - valorSeguinte;
            }

            valor = valorSeguinte; // coloca o valor x(i+1) como x(i) para realizar as iteracoes
            
            // iteracoes++; // incremento na variável da quantidade de iteracoes a cada iteracao feita

        } while ( diferenca >= epsilon ); // condição para continuar realizando as iteracoes

        resposta = valor;

    } else {
        resposta = -1; // resposta para qualquer a<0 ou epsilon<=0 ou epsilon>=1
    }

    // printf("Iteracoes feitas: %i. ", iteracoes); // imprime também a quantidade de iteracoes feitas para cada calculo de raiz

	return resposta;
}


/*
	Apenas para seus testes. ISSO SERA IGNORADO NA CORRECAO
*/
int main() {

	/* escreva seu codigo (para testes) aqui */

	double valor = 63;
	double precisao = 0.001;
	printf("Raiz aproximada de %f com epsilon %f é %.20f\n", valor, precisao, raizQuadrada(valor, precisao));
	
    valor = 63;
	precisao = 0.000001;
	printf("Raiz aproximada de %f com epsilon %f é %.20f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = 2;
	precisao = 0.001;
	printf("Raiz aproximada de %f com epsilon %f é %.20f\n", valor, precisao, raizQuadrada(valor, precisao));
	
    valor = 2;
	precisao = 0.000001;
	printf("Raiz aproximada de %f com epsilon %f é %.20f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = 3;
	precisao = 0.001;
	printf("Raiz aproximada de %f com epsilon %f é %.20f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = 3;
	precisao = 0.000001;
	printf("Raiz aproximada de %f com epsilon %f é %.20f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = 81;
	precisao = 0.001;
	printf("Raiz aproximada de %f com epsilon %f é %f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = 16;
	precisao = 0.001;
	printf("Raiz aproximada de %f com epsilon %f é %f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = 9;
	precisao = 0.001;
	printf("Raiz aproximada de %f com epsilon %f é %f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = 4;
	precisao = 0.001;
	printf("Raiz aproximada de %f com epsilon %f é %f\n", valor, precisao, raizQuadrada(valor, precisao));

    // testes de erros
    printf("\nTestes para erros\n");

	valor = 63;
	precisao = 1.1;
	printf("Raiz aproximada de %f com epsilon %f é %f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = 63;
	precisao = 1;
	printf("Raiz aproximada de %f com epsilon %f é %f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = 63;
	precisao = 0;
	printf("Raiz aproximada de %f com epsilon %f é %f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = 63;
	precisao = -1;
	printf("Raiz aproximada de %f com epsilon %f é %f\n", valor, precisao, raizQuadrada(valor, precisao));

	valor = -3;
	precisao = 0.001;
	printf("Raiz aproximada de %f com epsilon %f é %f\n", valor, precisao, raizQuadrada(valor, precisao));

	return 0;
}