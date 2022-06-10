public class Jogo {	

	public static void desenhaCena(Jogador jogador){

		// na versão final este metodo deverá desenhar o jogador,
		// na posição atual, em uma interface gráfica exibida em
		// uma janela. Por ora, vamos imprimir as coordenadas do
		// jogador na saída padrão.

		System.out.println("Posição do jogador: (" + jogador.getX() + ", " + jogador.getY() + ")");
	}

	public static void main(String [] args){

		boolean rodando = true;
		Jogador jogador = new Jogador(50, 50);
		TecladoFalso teclado = new TecladoFalso();

		desenhaCena(jogador);

		while(rodando){

			if(teclado.setaParaCimaPressionada()) jogador.moverParaCima();
			if(teclado.setaParaBaixoPressionada()) jogador.moverParaBaixo();
			if(teclado.setaParaEsquerdaPressionada()) jogador.moverParaEsquerda();
			if(teclado.setaParaDireitaPressionada()) jogador.moverParaDireita();
			if(teclado.EscPressionado()) {
				rodando = false;
				jogador.setX(0);
				jogador.setY(0);
			}
			desenhaCena(jogador);
		}

		System.out.println("Fim do jogo!");
	}
}
