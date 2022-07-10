import java.awt.Color;

/***********************************************************************/
/*                                                                     */
/* Para jogar:                                                         */
/*                                                                     */
/*    - cima, baixo, esquerda, direita: movimentação do player.        */
/*    - control: disparo de projéteis.                                 */
/*    - ESC: para sair do jogo.                                        */
/*                                                                     */
/***********************************************************************/

class Player {
	int state;						// estado
	double cord_X;					// coordenada x
	double cord_Y;				   // coordenada y
	double speed_X;						// velocidade no eixo x
	double speed_Y;						// velocidade no eixo y
	double radius;						// raio (tamanho aproximado do player)	
	double explosion_start = 0;					// instante do início da explosão
	double explosion_end = 0;					// instante do final da explosão
	long next_shot;					// instante a partir do qual pode haver um próximo tiro

	Player (int initState, double cordX, double cordY, double speedX, double speedY, double radius, long nextShot){
		this.state = initState;
		this.cord_X = cordX;
		this.cord_Y = cordY;
		this.speed_X = speedX;
		this.speed_Y = speedY;
		this.radius = radius;
		this.next_shot = nextShot;
	}

	//setter/getter states
	public void setState(int state) {
		this.state = state;
	}

	public int getState() {
		return this.state;
	}

	//setter/getter coordenadas X
	public void setCordX(double cord_X) {
		this.cord_X = cord_X;
	}

	public double getCordX() {
		return this.cord_X;
	}

	//setter/getter coordenadas Y
	public void setCordY(double cord_Y) {
		this.cord_Y = cord_Y;
	}

	public double getCordY() {
		return this.cord_Y;
	}

	//getter radius
	public double getRadius() {
		return this.radius;
	}

	//setter/getter explosion start
	public void setExplosionStart(long start) {
		this.explosion_start = start;
	}

	public double getExplosionStart() {
		return this.explosion_start;
	}

	//setter/getter explosion end
	public void setExplosionEnd(long end) {
		this.explosion_end = end;
	}

	public double getExplosionEnd() {
		return this.explosion_end;
	}

	//setter/getter speed X
	public void setVX(double speedX) {
		this.speed_X = speedX;
	}

	public double getVX() {
		return this.speed_X;
	}

	//setter/getter speed Y
	public void setVY(double speedY) {
		this.speed_Y = speedY;
	}

	public double getVY() {
		return this.speed_Y;
	}

	//setter/getter next shot
	public void setNextShot(long nextShot) {
		this.next_shot = nextShot;
	}

	public long getNextShot() {
		return this.next_shot;
	}
}

class Enemy {
	int [] state = new int[10];					// estados
	double [] cord_X = new double[10];					// coordenadas x
	double [] cord_Y = new double[10];					// coordenadas y
	double [] speed = new double[10];					// velocidades
	double [] angle = new double[10];				// ângulos (indicam direção do movimento)
	double [] rotation_speed = new double[10];					// velocidades de rotação
	double [] explosion_start = new double[10];			// instantes dos inícios das explosões
	double [] explosion_end = new double[10];			// instantes dos finais da explosões
	long [] next_shot = new long[10];				// instantes do próximo tiro
	double radius;						// raio (tamanho do inimigo)
	long next_enemy;					// instante em que um novo inimigo deve aparecer

	double spawn_X;				// coordenada x do próximo inimigo tipo 2 a aparecer
	int count;							// contagem de inimigos tipo 2 (usada na "formação de voo")

	Enemy (int state, double radius, long nextEnemy) {
		this.radius = radius;
		this.next_enemy = nextEnemy;
		for(int i = 0; i < 10; i++) this.state[i] = state;
	}
}
public class Main {
	
	/* Constantes relacionadas aos estados que os elementos   */
	/* do jogo (player, projeteis ou inimigos) podem assumir. */
	
	public static final int INACTIVE = 0;
	public static final int ACTIVE = 1;
	public static final int EXPLODING = 2;
	
	/* Espera, sem fazer nada, até que o instante de tempo atual seja */
	/* maior ou igual ao instante especificado no parâmetro "time.    */
	
	public static void busyWait(long time){
		
		while(System.currentTimeMillis() < time) Thread.yield();
	}
	
	/* Encontra e devolve o primeiro índice do  */
	/* array referente a uma posição "inativa". */
	
	public static int findFreeIndex(int [] stateArray){
		
		int i;
		
		for(i = 0; i < stateArray.length; i++){
			
			if(stateArray[i] == INACTIVE) break;
		}
		
		return i;
	}
	
	/* Encontra e devolve o conjunto de índices (a quantidade */
	/* de índices é defnida através do parâmetro "amount") do */
	/* array referente a posições "inativas".                 */ 

	public static int [] findFreeIndex(int [] stateArray, int amount){

		int i, k;
		int [] freeArray = new int[amount];

		for(i = 0; i < freeArray.length; i++) freeArray[i] = stateArray.length; 
		
		for(i = 0, k = 0; i < stateArray.length && k < amount; i++){
				
			if(stateArray[i] == INACTIVE) { 
				
				freeArray[k] = i; 
				k++;
			}
		}
		
		return freeArray;
	}
	
	/* Método principal */
	
	public static void main(String [] args){

		/* Indica que o jogo está em execução */

		boolean running = true;

		/* variáveis usadas no controle de tempo efetuado no main loop */
		
		long delta;
		long currentTime = System.currentTimeMillis();

		/* variáveis do player */
		Player player = new Player(ACTIVE, GameLib.WIDTH / 2, GameLib.HEIGHT * 0.90, 0.25, 0.25, 12.0, currentTime);

		/* variáveis dos projéteis disparados pelo player */
		
		int [] projectile_states = new int[10];					// estados
		double [] projectile_X = new double[10];				// coordenadas x
		double [] projectile_Y = new double[10];				// coordenadas y
		double [] projectile_VX = new double[10];				// velocidades no eixo x
		double [] projectile_VY = new double[10];				// velocidades no eixo y

		/* variáveis dos inimigos tipo 1 */
		Enemy enemy1 = new Enemy(INACTIVE, 9.0, currentTime+2000);

		/* variáveis dos inimigos tipo 2 */
		Enemy enemy2 = new Enemy(INACTIVE, 12.0, currentTime+7000);
		int [] enemy2_states = new int[10];					// estados
		double [] enemy2_X = new double[10];					// coordenadas x
		double [] enemy2_Y = new double[10];					// coordenadas y
		double [] enemy2_V = new double[10];					// velocidades
		double [] enemy2_angle = new double[10];				// ângulos (indicam direção do movimento)
		double [] enemy2_RV = new double[10];					// velocidades de rotação
		double [] enemy2_explosion_start = new double[10];			// instantes dos inícios das explosões
		double [] enemy2_explosion_end = new double[10];			// instantes dos finais das explosões
		double enemy2_spawnX = GameLib.WIDTH * 0.20;				// coordenada x do próximo inimigo tipo 2 a aparecer
		int enemy2_count = 0;							// contagem de inimigos tipo 2 (usada na "formação de voo")
		double enemy2_radius = 12.0;						// raio (tamanho aproximado do inimigo 2)
		long nextEnemy2 = currentTime + 7000;					// instante em que um novo inimigo 2 deve aparecer
		
		/* variáveis dos projéteis lançados pelos inimigos (tanto tipo 1, quanto tipo 2) */
		
		int [] e_projectile_states = new int[200];				// estados
		double [] e_projectile_X = new double[200];				// coordenadas x
		double [] e_projectile_Y = new double[200];				// coordenadas y
		double [] e_projectile_VX = new double[200];				// velocidade no eixo x
		double [] e_projectile_VY = new double[200];				// velocidade no eixo y
		double e_projectile_radius = 2.0;					// raio (tamanho dos projéteis inimigos)
		
		/* estrelas que formam o fundo de primeiro plano */
		
		double [] background1_X = new double[20];
		double [] background1_Y = new double[20];
		double background1_speed = 0.070;
		double background1_count = 0.0;
		
		/* estrelas que formam o fundo de segundo plano */
		
		double [] background2_X = new double[50];
		double [] background2_Y = new double[50];
		double background2_speed = 0.045;
		double background2_count = 0.0;
		
		/* inicializações */
		
		for(int i = 0; i < projectile_states.length; i++) projectile_states[i] = INACTIVE;
		for(int i = 0; i < e_projectile_states.length; i++) e_projectile_states[i] = INACTIVE;
		for(int i = 0; i < enemy2_states.length; i++) enemy2_states[i] = INACTIVE;
		
		for(int i = 0; i < background1_X.length; i++){
			
			background1_X[i] = Math.random() * GameLib.WIDTH;
			background1_Y[i] = Math.random() * GameLib.HEIGHT;
		}
		
		for(int i = 0; i < background2_X.length; i++){
			
			background2_X[i] = Math.random() * GameLib.WIDTH;
			background2_Y[i] = Math.random() * GameLib.HEIGHT;
		}
						
		/* iniciado interface gráfica */
		
		GameLib.initGraphics();
		//GameLib.initGraphics_SAFE_MODE();  // chame esta versão do método caso nada seja desenhado na janela do jogo.
		
		/*************************************************************************************************/
		/*                                                                                               */
		/* Main loop do jogo                                                                             */
		/* -----------------                                                                             */
		/*                                                                                               */
		/* O main loop do jogo executa as seguintes operações:                                           */
		/*                                                                                               */
		/* 1) Verifica se há colisões e atualiza estados dos elementos conforme a necessidade.           */
		/*                                                                                               */
		/* 2) Atualiza estados dos elementos baseados no tempo que correu entre a última atualização     */
		/*    e o timestamp atual: posição e orientação, execução de disparos de projéteis, etc.         */
		/*                                                                                               */
		/* 3) Processa entrada do usuário (teclado) e atualiza estados do player conforme a necessidade. */
		/*                                                                                               */
		/* 4) Desenha a cena, a partir dos estados dos elementos.                                        */
		/*                                                                                               */
		/* 5) Espera um período de tempo (de modo que delta seja aproximadamente sempre constante).      */
		/*                                                                                               */
		/*************************************************************************************************/
		
		while(running){
		
			/* Usada para atualizar o estado dos elementos do jogo    */
			/* (player, projéteis e inimigos) "delta" indica quantos  */
			/* ms se passaram desde a última atualização.             */
			
			delta = System.currentTimeMillis() - currentTime;
			
			/* Já a variável "currentTime" nos dá o timestamp atual.  */
			
			currentTime = System.currentTimeMillis();
			
			/***************************/
			/* Verificação de colisões */
			/***************************/
						
			if(player.getState() == ACTIVE){
				
				/* colisões player - projeteis (inimigo) */
				
				for(int i = 0; i < e_projectile_states.length; i++){
					
					double dx = e_projectile_X[i] - player.getCordX();
					double dy = e_projectile_Y[i] - player.getCordY();
					double dist = Math.sqrt(dx * dx + dy * dy);
					
					if(dist < (player.getRadius() + e_projectile_radius) * 0.8){
						
						player.setState(EXPLODING);
						player.setExplosionStart(currentTime);
						player.setExplosionEnd(currentTime + 2000);
					}
				}
			
				/* colisões player - inimigos */
							
				for(int i = 0; i < enemy1.state.length; i++){
					
					double dx = enemy1.cord_X[i] - player.getCordX();
					double dy = enemy1.cord_Y[i] - player.getCordY();
					double dist = Math.sqrt(dx * dx + dy * dy);
					
					if(dist < (player.getRadius() + enemy1.radius) * 0.8){
						
						player.setState(EXPLODING);
						player.setExplosionStart(currentTime);
						player.setExplosionEnd(currentTime + 2000);
					}
				}
				
				for(int i = 0; i < enemy2_states.length; i++){
					
					double dx = enemy2_X[i] - player.getCordX();
					double dy = enemy2_Y[i] - player.getCordY();
					double dist = Math.sqrt(dx * dx + dy * dy);
					
					if(dist < (player.getRadius() + enemy2_radius) * 0.8){
						
						player.setState(EXPLODING);
						player.setExplosionStart(currentTime);
						player.setExplosionEnd(currentTime + 2000);
					}
				}
			}
			
			/* colisões projeteis (player) - inimigos */
			
			for(int k = 0; k < projectile_states.length; k++){
				
				for(int i = 0; i < enemy1.state.length; i++){
										
					if(enemy1.state[i] == ACTIVE){
					
						double dx = enemy1.cord_X[i] - projectile_X[k];
						double dy = enemy1.cord_Y[i] - projectile_Y[k];
						double dist = Math.sqrt(dx * dx + dy * dy);
						
						if(dist < enemy1.radius){
							
							enemy1.state[i] = EXPLODING;
							enemy1.explosion_start[i] = currentTime;
							enemy1.explosion_end[i] = currentTime + 500;
						}
					}
				}
				
				for(int i = 0; i < enemy2_states.length; i++){
					
					if(enemy2_states[i] == ACTIVE){
						
						double dx = enemy2_X[i] - projectile_X[k];
						double dy = enemy2_Y[i] - projectile_Y[k];
						double dist = Math.sqrt(dx * dx + dy * dy);
						
						if(dist < enemy2_radius){
							
							enemy2_states[i] = EXPLODING;
							enemy2_explosion_start[i] = currentTime;
							enemy2_explosion_end[i] = currentTime + 500;
						}
					}
				}
			}
				
			/***************************/
			/* Atualizações de estados */
			/***************************/
			
			/* projeteis (player) */
			
			for(int i = 0; i < projectile_states.length; i++){
				
				if(projectile_states[i] == ACTIVE){
					
					/* verificando se projétil saiu da tela */
					if(projectile_Y[i] < 0) {
						
						projectile_states[i] = INACTIVE;
					}
					else {
					
						projectile_X[i] += projectile_VX[i] * delta;
						projectile_Y[i] += projectile_VY[i] * delta;
					}
				}
			}
			
			/* projeteis (inimigos) */
			
			for(int i = 0; i < e_projectile_states.length; i++){
				
				if(e_projectile_states[i] == ACTIVE){
					
					/* verificando se projétil saiu da tela */
					if(e_projectile_Y[i] > GameLib.HEIGHT) {
						
						e_projectile_states[i] = INACTIVE;
					}
					else {
					
						e_projectile_X[i] += e_projectile_VX[i] * delta;
						e_projectile_Y[i] += e_projectile_VY[i] * delta;
					}
				}
			}
			
			/* inimigos tipo 1 */
			
			for(int i = 0; i < enemy1.state.length; i++){
				
				if(enemy1.state[i] == EXPLODING){
					
					if(currentTime > enemy1.explosion_end[i]){
						
						enemy1.state[i] = INACTIVE;
					}
				}
				
				if(enemy1.state[i] == ACTIVE){
					
					/* verificando se inimigo saiu da tela */
					if(enemy1.cord_Y[i] > GameLib.HEIGHT + 10) {
						
						enemy1.state[i] = INACTIVE;
					}
					else {
					
						enemy1.cord_X[i] += enemy1.speed[i] * Math.cos(enemy1.angle[i]) * delta;
						enemy1.cord_Y[i] += enemy1.speed[i] * Math.sin(enemy1.angle[i]) * delta * (-1.0);
						enemy1.angle[i] += enemy1.rotation_speed[i] * delta;
						
						if(currentTime > enemy1.next_shot[i] && enemy1.cord_Y[i] < player.getCordY()){
																							
							int free = findFreeIndex(e_projectile_states);
							
							if(free < e_projectile_states.length){
								
								e_projectile_X[free] = enemy1.cord_X[i];
								e_projectile_Y[free] = enemy1.cord_Y[i];
								e_projectile_VX[free] = Math.cos(enemy1.angle[i]) * 0.45;
								e_projectile_VY[free] = Math.sin(enemy1.angle[i]) * 0.45 * (-1.0);
								e_projectile_states[free] = ACTIVE;
								
								enemy1.next_shot[i] = (long) (currentTime + 200 + Math.random() * 500);
							}
						}
					}
				}
			}
			
			/* inimigos tipo 2 */
			
			for(int i = 0; i < enemy2_states.length; i++){
				
				if(enemy2_states[i] == EXPLODING){
					
					if(currentTime > enemy2_explosion_end[i]){
						
						enemy2_states[i] = INACTIVE;
					}
				}
				
				if(enemy2_states[i] == ACTIVE){
					
					/* verificando se inimigo saiu da tela */
					if(	enemy2_X[i] < -10 || enemy2_X[i] > GameLib.WIDTH + 10 ) {
						
						enemy2_states[i] = INACTIVE;
					}
					else {
						
						boolean shootNow = false;
						double previousY = enemy2_Y[i];
												
						enemy2_X[i] += enemy2_V[i] * Math.cos(enemy2_angle[i]) * delta;
						enemy2_Y[i] += enemy2_V[i] * Math.sin(enemy2_angle[i]) * delta * (-1.0);
						enemy2_angle[i] += enemy2_RV[i] * delta;
						
						double threshold = GameLib.HEIGHT * 0.30;
						
						if(previousY < threshold && enemy2_Y[i] >= threshold) {
							
							if(enemy2_X[i] < GameLib.WIDTH / 2) enemy2_RV[i] = 0.003;
							else enemy2_RV[i] = -0.003;
						}
						
						if(enemy2_RV[i] > 0 && Math.abs(enemy2_angle[i] - 3 * Math.PI) < 0.05){
							
							enemy2_RV[i] = 0.0;
							enemy2_angle[i] = 3 * Math.PI;
							shootNow = true;
						}
						
						if(enemy2_RV[i] < 0 && Math.abs(enemy2_angle[i]) < 0.05){
							
							enemy2_RV[i] = 0.0;
							enemy2_angle[i] = 0.0;
							shootNow = true;
						}
																		
						if(shootNow){

							double [] angles = { Math.PI/2 + Math.PI/8, Math.PI/2, Math.PI/2 - Math.PI/8 };
							int [] freeArray = findFreeIndex(e_projectile_states, angles.length);

							for(int k = 0; k < freeArray.length; k++){
								
								int free = freeArray[k];
								
								if(free < e_projectile_states.length){
									
									double a = angles[k] + Math.random() * Math.PI/6 - Math.PI/12;
									double vx = Math.cos(a);
									double vy = Math.sin(a);
										
									e_projectile_X[free] = enemy2_X[i];
									e_projectile_Y[free] = enemy2_Y[i];
									e_projectile_VX[free] = vx * 0.30;
									e_projectile_VY[free] = vy * 0.30;
									e_projectile_states[free] = ACTIVE;
								}
							}
						}
					}
				}
			}
			
			/* verificando se novos inimigos (tipo 1) devem ser "lançados" */
			
			if(currentTime > enemy1.next_enemy){
				
				int free = findFreeIndex(enemy1.state);
								
				if(free < enemy1.state.length){
					
					enemy1.cord_X[free] = Math.random() * (GameLib.WIDTH - 20.0) + 10.0;
					enemy1.cord_Y[free] = -10.0;
					enemy1.speed[free] = 0.20 + Math.random() * 0.15;
					enemy1.angle[free] = (3 * Math.PI) / 2;
					enemy1.rotation_speed[free] = 0.0;
					enemy1.state[free] = ACTIVE;
					enemy1.next_shot[free] = currentTime + 500;
					enemy1.next_enemy = currentTime + 500;
				}
			}
			
			/* verificando se novos inimigos (tipo 2) devem ser "lançados" */
			
			if(currentTime > nextEnemy2){
				
				int free = findFreeIndex(enemy2_states);
								
				if(free < enemy2_states.length){
					
					enemy2_X[free] = enemy2_spawnX;
					enemy2_Y[free] = -10.0;
					enemy2_V[free] = 0.42;
					enemy2_angle[free] = (3 * Math.PI) / 2;
					enemy2_RV[free] = 0.0;
					enemy2_states[free] = ACTIVE;

					enemy2_count++;
					
					if(enemy2_count < 10){
						
						nextEnemy2 = currentTime + 120;
					}
					else {
						
						enemy2_count = 0;
						enemy2_spawnX = Math.random() > 0.5 ? GameLib.WIDTH * 0.2 : GameLib.WIDTH * 0.8;
						nextEnemy2 = (long) (currentTime + 3000 + Math.random() * 3000);
					}
				}
			}
			
			/* Verificando se a explosão do player já acabou.         */
			/* Ao final da explosão, o player volta a ser controlável */
			if(player.getState() == EXPLODING){
				
				if(currentTime > player.getExplosionEnd()){
					
					player.setState(ACTIVE);
				}
			}
			
			/********************************************/
			/* Verificando entrada do usuário (teclado) */
			/********************************************/
			
			if(player.getState() == ACTIVE){
				if(GameLib.iskeyPressed(GameLib.KEY_UP)) player.setCordY(player.getCordY() - delta * player.getVY());
				if(GameLib.iskeyPressed(GameLib.KEY_DOWN)) player.setCordY(player.getCordY() + delta * player.getVY());
				if(GameLib.iskeyPressed(GameLib.KEY_LEFT)) player.setCordX(player.getCordX() - delta * player.getVX());
				if(GameLib.iskeyPressed(GameLib.KEY_RIGHT)) player.setCordX(player.getCordX() + delta * player.getVX());
				
				if(GameLib.iskeyPressed(GameLib.KEY_CONTROL)) {
					
					if(currentTime > player.getNextShot()){
						
						int free = findFreeIndex(projectile_states);
												
						if(free < projectile_states.length){
							
							projectile_X[free] = player.getCordX();
							projectile_Y[free] = player.getCordY() - 2 * player.getRadius();
							projectile_VX[free] = 0.0;
							projectile_VY[free] = -1.0;
							projectile_states[free] = ACTIVE;
							player.setNextShot(currentTime+100);
						}
					}	
				}
			}
			
			if(GameLib.iskeyPressed(GameLib.KEY_ESCAPE)) running = false;
			
			/* Verificando se coordenadas do player ainda estão dentro */
			/* da tela de jogo após processar entrada do usuário.      */
			
			if(player.getCordX() < 0.0) player.setCordX(0.0);
			if(player.getCordX() >= GameLib.WIDTH) player.setCordX(GameLib.WIDTH - 1);
			if(player.getCordY() < 25.0) player.setCordY(25.0);
			if(player.getCordY() >= GameLib.HEIGHT) player.setCordY(GameLib.HEIGHT - 1);

			/*******************/
			/* Desenho da cena */
			/*******************/
			
			/* desenhando plano fundo distante */
			
			GameLib.setColor(Color.DARK_GRAY);
			background2_count += background2_speed * delta;
			
			for(int i = 0; i < background2_X.length; i++){
				
				GameLib.fillRect(background2_X[i], (background2_Y[i] + background2_count) % GameLib.HEIGHT, 2, 2);
			}
			
			/* desenhando plano de fundo próximo */
			
			GameLib.setColor(Color.GRAY);
			background1_count += background1_speed * delta;
			
			for(int i = 0; i < background1_X.length; i++){
				
				GameLib.fillRect(background1_X[i], (background1_Y[i] + background1_count) % GameLib.HEIGHT, 3, 3);
			}
						
			/* desenhando player */
			
			if(player.getState() == EXPLODING){
				
				double alpha = (currentTime - player.getExplosionStart()) / (player.getExplosionEnd() - player.getExplosionStart());
				GameLib.drawExplosion(player.getCordX(), player.getCordY(), alpha);
			}
			else{
				
				GameLib.setColor(Color.BLUE);
				GameLib.drawPlayer(player.getCordX(), player.getCordY(), player.getRadius());
			}
				
			/* deenhando projeteis (player) */
			
			for(int i = 0; i < projectile_states.length; i++){
				
				if(projectile_states[i] == ACTIVE){
					
					GameLib.setColor(Color.GREEN);
					GameLib.drawLine(projectile_X[i], projectile_Y[i] - 5, projectile_X[i], projectile_Y[i] + 5);
					GameLib.drawLine(projectile_X[i] - 1, projectile_Y[i] - 3, projectile_X[i] - 1, projectile_Y[i] + 3);
					GameLib.drawLine(projectile_X[i] + 1, projectile_Y[i] - 3, projectile_X[i] + 1, projectile_Y[i] + 3);
				}
			}
			
			/* desenhando projeteis (inimigos) */
		
			for(int i = 0; i < e_projectile_states.length; i++){
				
				if(e_projectile_states[i] == ACTIVE){
	
					GameLib.setColor(Color.RED);
					GameLib.drawCircle(e_projectile_X[i], e_projectile_Y[i], e_projectile_radius);
				}
			}
			
			/* desenhando inimigos (tipo 1) */
			
			for(int i = 0; i < enemy1.state.length; i++){
				
				if(enemy1.state[i] == EXPLODING){
					
					double alpha = (currentTime - enemy1.explosion_start[i]) / (enemy1.explosion_end[i] - enemy1.explosion_start[i]);
					GameLib.drawExplosion(enemy1.cord_X[i], enemy1.cord_Y[i], alpha);
				}
				
				if(enemy1.state[i] == ACTIVE){
			
					GameLib.setColor(Color.CYAN);
					GameLib.drawCircle(enemy1.cord_X[i], enemy1.cord_Y[i], enemy1.radius);
				}
			}
			
			/* desenhando inimigos (tipo 2) */
			
			for(int i = 0; i < enemy2_states.length; i++){
				
				if(enemy2_states[i] == EXPLODING){
					
					double alpha = (currentTime - enemy2_explosion_start[i]) / (enemy2_explosion_end[i] - enemy2_explosion_start[i]);
					GameLib.drawExplosion(enemy2_X[i], enemy2_Y[i], alpha);
				}
				
				if(enemy2_states[i] == ACTIVE){
			
					GameLib.setColor(Color.MAGENTA);
					GameLib.drawDiamond(enemy2_X[i], enemy2_Y[i], enemy2_radius);
				}
			}
			
			/* chamada a display() da classe GameLib atualiza o desenho exibido pela interface do jogo. */
			
			GameLib.display();
			
			/* faz uma pausa de modo que cada execução do laço do main loop demore aproximadamente 3 ms. */
			
			busyWait(currentTime + 3);
		}
		
		System.exit(0);
	}
}
