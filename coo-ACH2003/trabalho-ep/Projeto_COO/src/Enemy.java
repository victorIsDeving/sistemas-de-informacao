import java.awt.Color;

public class Enemy extends Basics {
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

	Enemy (int arraysSize, int state, double radius, long nextEnemy) {
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

	public void exploding(long currentTime, int i) {
		this.state[i] = EXPLODING;
		this.explosion_start[i] = currentTime;
		this.explosion_end[i] = currentTime + 500;
	}

	public void moving (long delta, int i) {
		this.cord_X[i] += this.speed[i] * Math.cos(this.angle[i]) * delta;
		this.cord_Y[i] += this.speed[i] * Math.sin(this.angle[i]) * delta * (-1.0);
		this.angle[i] += this.rotation_speed[i] * delta;
	} 

	public void shooting(long currentTime, int i, ProjectileEnemy enemyProjectile, Player player) {
		if (currentTime > this.next_shot[i] && this.cord_Y[i] < player.getCordY()){
			int free = this.findFreeIndex(enemyProjectile.states);

			if (free < enemyProjectile.states.length){
				enemyProjectile.cord_X[free] = this.cord_X[i];
				enemyProjectile.cord_Y[free] = this.cord_Y[i];
				enemyProjectile.speed_X[free] = Math.cos(this.angle[i]) * 0.45;
				enemyProjectile.speed_Y[free] = Math.sin(this.angle[i]) * 0.45 * (-1.0);
				enemyProjectile.states[free] = ACTIVE;
				
				this.next_shot[i] = (long) (currentTime + 200 + Math.random() * 500);
			}
		}
	}

	public void lauching(int screenWidth, long currentTime) {
		if(currentTime > this.next_enemy){
				
			int free = findFreeIndex(this.state);
							
			if(free < this.state.length){
				this.cord_X[free] = Math.random() * (screenWidth - 20.0) + 10.0;
				this.cord_Y[free] = -10.0;
				this.speed[free] = 0.20 + Math.random() * 0.15;
				this.angle[free] = (3 * Math.PI) / 2;
				this.rotation_speed[free] = 0.0;
				this.state[free] = ACTIVE;
				this.next_shot[free] = currentTime + 500;
				this.next_enemy = currentTime + 500;
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
		
				GameLib.setColor(Color.CYAN);
				GameLib.drawCircle(this.cord_X[i], this.cord_Y[i], this.radius);
			}
		}
	}
}
