/*********************************************************************/
/**   ACH2001 - Introducao a Programacao                            **/
/**   EACH-USP - Primeiro Semestre de 2021                          **/
/**   94 - Luciano Antonio Digiampietri                             **/
/**                                                                 **/
/**   Terceiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   Victor Augusto Costa Monteiro      Nº USP 8942937             **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>

#define pecaX 'X'
#define pecaY 'O'
#define espacoVazio ' '

#define true 1
#define false 0

typedef int bool;


/*
	Jogo da Velha - programa para verificar o status de um jogo.

	Lista de Status calculado:
    0 - Jogo nao iniciado: o tabuleiro esta 'vazio', i.e., sem pecas X e O;
    1 - Jogo encerrado1: o primeiro jogador (que usa as pecas X) ganhou;
    2 - Jogo encerrado2: o segundo jogador (que usa as pecas O) ganhou;
    3 - Jogo encerrado3: empate - todas as casas do tabuleiro estao preenchidas com X e O, mas nenhum dos jogadores ganhou;
    4 - Jogo ja iniciado e em andamento: nenhuma das alternativas anteriores.	
*/

/*
	Determina o status de um partida de Jogo da Valha

	Entrada:
		tabuleiro - matriz 3x3 de caracteres representando uma partida valida de Jogo da Velha

	Saida:
		um inteiro contendo o status da partida (valores validos de zero a quatro)
*/

int verificaStatus(char tabuleiro[][3]) {
	int status;
    int countVazios = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == espacoVazio) {
                /**
                 * Contador de casas vazias no tabuleiro
                 * Cada casa que corresponda ao espacoVazio vai somar 1
                 * na variavel countVazios 
                */
                countVazios++;
            }
        }
    }

    if (countVazios == 9) {
        /**
         * Existem 9 casas no tabuleiro, se todas correspondem ao espacoVazio
         * entao o jogo ainda nao comecou 
        */
        status = 0;
    } else if ( ( tabuleiro[0][0] == pecaX && tabuleiro[1][1] == pecaX && tabuleiro[2][2] == pecaX ) || ( tabuleiro[0][2] == pecaX && tabuleiro[1][1] == pecaX && tabuleiro[2][0] == pecaX ) ) {
        /**
         * Checa se ou a diagonal principal ou a diagonal secundária estão
         * completas com a pecaX 
        */
        status = 1;
    } else if ( ( tabuleiro[0][0] == pecaY && tabuleiro[1][1] == pecaY && tabuleiro[2][2] == pecaY ) || ( tabuleiro[0][2] == pecaY && tabuleiro[1][1] == pecaY && tabuleiro[2][0] == pecaY ) ) {
        /**
         * Checa se ou a diagonal principal ou a diagonal secundária estão
         * completas com a pecaY 
        */
        status = 2;
    } else {

        /**
         * Aqui vai verificar se algum jogador venceu em alguma linha ou coluna
         * verificando linha a linha para X e depois Y
         * depois verificando coluna a coluna para X e depois Y
        */

        for (int i = 0; i < 3; i++) {
            if ( tabuleiro[i][0] == pecaX && tabuleiro[i][1] == pecaX && tabuleiro[i][2] == pecaX ) {  // todas as linhas para X
                status = 1;
                break;
            } else if ( tabuleiro[i][0] == pecaY && tabuleiro[i][1] == pecaY && tabuleiro[i][2] == pecaY ) {  // todas as linhas para Y
                status = 2;
                break;
            } else if ( tabuleiro[0][i] == pecaX && tabuleiro[1][i] == pecaX && tabuleiro[2][i] == pecaX ) {  // todas as colunas para X
                status = 1;
                break;
            } else if ( tabuleiro[0][i] == pecaY && tabuleiro[1][i] == pecaY && tabuleiro[2][i] == pecaY ) {  // todas as colunas para Y
                status = 2;
                break;
            } else if ( countVazios == 0 ) {
                /**
                 * Se nem o X nem o Y ganhou e não tem nenhum campo vazio no tabuleiro
                 * Então o jogo terminou empatado 
                */ 
                status = 3;
            } else {
                /**
                 * Nem o X nem o Y ganhou e ainda tem espaços vazios no tabuleiro
                 * Então o jogo ainda está em andamento
                */
                status = 4;
            }
        }
    }

	return status;
}

int main(){
	char tab0[][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
	char tab1[][3] = {{'X','X','X'},{'O','O',' '},{' ',' ',' '}};
	char tab11[][3] = {{'O','O','O'},{'X','X',' '},{' ',' ',' '}};
	char tab2[][3] = {{'O','X','X'},{'X','O','O'},{' ',' ','O'}};
	char tab21[][3] = {{'X','O','O'},{'O','X','X'},{' ',' ','X'}};
	char tab3[][3] = {{'O','X','X'},{'X','O','O'},{'O','X','X'}};
	char tab4[][3] = {{' ',' ',' '},{'X','O','X'},{' ',' ',' '}};
	char tab5[][3] = {{' ','X','O'},{'X','O','X'},{'O',' ',' '}};
	char tab51[][3] = {{' ','O','X'},{'O','X','O'},{'X',' ',' '}};
	char tab6[][3] = {{'O',' ','X'},{'O','X','X'},{'O',' ',' '}};
	char tab61[][3] = {{'X',' ','O'},{'X','O','O'},{'X',' ',' '}};

	printf("Status calculado: %i\n", verificaStatus(tab0)); // jogo não iniciado
	printf("Status esperado para o tabuleiro0: 0\n\n");

	printf("Status calculado: %i\n", verificaStatus(tab1)); // X ganha na primeira linha
	printf("Status esperado para o tabuleiro1: 1\n\n");

	printf("Status calculado: %i\n", verificaStatus(tab11)); // Y ganha na primeira linha
	printf("Status esperado para o tabuleiro11: 2\n\n");

	printf("Status calculado: %i\n", verificaStatus(tab2)); // Y ganha na diagonal principal
	printf("Status esperado para o tabuleiro2: 2\n\n");

	printf("Status calculado: %i\n", verificaStatus(tab21)); // X ganha na diagonal principal
	printf("Status esperado para o tabuleiro21: 1\n\n");
	
	printf("Status calculado: %i\n", verificaStatus(tab3)); // jogo empatado
	printf("Status esperado para o tabuleiro3: 3\n\n");
	
	printf("Status calculado: %i\n", verificaStatus(tab4)); // jogo incompleto
	printf("Status esperado para o tabuleiro4: 4\n\n");
	
	printf("Status calculado: %i\n", verificaStatus(tab5)); // Y ganha na diagonal secundária
	printf("Status esperado para o tabuleiro5: 2\n\n");
	
	printf("Status calculado: %i\n", verificaStatus(tab51)); // X ganha na diagonal secundária
	printf("Status esperado para o tabuleiro51: 1\n\n");
	
	printf("Status calculado: %i\n", verificaStatus(tab6)); // Y ganha na primeira coluna
	printf("Status esperado para o tabuleiro6: 2\n\n");
	
	printf("Status calculado: %i\n", verificaStatus(tab61)); // X ganha na primeira coluna
	printf("Status esperado para o tabuleiro61: 1\n\n");
	
	return 0;
}


/* SAIDA ESPERADA:

Status calculado: 0
Status esperado para o tabuleiro0: 0

Status calculado: 1
Status esperado para o tabuleiro1: 1

Status calculado: 2
Status esperado para o tabuleiro11: 2

Status calculado: 2
Status esperado para o tabuleiro2: 2

Status calculado: 1
Status esperado para o tabuleiro21: 1

Status calculado: 3
Status esperado para o tabuleiro3: 3

Status calculado: 4
Status esperado para o tabuleiro4: 4

Status calculado: 2
Status esperado para o tabuleiro5: 2

Status calculado: 1
Status esperado para o tabuleiro51: 1

*/