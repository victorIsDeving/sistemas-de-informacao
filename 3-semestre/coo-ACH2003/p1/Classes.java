/*
	Considere as seguintes classes, envolvidas na implementação
	de um jogo que, em resumo, simula um ambiente bidimensional
	através do qual um jogador se movimenta:

	Ponto2D: classe de propósito geral que representa um ponto 
	bidimensional. Cada instancia desta classe possui dois 
	atributos: 'x' e 'y' que representam, respectivamente, as 
	coordenadas horizonal e vertical do ponto. A classe também 
	declara getters e setters públicos para os atributos.
	
	Jogador: classe que implementa o jogador em si. É criada
	através herança, tendo como classe base a classe Ponto2D
	(afinal, um objeto do tipo jogador deve possuir uma localização
	e o código herdado de Ponto2D representa essa informação),
	e implementa métodos que são responsáveis por implementar
	a movimentação do jogador através do ambiente. Esses métodos
	são chamados pelo programa principal como resposta ao
	pressionar das teclas pelo usuário.
	
	TecladoFalso: classe que serve apenas para o tornar o código 
	principal compilável, já que a parte de referente ao processamento 
	do input do usuário ainda não está implementada. Cada chamada de
	método "simula" o pressionar de uma tecla com uma determinada
	probabilidade.
	
	Jogo: programa principal do jogo. Apesar de estar inacabada é
	uma classe plenamnte funcional, servindo essencialmente para
	testar o funcionamento da classe Jogador e sua movimentação 
	pelo ambiente simulado.
*/

class Ponto2D {
	
	private int x, y;
	
	public Ponto2D(int x, int y){  //private constructor should be better for singleton classes
		
		setX(x); 
		setY(y); 
	}

	public int getX(){ 
	
		return x; 
	}

	public int getY() { 

		return y; 
	}

	// protected void setX(int x){ 

	// 	this.x = x;
	// }

	// protected void setY(int y){ 
	
	// 	this.y = y; 
	// }
}

class Jogador extends Ponto2D {

	public Jogador(int x, int y){ //private constructor should be better for singleton classes

		super(x, y);
	}
	
	public void moverParaCima(){

		setY(getY() + 1);
	}

	public void moverParaBaixo(){

		setY(getY() - 1);
	}

	public void moverParaEsquerda(){

		setX(getX() - 1);
	}

	public void moverParaDireita(){

		setX(getX() + 1);
	}
}

class TecladoFalso{

	public boolean setaParaCimaPressionada(){

		// ~50% de chance da seta para cima estar pressionada 
		return Math.random() > 0.5;   
	}

	public boolean setaParaBaixoPressionada(){

		// ~50% de chance da seta para baixo estar pressionada 
		return Math.random() > 0.5;
	}

	public boolean setaParaEsquerdaPressionada(){

		// ~80% de chance da seta para a esquerda estar pressionada  
		return Math.random() > 0.2;
	}

	public boolean setaParaDireitaPressionada(){

		// ~20% de chance da seta para a direita estar pressionada  
		return Math.random() > 0.8;
	}

	public boolean EscPressionado(){

		// ~10% de chance da tecla ESC estar pressionada 
		return Math.random() > 0.9;
	}
}

// public class Jogo {	

// 	public static void desenhaCena(Jogador jogador){

// 		// na versão final este metodo deverá desenhar o jogador,
// 		// na posição atual, em uma interface gráfica exibida em
// 		// uma janela. Por ora, vamos imprimir as coordenadas do
// 		// jogador na saída padrão.

// 		System.out.println("Posição do jogador: (" + jogador.getX() + ", " + jogador.getY() + ")");
// 	}

// 	public static void main(String [] args){

// 		boolean rodando = true;
// 		Jogador jogador = new Jogador(50, 50);
// 		TecladoFalso teclado = new TecladoFalso();

// 		desenhaCena(jogador);

// 		while(rodando){

// 			if(teclado.setaParaCimaPressionada()) jogador.moverParaCima();
// 			if(teclado.setaParaBaixoPressionada()) jogador.moverParaBaixo();
// 			if(teclado.setaParaEsquerdaPressionada()) jogador.moverParaEsquerda();
// 			if(teclado.setaParaDireitaPressionada()) jogador.moverParaDireita();
// 			if(teclado.EscPressionado()) {
// 				rodando = false;
// 				jogador.setX(0);
// 				jogador.setY(0);
// 			}
// 			desenhaCena(jogador);
// 		}

// 		System.out.println("Fim do jogo!");
// 	}
// }