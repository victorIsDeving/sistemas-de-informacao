import java.awt.Color;

public class EnemyArmada extends Enemy {
    double spawn_X;				// coordenada x do próximo inimigo tipo 2 a aparecer
	int count;					// contagem de inimigos tipo 2 (usada na "formação de voo")
	
	EnemyArmada (int arraysSize, int state, double radius, long nextEnemy, double spawnX, int enemyCount) {
		super(arraysSize, state, radius, nextEnemy);
		spawn_X = spawnX;
		count = enemyCount;
	}

	public void shooting(long currentTime, int free, int i, ProjectileEnemy enemyProjectile) {			
		double a = this.angle[i] + Math.random() * Math.PI/6 - Math.PI/12;
		double vx = Math.cos(a);
		double vy = Math.sin(a);

		enemyProjectile.cord_X[free] = this.cord_X[i];
		enemyProjectile.cord_Y[free] = this.cord_Y[i];
		enemyProjectile.speed_X[free] = vx * 0.30;
		enemyProjectile.speed_Y[free] = vy * 0.30;
		enemyProjectile.states[free] = ACTIVE;
	}

	public void lauching(int free, int screenSize, long currentTime) {
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
			this.spawn_X = Math.random() > 0.5 ? screenSize * 0.2 : screenSize * 0.8;
			this.next_enemy = (long) (currentTime + 3000 + Math.random() * 3000);
		}}

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
