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
		Enemy enemy1 = new Enemy(10, INACTIVE, 9.0, currentTime+2000);
		
		/* variáveis dos inimigos tipo 2 */
		EnemyArmada enemy2 = new EnemyArmada(10, INACTIVE, 12.0, currentTime+7000, GameLib.WIDTH*0.20, 0);

		/* variáveis dos inimigos tipo 3 */
		EnemyCrab enemy3 = new EnemyCrab(2, INACTIVE, 12.0, currentTime+3000);
	
		/* variáveis dos projéteis lançados pelos inimigos (tanto tipo 1, 2, 3) */
		ProjectileEnemy enemy_projectile = new ProjectileEnemy(10, INACTIVE, 2.0);
		
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
							player.exploding(currentTime);
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
							player.exploding(currentTime);
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
							player.exploding(currentTime);
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
							player.exploding(currentTime);
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
							enemy1.exploding(currentTime, i);
						}
					}
				}
				
				for(int i = 0; i < enemy2.state.length; i++){
					
					if(enemy2.state[i] == ACTIVE){
						
						double dx = enemy2.cord_X[i] - player_projectile.cord_X[k];
						double dy = enemy2.cord_Y[i] - player_projectile.cord_Y[k];
						double dist = Math.sqrt(dx * dx + dy * dy);
						
						if(dist < enemy2.radius){
							enemy2.exploding(currentTime, i);
						}
					}
				}
				
				for(int i = 0; i < enemy3.state.length; i++){
					
					if(enemy3.state[i] == ACTIVE){
						
						double dx = enemy3.cord_X[i] - player_projectile.cord_X[k];
						double dy = enemy3.cord_Y[i] - player_projectile.cord_Y[k];
						double dist = Math.sqrt(dx * dx + dy * dy);
						
						if(dist < enemy3.radius){
							enemy3.exploding(currentTime, i);
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
						enemy1.moving(delta, i);
						if (currentTime > enemy1.next_shot[i] && enemy1.cord_Y[i] < player.getCordY()){
																							
							int free = findFreeIndex(enemy_projectile.states);
							
							if (free < enemy_projectile.states.length){
								enemy1.shooting(currentTime, free, i, enemy_projectile);
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
									enemy2.shooting(currentTime, free, k, enemy_projectile);
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
									enemy3.shooting(currentTime, free, i, enemy_projectile);
								}
							}
						} else {
							enemy3.moving(delta, i);
						}	
	
					} else {
						enemy3.moving(delta, i);

						if (currentTime > enemy3.next_shot[i] && enemy3.cord_Y[i] < player.getCordY()){
																							
							int free = findFreeIndex(enemy_projectile.states);
							
							if(free < enemy_projectile.states.length){
								enemy3.shooting(currentTime, free, i, enemy_projectile);
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
					enemy1.lauching(free, GameLib.WIDTH, currentTime);
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
					enemy3.lauching(free, GameLib.WIDTH, currentTime);				
				}
			}	
		
			/* verificando se power ups devem ser "lançados" */
			
			if(currentTime > power_up1.next_power_up){
				
				int free = findFreeIndex(power_up1.state);

				power_up1.lauching(free, GameLib.WIDTH, currentTime);
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
				player.moving( GameLib.iskeyPressed(GameLib.KEY_UP), GameLib.iskeyPressed(GameLib.KEY_DOWN), GameLib.iskeyPressed(GameLib.KEY_LEFT), GameLib.iskeyPressed(GameLib.KEY_RIGHT), delta );
				
				if(GameLib.iskeyPressed(GameLib.KEY_CONTROL)) {
					if(currentTime > player.getNextShot()){
						int free = findFreeIndex(player_projectile.states);
						player.shooting(free, player_projectile, currentTime);
					}	
				}
			}
			
			if(GameLib.iskeyPressed(GameLib.KEY_ESCAPE)) running = false;
			
			/* Verificando se coordenadas do player ainda estão dentro */
			/* da tela de jogo após processar entrada do usuário.      */
			
			player.playerInside(GameLib.WIDTH, GameLib.HEIGHT);

			/*******************/
			/* Desenho da cena */
			/*******************/
			
			/* desenhando plano fundo distante */
			background2.drawBackground(GameLib.HEIGHT, delta, Color.DARK_GRAY, 2);
				
			/* desenhando plano de fundo próximo */
			background1.drawBackground(GameLib.HEIGHT, delta, Color.GRAY, 3);
						
			/* desenhando player */
			player.drawPlayer(currentTime);
				
			/* desenhando projeteis (player) */
			player_projectile.drawProjectile();
			
			/* desenhando projeteis (inimigos) */
			enemy_projectile.drawProjectile();
			
			/* desenhando inimigos (tipo 1) */
			enemy1.drawEnemy(currentTime);
			
			/* desenhando inimigos (tipo 2) */
			enemy2.drawEnemy(currentTime);
			
			/* desenhando inimigos (tipo 3) */
			enemy3.drawEnemy(currentTime);
			
			/* desenhando power ups */
			power_up1.drawPowerUp(currentTime);
			
			/* chamada a display() da classe GameLib atualiza o desenho exibido pela interface do jogo. */
			
			GameLib.display();
			
			/* faz uma pausa de modo que cada execução do laço do main loop demore aproximadamente 3 ms. */
			
			busyWait(currentTime + 3);
		}
		
		System.exit(0);
	}
}
