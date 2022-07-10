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

class EnemyBasic {
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

	EnemyBasic (int state, double radius, long nextEnemy) {
		this.radius = radius;
		this.next_enemy = nextEnemy;
		for(int i = 0; i < this.state.length; i++) this.state[i] = state;
	}
}

class EnemyArmada extends EnemyBasic {
	double spawn_X;				// coordenada x do próximo inimigo tipo 2 a aparecer
	int count;							// contagem de inimigos tipo 2 (usada na "formação de voo")
	
	EnemyArmada (int state, double radius, long nextEnemy, double spawnX, int enemyCount) {
		super(state, radius, nextEnemy);
		spawn_X = spawnX;
		count = enemyCount;
	}
}

class ProjectileBasic {
	
	int [] states = new int[10];					// estados
	double [] cord_X = new double[10];				// coordenadas x
	double [] cord_Y = new double[10];				// coordenadas y
	double [] speed_X = new double[10];				// velocidades no eixo x
	double [] speed_Y = new double[10];				// velocidades no eixo y

	ProjectileBasic (int states) {
		for(int i = 0; i < this.states.length; i++) this.states[i] = states;
	}
}

class ProjectileRadius extends ProjectileBasic {

	double radius;					// raio (tamanho dos projéteis inimigos)

	ProjectileRadius (int states, double radius) {
		super(states);
		this.radius = radius;
	} 
}

class Background {

	double [] x;
	double [] y;
	double speed;
	double count;

	Background (int arraySize, double speed, double count) {
		this.x = new double[arraySize];
		this.y = new double[arraySize];
		this.speed = speed;
		this.count = count;

		for(int i = 0; i < arraySize; i++){
			
			this.x[i] = Math.random() * GameLib.WIDTH;
			this.y[i] = Math.random() * GameLib.HEIGHT;
		}
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
		ProjectileBasic player_projectile = new ProjectileBasic(INACTIVE);

		/* variáveis dos inimigos tipo 1 */
		EnemyBasic enemy1 = new EnemyBasic(INACTIVE, 9.0, currentTime+2000);

		/* variáveis dos inimigos tipo 2 */
		EnemyArmada enemy2 = new EnemyArmada(INACTIVE, 12.0, currentTime+7000, GameLib.WIDTH * 0.20, 0);
	
		/* variáveis dos projéteis lançados pelos inimigos (tanto tipo 1, quanto tipo 2) */
		ProjectileRadius enemy_projectile = new ProjectileRadius(INACTIVE, 2.0);
		
		/* estrelas que formam o fundo de primeiro plano */
		Background background1 = new Background(20, 0.070, 0.0);
		
		/* estrelas que formam o fundo de segundo plano */
		Background background2 = new Background(50, 0.045, 0.0);
						
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
				
				for(int i = 0; i < enemy_projectile.states.length; i++){
					
					double dx = enemy_projectile.cord_X[i] - player.getCordX();
					double dy = enemy_projectile.cord_Y[i] - player.getCordY();
					double dist = Math.sqrt(dx * dx + dy * dy);
					
					if(dist < (player.getRadius() + enemy_projectile.radius) * 0.8){
						
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
				
				for(int i = 0; i < enemy2.state.length; i++){
					
					double dx = enemy2.cord_X[i] - player.getCordX();
					double dy = enemy2.cord_Y[i] - player.getCordY();
					double dist = Math.sqrt(dx * dx + dy * dy);
					
					if(dist < (player.getRadius() + enemy2.radius) * 0.8){
						
						player.setState(EXPLODING);
						player.setExplosionStart(currentTime);
						player.setExplosionEnd(currentTime + 2000);
					}
				}
			}
			
			/* colisões projeteis (player) - inimigos */
			
			for(int k = 0; k < player_projectile.states.length; k++){
				
				for(int i = 0; i < enemy1.state.length; i++){
										
					if(enemy1.state[i] == ACTIVE){
					
						double dx = enemy1.cord_X[i] - player_projectile.cord_X[k];
						double dy = enemy1.cord_Y[i] - player_projectile.cord_Y[k];
						double dist = Math.sqrt(dx * dx + dy * dy);
						
						if(dist < enemy1.radius){
							
							enemy1.state[i] = EXPLODING;
							enemy1.explosion_start[i] = currentTime;
							enemy1.explosion_end[i] = currentTime + 500;
						}
					}
				}
				
				for(int i = 0; i < enemy2.state.length; i++){
					
					if(enemy2.state[i] == ACTIVE){
						
						double dx = enemy2.cord_X[i] - player_projectile.cord_X[k];
						double dy = enemy2.cord_Y[i] - player_projectile.cord_Y[k];
						double dist = Math.sqrt(dx * dx + dy * dy);
						
						if(dist < enemy2.radius){
							
							enemy2.state[i] = EXPLODING;
							enemy2.explosion_start[i] = currentTime;
							enemy2.explosion_end[i] = currentTime + 500;
						}
					}
				}
			}
				
			/***************************/
			/* Atualizações de estados */
			/***************************/
			
			/* projeteis (player) */
			
			for(int i = 0; i < player_projectile.states.length; i++){
				
				if(player_projectile.states[i] == ACTIVE){
					
					/* verificando se projétil saiu da tela */
					if(player_projectile.cord_Y[i] < 0) {
						
						player_projectile.states[i] = INACTIVE;
					}
					else {
					
						player_projectile.cord_X[i] += player_projectile.speed_X[i] * delta;
						player_projectile.cord_Y[i] += player_projectile.speed_Y[i] * delta;
					}
				}
			}
			
			/* projeteis (inimigos) */
			
			for(int i = 0; i < enemy_projectile.states.length; i++){
				
				if(enemy_projectile.states[i] == ACTIVE){
					
					/* verificando se projétil saiu da tela */
					if(enemy_projectile.cord_Y[i] > GameLib.HEIGHT) {
						
						enemy_projectile.states[i] = INACTIVE;
					}
					else {
					
						enemy_projectile.cord_X[i] += enemy_projectile.speed_X[i] * delta;
						enemy_projectile.cord_Y[i] += enemy_projectile.speed_Y[i] * delta;
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
																							
							int free = findFreeIndex(enemy_projectile.states);
							
							if(free < enemy_projectile.states.length){
								
								enemy_projectile.cord_X[free] = enemy1.cord_X[i];
								enemy_projectile.cord_Y[free] = enemy1.cord_Y[i];
								enemy_projectile.speed_X[free] = Math.cos(enemy1.angle[i]) * 0.45;
								enemy_projectile.speed_Y[free] = Math.sin(enemy1.angle[i]) * 0.45 * (-1.0);
								enemy_projectile.states[free] = ACTIVE;
								
								enemy1.next_shot[i] = (long) (currentTime + 200 + Math.random() * 500);
							}
						}
					}
				}
			}
			
			/* inimigos tipo 2 */
			
			for(int i = 0; i < enemy2.state.length; i++){
				
				if(enemy2.state[i] == EXPLODING){
					
					if(currentTime > enemy2.explosion_end[i]){
						
						enemy2.state[i] = INACTIVE;
					}
				}
				
				if(enemy2.state[i] == ACTIVE){
					
					/* verificando se inimigo saiu da tela */
					if(	enemy2.cord_X[i] < -10 || enemy2.cord_X[i] > GameLib.WIDTH + 10 ) {
						
						enemy2.state[i] = INACTIVE;
					}
					else {
						
						boolean shootNow = false;
						double previousY = enemy2.cord_Y[i];
												
						enemy2.cord_X[i] += enemy2.speed[i] * Math.cos(enemy2.angle[i]) * delta;
						enemy2.cord_Y[i] += enemy2.speed[i] * Math.sin(enemy2.angle[i]) * delta * (-1.0);
						enemy2.angle[i] += enemy2.rotation_speed[i] * delta;
						
						double threshold = GameLib.HEIGHT * 0.30;
						
						if(previousY < threshold && enemy2.cord_Y[i] >= threshold) {
							
							if(enemy2.cord_X[i] < GameLib.WIDTH / 2) enemy2.rotation_speed[i] = 0.003;
							else enemy2.rotation_speed[i] = -0.003;
						}
						
						if(enemy2.rotation_speed[i] > 0 && Math.abs(enemy2.angle[i] - 3 * Math.PI) < 0.05){
							
							enemy2.rotation_speed[i] = 0.0;
							enemy2.angle[i] = 3 * Math.PI;
							shootNow = true;
						}
						
						if(enemy2.rotation_speed[i] < 0 && Math.abs(enemy2.angle[i]) < 0.05){
							
							enemy2.rotation_speed[i] = 0.0;
							enemy2.angle[i] = 0.0;
							shootNow = true;
						}
																		
						if(shootNow){

							double [] angles = { Math.PI/2 + Math.PI/8, Math.PI/2, Math.PI/2 - Math.PI/8 };
							int [] freeArray = findFreeIndex(enemy_projectile.states, angles.length);

							for(int k = 0; k < freeArray.length; k++){
								
								int free = freeArray[k];
								
								if(free < enemy_projectile.states.length){
									
									double a = angles[k] + Math.random() * Math.PI/6 - Math.PI/12;
									double vx = Math.cos(a);
									double vy = Math.sin(a);
										
									enemy_projectile.cord_X[free] = enemy2.cord_X[i];
									enemy_projectile.cord_Y[free] = enemy2.cord_Y[i];
									enemy_projectile.speed_X[free] = vx * 0.30;
									enemy_projectile.speed_Y[free] = vy * 0.30;
									enemy_projectile.states[free] = ACTIVE;
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
			
			if(currentTime > enemy2.next_enemy){
				
				int free = findFreeIndex(enemy2.state);
								
				if(free < enemy2.state.length){
					
					enemy2.cord_X[free] = enemy2.spawn_X;
					enemy2.cord_Y[free] = -10.0;
					enemy2.speed[free] = 0.42;
					enemy2.angle[free] = (3 * Math.PI) / 2;
					enemy2.rotation_speed[free] = 0.0;
					enemy2.state[free] = ACTIVE;

					enemy2.count++;
					
					if(enemy2.count < 10){
						
						enemy2.next_enemy = currentTime + 120;
					}
					else {
						
						enemy2.count = 0;
						enemy2.spawn_X = Math.random() > 0.5 ? GameLib.WIDTH * 0.2 : GameLib.WIDTH * 0.8;
						enemy2.next_enemy = (long) (currentTime + 3000 + Math.random() * 3000);
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
						
						int free = findFreeIndex(player_projectile.states);
												
						if(free < player_projectile.states.length){
							
							player_projectile.cord_X[free] = player.getCordX();
							player_projectile.cord_Y[free] = player.getCordY() - 2 * player.getRadius();
							player_projectile.speed_X[free] = 0.0;
							player_projectile.speed_Y[free] = -1.0;
							player_projectile.states[free] = ACTIVE;
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
			background2.count += background2.speed * delta;
			
			for(int i = 0; i < background2.x.length; i++){
				
				GameLib.fillRect(background2.x[i], (background2.y[i] + background2.count) % GameLib.HEIGHT, 2, 2);
			}
			
			/* desenhando plano de fundo próximo */
			
			GameLib.setColor(Color.GRAY);
			background1.count += background1.speed * delta;
			
			for(int i = 0; i < background1.x.length; i++){
				
				GameLib.fillRect(background1.x[i], (background1.y[i] + background1.count) % GameLib.HEIGHT, 3, 3);
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
			
			for(int i = 0; i < player_projectile.states.length; i++){
				
				if(player_projectile.states[i] == ACTIVE){
					
					GameLib.setColor(Color.GREEN);
					GameLib.drawLine(player_projectile.cord_X[i], player_projectile.cord_Y[i] - 5, player_projectile.cord_X[i], player_projectile.cord_Y[i] + 5);
					GameLib.drawLine(player_projectile.cord_X[i] - 1, player_projectile.cord_Y[i] - 3, player_projectile.cord_X[i] - 1, player_projectile.cord_Y[i] + 3);
					GameLib.drawLine(player_projectile.cord_X[i] + 1, player_projectile.cord_Y[i] - 3, player_projectile.cord_X[i] + 1, player_projectile.cord_Y[i] + 3);
				}
			}
			
			/* desenhando projeteis (inimigos) */
		
			for(int i = 0; i < enemy_projectile.states.length; i++){
				
				if(enemy_projectile.states[i] == ACTIVE){
	
					GameLib.setColor(Color.RED);
					GameLib.drawCircle(enemy_projectile.cord_X[i], enemy_projectile.cord_Y[i], enemy_projectile.radius);
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
			
			for(int i = 0; i < enemy2.state.length; i++){
				
				if(enemy2.state[i] == EXPLODING){
					
					double alpha = (currentTime - enemy2.explosion_start[i]) / (enemy2.explosion_end[i] - enemy2.explosion_start[i]);
					GameLib.drawExplosion(enemy2.cord_X[i], enemy2.cord_Y[i], alpha);
				}
				
				if(enemy2.state[i] == ACTIVE){
			
					GameLib.setColor(Color.MAGENTA);
					GameLib.drawDiamond(enemy2.cord_X[i], enemy2.cord_Y[i], enemy2.radius);
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
