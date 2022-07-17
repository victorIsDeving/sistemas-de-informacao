import java.awt.Color;

public class EnemyArmada extends Enemy {
    double spawn_X;				// coordenada x do próximo inimigo tipo 2 a aparecer
	int count;					// contagem de inimigos tipo 2 (usada na "formação de voo")
	
	EnemyArmada (int arraysSize, int state, double radius, long nextEnemy, double spawnX, int enemyCount) {
		super(arraysSize, state, radius, nextEnemy);
		spawn_X = spawnX;
		count = enemyCount;
	}

	public void shooting(long currentTime, long delta, int i, ProjectileEnemy enemyProjectile, Player player) {			
		boolean shootNow = false;
		double previousY = this.cord_Y[i];
								
		this.cord_X[i] += this.speed[i] * Math.cos(this.angle[i]) * delta;
		this.cord_Y[i] += this.speed[i] * Math.sin(this.angle[i]) * delta * (-1.0);
		this.angle[i] += this.rotation_speed[i] * delta;
		
		double threshold = GameLib.HEIGHT * 0.30;
		
		if (previousY < threshold && this.cord_Y[i] >= threshold) {
			
			if(this.cord_X[i] < GameLib.WIDTH / 2) this.rotation_speed[i] = 0.003;
			else this.rotation_speed[i] = -0.003;
		}
		
		if (this.rotation_speed[i] > 0 && Math.abs(this.angle[i] - 3 * Math.PI) < 0.05){
			
			this.rotation_speed[i] = 0.0;
			this.angle[i] = 3 * Math.PI;
			shootNow = true;
		}
		
		if (this.rotation_speed[i] < 0 && Math.abs(this.angle[i]) < 0.05){
			
			this.rotation_speed[i] = 0.0;
			this.angle[i] = 0.0;
			shootNow = true;
		}
																		
		if (shootNow){

			double [] angles = { Math.PI/2 + Math.PI/8, Math.PI/2, Math.PI/2 - Math.PI/8 };
			int [] freeArray = findFreeIndex(enemyProjectile.states, angles.length);

			for(int k = 0; k < freeArray.length; k++){
				double a = this.angle[i] + Math.random() * Math.PI/6 - Math.PI/12;
				double vx = Math.cos(a);
				double vy = Math.sin(a);
		
				enemyProjectile.cord_X[k] = this.cord_X[i];
				enemyProjectile.cord_Y[k] = this.cord_Y[i];
				enemyProjectile.speed_X[k] = vx * 0.30;
				enemyProjectile.speed_Y[k] = vy * 0.30;
				enemyProjectile.states[k] = ACTIVE;
			}
		}
	}
		

	public void lauching(int screenSize, long currentTime) {
		if(currentTime > this.next_enemy){
				
			int free = findFreeIndex(this.state);
							
			if(free < this.state.length){
				
				this.cord_X[free] = this.spawn_X;
				this.cord_Y[free] = -10.0;
				this.speed[free] = 0.42;
				this.angle[free] = (3 * Math.PI) / 2;
				this.rotation_speed[free] = 0.0;
				this.state[free] = ACTIVE;

				this.count++;
				
				if(this.count < 10){
					
					this.next_enemy = currentTime + 120;
				}
				else {
					
					this.count = 0;
					this.spawn_X = Math.random() > 0.5 ? GameLib.WIDTH * 0.2 : GameLib.WIDTH * 0.8;
					this.next_enemy = (long) (currentTime + 3000 + Math.random() * 3000);
				}
			}
		}
	}

	public void drawEnemy(long currentTime) {
		for(int i = 0; i < this.state.length; i++){
			
			if(this.state[i] == EXPLODING){
				
				double alpha = (currentTime - this.explosion_start[i]) / (this.explosion_end[i] - this.explosion_start[i]);
				GameLib.drawExplosion(this.cord_X[i], this.cord_Y[i], alpha);
			}
			
			if(this.state[i] == ACTIVE){
		
				GameLib.setColor(Color.MAGENTA);
				GameLib.drawDiamond(this.cord_X[i], this.cord_Y[i], this.radius);
			}
		}
	}
}
