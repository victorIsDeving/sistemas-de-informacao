import java.awt.Color;

public class PowerUp extends Basics {
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

	public void drawPowerUp(long currentTime) {
		for(int i = 0; i < this.state.length; i++){
			
			if(this.state[i] == EXPLODING){
				
				double alpha = (currentTime - this.explosion_start[i]) / (this.explosion_end[i] - this.explosion_start[i]);
				GameLib.drawExplosion(this.cord_X[i], this.cord_Y[i], alpha);
			}
			
			if(this.state[i] == ACTIVE){
				
				GameLib.setColor(Color.PINK);
				GameLib.drawDiamond(this.cord_X[i], this.cord_Y[i], this.radius);
				GameLib.setColor(Color.GREEN);
				GameLib.drawDiamond(this.cord_X[i], this.cord_Y[i], this.radius/2);
			}
		}
	}

	public void lauching(int screenWidth, long currentTime) {				
		if(currentTime > this.next_power_up){
				
			int free = findFreeIndex(this.state);

			if(free < this.state.length){
				this.cord_X[free] = Math.random() * (screenWidth - 20.0) + 10.0;
				this.cord_Y[free] = -10.0;
				this.speed[free] = 0.20 + Math.random() * 0.15;
				this.angle[free] = (3 * Math.PI) / 2;
				this.rotation_speed[free] = 0.0;
				this.state[free] = ACTIVE;
				this.next_power_up = currentTime + 10000;
			}
		}
	}

}
