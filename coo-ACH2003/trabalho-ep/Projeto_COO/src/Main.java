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


interface Projectiles {
	public static final int INACTIVE = 0;
	public static final int ACTIVE = 1;
	public static final int EXPLODING = 2;

	public void statesUpdate(long deltaTime, int screenEnd);
}

class Player {
	int state;						// estado
	double cord_X;					// coordenada x
	double cord_Y;				    // coordenada y
	double speed_X;					// velocidade no eixo x
	double speed_Y;					// velocidade no eixo y
	double radius;					// raio (tamanho aproximado do player)	
	double explosion_start = 0;		// instante do início da explosão
	double explosion_end = 0;		// instante do final da explosão
	long next_shot;					// instante a partir do qual pode haver um próximo tiro
	int power_up_state;				// estado do power up

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

	//getter speed X
	public double getVX() {
		return this.speed_X;
	}

	//getter speed Y
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

	//setter/getter power up
	public void setPowerUpState(int powerUp) {
		this.power_up_state = powerUp;
	}

	public int getPowerUpState() {
		return this.power_up_state;
	}

}

class EnemyBasic {
	int [] state;					// estados
	double [] cord_X;					// coordenadas x
	double [] cord_Y;					// coordenadas y
	double [] speed;					// velocidades
	double [] angle;				// ângulos (indicam direção do movimento)
	double [] rotation_speed;					// velocidades de rotação
	double [] explosion_start;			// instantes dos inícios das explosões
	double [] explosion_end;			// instantes dos finais da explosões
	long [] next_shot;				// instantes do próximo tiro
	double radius;						// raio (tamanho do inimigo)
	long next_enemy;					// instante em que um novo inimigo deve aparecer

	EnemyBasic (int arraysSize, int state, double radius, long nextEnemy) {
		this.state = new int[arraysSize];
		this.cord_X = new double[arraysSize];
		this.cord_Y = new double[arraysSize];
		this.speed = new double[arraysSize];
		this.angle = new double[arraysSize];
		this.rotation_speed = new double[arraysSize];
		this.explosion_start = new double[arraysSize];
		this.explosion_end = new double[arraysSize];
		this.next_shot = new long[arraysSize];
		this.radius = radius;
		this.next_enemy = nextEnemy;
		for(int i = 0; i < arraysSize; i++) this.state[i] = state;
	}

}

class EnemyArmada extends EnemyBasic {
	double spawn_X;				// coordenada x do próximo inimigo tipo 2 a aparecer
	int count;					// contagem de inimigos tipo 2 (usada na "formação de voo")
	
	EnemyArmada (int arraysSize, int state, double radius, long nextEnemy, double spawnX, int enemyCount) {
		super(arraysSize, state, radius, nextEnemy);
		spawn_X = spawnX;
		count = enemyCount;
	}
}

class EnemyCrab extends EnemyBasic {
	
	EnemyCrab (int arraysSize, int state, double radius, long nextEnemy) {
		super(arraysSize, state, radius, nextEnemy);
	}
}

class ProjectileBasic implements Projectiles {

	int [] states;					// estados
	double [] cord_X;				// coordenadas x
	double [] cord_Y;				// coordenadas y
	double [] speed_X;				// velocidades no eixo x
	double [] speed_Y;				// velocidades no eixo y

	ProjectileBasic (int arraysSize, int states) {
		this.states = new int[arraysSize];
		this.cord_X = new double[arraysSize];
		this.cord_Y = new double[arraysSize];
		this.speed_X = new double[arraysSize];
		this.speed_Y = new double[arraysSize];
		
		for(int i = 0; i < arraysSize; i++) this.states[i] = states;
	}

	public void statesUpdate(long deltaTime, int screenEnd) {
		for(int i = 0; i < this.states.length; i++){	
			if(this.states[i] == ACTIVE){
				/* verificando se projétil saiu da tela */
				if(this.cord_Y[i] < screenEnd) {
					this.states[i] = INACTIVE;
				} else {
					this.cord_X[i] += this.speed_X[i] * deltaTime;
					this.cord_Y[i] += this.speed_Y[i] * deltaTime;
				}
			}
		}
	}
}

class ProjectileRadius extends ProjectileBasic {

	double radius;					// raio (tamanho dos projéteis inimigos)

	ProjectileRadius (int arraysSize, int states, double radius) {
		super(arraysSize, states);
		this.radius = radius;
	}

	public void statesUpdate(long deltaTime, int screenEnd) {
		for(int i = 0; i < this.states.length; i++){
			if(this.states[i] == ACTIVE){
				/* verificando se projétil saiu da tela */
				if(this.cord_Y[i] > screenEnd) {	
					this.states[i] = INACTIVE;
				}
				else {
					this.cord_X[i] += this.speed_X[i] * deltaTime;
					this.cord_Y[i] += this.speed_Y[i] * deltaTime;
				}
			}
		}
	}
}

class PowerUp {
	int [] state;					// estados
	double [] cord_X;					// coordenadas x
	double [] cord_Y;					// coordenadas y
	double [] speed;					// velocidades
	double [] angle;				// ângulos (indicam direção do movimento)
	double [] rotation_speed;					// velocidades de rotação
	double [] explosion_start;			// instantes dos inícios das explosões
	double [] explosion_end;			// instantes dos finais da explosões
	double radius;						// raio (tamanho)
	long next_power_up;					// instante em que um novo inimigo deve aparecer
	long power_up_start = 0;		// instante do início do power up
	long power_up_end = 0;		// instante do final do power up

	PowerUp (int arraysSize, int state, double radius, long nextPowerUp) {
		this.state = new int[arraysSize];
		this.cord_X = new double[arraysSize];
		this.cord_Y = new double[arraysSize];
		this.speed = new double[arraysSize];
		this.angle = new double[arraysSize];
		this.rotation_speed = new double[arraysSize];
		this.explosion_start = new double[arraysSize];
		this.explosion_end = new double[arraysSize];
		this.radius = radius;
		this.next_power_up = nextPowerUp;

		for(int i = 0; i < arraysSize; i++) this.state[i] = state;
	}
	
	//setter/getter power up start
	public void setPowerUpStart(long powerUpStart) {
		this.power_up_start = powerUpStart;
	}

	public long getPowerUpStart() {
		return this.power_up_start;
	}

	//setter/getter power up end
	public void setPowerUpEnd(long powerUpEnd) {
		this.power_up_end = powerUpEnd;
	}

	public long getPowerUpEnd() {
		return this.power_up_end;
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
		ProjectileBasic player_projectile = new ProjectileBasic(10, INACTIVE);

		/* variáveis dos inimigos tipo 1 */
		EnemyBasic enemy1 = new EnemyBasic(10, INACTIVE, 9.0, currentTime+2000);
		
		/* variáveis dos inimigos tipo 2 */
		EnemyArmada enemy2 = new EnemyArmada(10, INACTIVE, 12.0, currentTime+7000, GameLib.WIDTH*0.20, 0);

		/* variáveis dos inimigos tipo 3 */
		EnemyCrab enemy3 = new EnemyCrab(2, INACTIVE, 12.0, currentTime+3000);
	
		/* variáveis dos projéteis lançados pelos inimigos (tanto tipo 1, 2, 3) */
		ProjectileRadius enemy_projectile = new ProjectileRadius(10, INACTIVE, 2.0);
		
		/* estrelas que formam o fundo de primeiro plano */
		Background background1 = new Background(20, 0.070, 0.0);
		
		/* estrelas que formam o fundo de segundo plano */
		Background background2 = new Background(50, 0.045, 0.0);
		
		/* variáveis dos inimigos tipo 1 */
		PowerUp power_up1 = new PowerUp(1, INACTIVE, 9.0, currentTime+20000);

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
						if (player.getPowerUpState() == ACTIVE) {
							enemy_projectile.states[i] = INACTIVE;
						} else {
							player.setState(EXPLODING);
							player.setExplosionStart(currentTime);
							player.setExplosionEnd(currentTime + 2000);
						}
					}
				}
			
				/* colisões player - inimigos */
							
				for(int i = 0; i < enemy1.state.length; i++){
					
					double dx = enemy1.cord_X[i] - player.getCordX();
					double dy = enemy1.cord_Y[i] - player.getCordY();
					double dist = Math.sqrt(dx * dx + dy * dy);
					
					if(dist < (player.getRadius() + enemy1.radius) * 0.8){
						if (player.getPowerUpState() == ACTIVE) {
							enemy1.state[i] = EXPLODING;
							enemy1.explosion_start[i] = currentTime;
							enemy1.explosion_end[i] = currentTime + 500;
						} else {
							player.setState(EXPLODING);
							player.setExplosionStart(currentTime);
							player.setExplosionEnd(currentTime + 2000);
						}
					}
				}
				
				for(int i = 0; i < enemy2.state.length; i++){
					
					double dx = enemy2.cord_X[i] - player.getCordX();
					double dy = enemy2.cord_Y[i] - player.getCordY();
					double dist = Math.sqrt(dx * dx + dy * dy);
					
					if(dist < (player.getRadius() + enemy2.radius) * 0.8){
						if (player.getPowerUpState() == ACTIVE) {
							enemy2.state[i] = EXPLODING;
							enemy2.explosion_start[i] = currentTime;
							enemy2.explosion_end[i] = currentTime + 500;
						} else {
							player.setState(EXPLODING);
							player.setExplosionStart(currentTime);
							player.setExplosionEnd(currentTime + 2000);
						}
					}
				}
				
				for(int i = 0; i < enemy3.state.length; i++){
					
					double dx = enemy3.cord_X[i] - player.getCordX();
					double dy = enemy3.cord_Y[i] - player.getCordY();
					double dist = Math.sqrt(dx * dx + dy * dy);
					
					if(dist < (player.getRadius() + enemy3.radius) * 0.8){
						if (player.getPowerUpState() == ACTIVE) {
							enemy3.state[i] = EXPLODING;
							enemy3.explosion_start[i] = currentTime;
							enemy3.explosion_end[i] = currentTime + 500;
						} else {
							player.setState(EXPLODING);
							player.setExplosionStart(currentTime);
							player.setExplosionEnd(currentTime + 2000);
						}
					}
				}
	
				/* colisões player - power up */
				
				for(int i = 0; i < power_up1.state.length; i++){
		
					double dx = power_up1.cord_X[i] - player.getCordX();
					double dy = power_up1.cord_Y[i] - player.getCordY();
					double dist = Math.sqrt(dx * dx + dy * dy);
					
					if(dist < (player.getRadius() + power_up1.radius) * 0.8){
						
						power_up1.state[i] = (EXPLODING);
						power_up1.explosion_start[i] = currentTime;
						power_up1.explosion_end[i] = currentTime + 1000;
						
						player.setPowerUpState(ACTIVE);
						power_up1.setPowerUpStart(currentTime);
						power_up1.setPowerUpEnd(currentTime + 5000);
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
				
				for(int i = 0; i < enemy3.state.length; i++){
					
					if(enemy3.state[i] == ACTIVE){
						
						double dx = enemy3.cord_X[i] - player_projectile.cord_X[k];
						double dy = enemy3.cord_Y[i] - player_projectile.cord_Y[k];
						double dist = Math.sqrt(dx * dx + dy * dy);
						
						if(dist < enemy3.radius){
							
							enemy3.state[i] = EXPLODING;
							enemy3.explosion_start[i] = currentTime;
							enemy3.explosion_end[i] = currentTime + 500;
						}
					}
				}
			}
				
			/***************************/
			/* Atualizações de estados */
			/***************************/
			
			/* projeteis (player) */
			player_projectile.statesUpdate(delta, 0);
			
			/* projeteis (inimigos) */
			enemy_projectile.statesUpdate(delta, GameLib.HEIGHT);
			
			/* inimigos tipo 1 */
			
			for (int i = 0; i < enemy1.state.length; i++){
				
				if (enemy1.state[i] == EXPLODING){
					
					if (currentTime > enemy1.explosion_end[i]){
						
						enemy1.state[i] = INACTIVE;
					}
				}
				
				if (enemy1.state[i] == ACTIVE){
					
					/* verificando se inimigo saiu da tela */
					if (enemy1.cord_Y[i] > GameLib.HEIGHT + 10) {
						
						enemy1.state[i] = INACTIVE;
					}
					else {
					
						enemy1.cord_X[i] += enemy1.speed[i] * Math.cos(enemy1.angle[i]) * delta;
						enemy1.cord_Y[i] += enemy1.speed[i] * Math.sin(enemy1.angle[i]) * delta * (-1.0);
						enemy1.angle[i] += enemy1.rotation_speed[i] * delta;
						
						if (currentTime > enemy1.next_shot[i] && enemy1.cord_Y[i] < player.getCordY()){
																							
							int free = findFreeIndex(enemy_projectile.states);
							
							if (free < enemy_projectile.states.length){
								
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
			
			for (int i = 0; i < enemy2.state.length; i++){
				
				if (enemy2.state[i] == EXPLODING){
					
					if(currentTime > enemy2.explosion_end[i]){
						
						enemy2.state[i] = INACTIVE;
					}
				}
				
				if (enemy2.state[i] == ACTIVE){
					
					/* verificando se inimigo saiu da tela */
					if (enemy2.cord_X[i] < -10 || enemy2.cord_X[i] > GameLib.WIDTH + 10 ) {
						
						enemy2.state[i] = INACTIVE;
					}
					else {
						
						boolean shootNow = false;
						double previousY = enemy2.cord_Y[i];
												
						enemy2.cord_X[i] += enemy2.speed[i] * Math.cos(enemy2.angle[i]) * delta;
						enemy2.cord_Y[i] += enemy2.speed[i] * Math.sin(enemy2.angle[i]) * delta * (-1.0);
						enemy2.angle[i] += enemy2.rotation_speed[i] * delta;
						
						double threshold = GameLib.HEIGHT * 0.30;
						
						if (previousY < threshold && enemy2.cord_Y[i] >= threshold) {
							
							if(enemy2.cord_X[i] < GameLib.WIDTH / 2) enemy2.rotation_speed[i] = 0.003;
							else enemy2.rotation_speed[i] = -0.003;
						}
						
						if (enemy2.rotation_speed[i] > 0 && Math.abs(enemy2.angle[i] - 3 * Math.PI) < 0.05){
							
							enemy2.rotation_speed[i] = 0.0;
							enemy2.angle[i] = 3 * Math.PI;
							shootNow = true;
						}
						
						if (enemy2.rotation_speed[i] < 0 && Math.abs(enemy2.angle[i]) < 0.05){
							
							enemy2.rotation_speed[i] = 0.0;
							enemy2.angle[i] = 0.0;
							shootNow = true;
						}
																		
						if (shootNow){

							double [] angles = { Math.PI/2 + Math.PI/8, Math.PI/2, Math.PI/2 - Math.PI/8 };
							int [] freeArray = findFreeIndex(enemy_projectile.states, angles.length);

							for(int k = 0; k < freeArray.length; k++){
								
								int free = freeArray[k];
								
								if (free < enemy_projectile.states.length){
									
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

			/* inimigos tipo 3 */
			
			for(int i = 0; i < enemy3.state.length; i++){
				
				if(enemy3.state[i] == EXPLODING){
					
					if(currentTime > enemy3.explosion_end[i]){
						
						enemy3.state[i] = INACTIVE;
					}
				}
				
				if (enemy3.state[i] == ACTIVE){
					
					/* verificando se inimigo saiu da tela */
					if (enemy3.cord_Y[i] > GameLib.HEIGHT + 10) {
						
						enemy3.state[i] = INACTIVE;
					} else if ( enemy3.cord_Y[i] >= GameLib.HEIGHT/3 && enemy3.cord_Y[i] <= GameLib.HEIGHT/2 ) {

						if (enemy3.cord_X[i] <= GameLib.WIDTH - enemy3.radius*2) {
							enemy3.cord_X[i] += 0.75;
							if (currentTime > enemy3.next_shot[i] && enemy3.cord_Y[i] < player.getCordY()){												
								int free = findFreeIndex(enemy_projectile.states);
								
								if(free < enemy_projectile.states.length){
									
									enemy_projectile.cord_X[free] = enemy3.cord_X[i];
									enemy_projectile.cord_Y[free] = enemy3.cord_Y[i];
									enemy_projectile.speed_X[free] = Math.cos(enemy3.angle[i]) * 0.45;
									enemy_projectile.speed_Y[free] = Math.sin(enemy3.angle[i]) * 0.45 * (-1.0);
									enemy_projectile.states[free] = ACTIVE;
									
									enemy3.next_shot[i] = (long) (currentTime + 200 + Math.random() * 500);
								}
							}
						} else {
							enemy3.cord_X[i] += enemy3.speed[i] * Math.cos(enemy3.angle[i]) * delta;
							enemy3.cord_Y[i] += enemy3.speed[i] * Math.sin(enemy3.angle[i]) * delta * (-1.0);
							enemy3.angle[i] += enemy3.rotation_speed[i] * delta;
						}	
	
					} else {
					
						enemy3.cord_X[i] += enemy3.speed[i] * Math.cos(enemy3.angle[i]) * delta;
						enemy3.cord_Y[i] += enemy3.speed[i] * Math.sin(enemy3.angle[i]) * delta * (-1.0);
						enemy3.angle[i] += enemy3.rotation_speed[i] * delta;

						if (currentTime > enemy3.next_shot[i] && enemy3.cord_Y[i] < player.getCordY()){
																							
							int free = findFreeIndex(enemy_projectile.states);
							
							if(free < enemy_projectile.states.length){
								
								enemy_projectile.cord_X[free] = enemy3.cord_X[i];
								enemy_projectile.cord_Y[free] = enemy3.cord_Y[i];
								enemy_projectile.speed_X[free] = Math.cos(enemy3.angle[i]) * 0.45;
								enemy_projectile.speed_Y[free] = Math.sin(enemy3.angle[i]) * 0.45 * (-1.0);
								enemy_projectile.states[free] = ACTIVE;
								
								enemy3.next_shot[i] = (long) (currentTime + 200 + Math.random() * 500);
							}
						}
					}
				}
			}
			
			/* power ups */
			
			for (int i = 0; i < power_up1.state.length; i++){
				
				if (power_up1.state[i] == EXPLODING){
					if (currentTime > power_up1.explosion_end[i]){
						power_up1.state[i] = INACTIVE;
					}
				}
				if (power_up1.state[i] == ACTIVE){
					/* verificando se power up saiu da tela */
					if (power_up1.cord_Y[i] > GameLib.HEIGHT + 10) {
						power_up1.state[i] = INACTIVE;
					} else {
						power_up1.cord_X[i] += power_up1.speed[i] * Math.cos(power_up1.angle[i]) * delta;
						power_up1.cord_Y[i] += power_up1.speed[i] * Math.sin(power_up1.angle[i]) * delta * (-1.0);
						power_up1.angle[i] += power_up1.rotation_speed[i] * delta;
					}
				}
				if (currentTime > power_up1.power_up_end){
					player.power_up_state = INACTIVE;
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
			
			/* verificando se novos inimigos (tipo 3) devem ser "lançados" */
			
			if(currentTime > enemy3.next_enemy){
				
				int free = findFreeIndex(enemy3.state);
								
				if(free < enemy3.state.length){						
					enemy3.cord_X[free] = enemy3.radius*2;
					enemy3.cord_Y[free] = -10.0;
					enemy3.speed[free] = 0.05 + Math.random() * 0.15;
					enemy3.angle[free] = (3 * Math.PI) / 2;
					enemy3.rotation_speed[free] = 0.0;
					enemy3.state[free] = ACTIVE;
					enemy3.next_shot[free] = currentTime + 500;
					enemy3.next_enemy = currentTime + 500;
				}
			}	
		
			/* verificando se power ups devem ser "lançados" */
			
			if(currentTime > power_up1.next_power_up){
				
				int free = findFreeIndex(power_up1.state);
								
				if(free < power_up1.state.length){
					
					power_up1.cord_X[free] = Math.random() * (GameLib.WIDTH - 20.0) + 10.0;
					power_up1.cord_Y[free] = -10.0;
					power_up1.speed[free] = 0.20 + Math.random() * 0.15;
					power_up1.angle[free] = (3 * Math.PI) / 2;
					power_up1.rotation_speed[free] = 0.0;
					power_up1.state[free] = ACTIVE;
					power_up1.next_power_up = currentTime + 10000;
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
			
			/* desenhando inimigos (tipo 3) */
			
			for(int i = 0; i < enemy3.state.length; i++){
				
				if(enemy3.state[i] == EXPLODING){
					
					double alpha = (currentTime - enemy3.explosion_start[i]) / (enemy3.explosion_end[i] - enemy3.explosion_start[i]);
					GameLib.drawExplosion(enemy3.cord_X[i], enemy3.cord_Y[i], alpha);
				}
				
				if(enemy3.state[i] == ACTIVE){
					
					GameLib.setColor(Color.RED);
					GameLib.drawDiamond(enemy3.cord_X[i], enemy3.cord_Y[i], enemy3.radius);
					GameLib.setColor(Color.ORANGE);
					GameLib.drawCircle(enemy3.cord_X[i], enemy3.cord_Y[i], enemy3.radius/2);
				}
			}
			
			/* desenhando power ups */
			
			for(int i = 0; i < power_up1.state.length; i++){
				
				if(power_up1.state[i] == EXPLODING){
					
					double alpha = (currentTime - power_up1.explosion_start[i]) / (power_up1.explosion_end[i] - power_up1.explosion_start[i]);
					GameLib.drawExplosion(power_up1.cord_X[i], power_up1.cord_Y[i], alpha);
				}
				
				if(power_up1.state[i] == ACTIVE){
					
					GameLib.setColor(Color.PINK);
					GameLib.drawDiamond(power_up1.cord_X[i], power_up1.cord_Y[i], power_up1.radius);
					GameLib.setColor(Color.GREEN);
					GameLib.drawDiamond(power_up1.cord_X[i], power_up1.cord_Y[i], power_up1.radius/2);
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