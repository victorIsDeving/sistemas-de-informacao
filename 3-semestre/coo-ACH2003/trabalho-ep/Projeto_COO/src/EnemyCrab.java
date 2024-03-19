import java.awt.Color;

public class EnemyCrab extends Enemy {
    	
	EnemyCrab (int arraysSize, int state, double radius, long nextEnemy) {
		super(arraysSize, state, radius, nextEnemy);
	}
	
	public void movingHorizontal(int i, double speed) {
		this.cord_X[i] += speed;
	}

	public void drawEnemy(long currentTime) {
		for(int i = 0; i < this.state.length; i++){
				
			if(this.state[i] == EXPLODING){
				
				double alpha = (currentTime - this.explosion_start[i]) / (this.explosion_end[i] - this.explosion_start[i]);
				GameLib.drawExplosion(this.cord_X[i], this.cord_Y[i], alpha);
			}
			
			if(this.state[i] == ACTIVE){
				
				GameLib.setColor(Color.RED);
				GameLib.drawDiamond(this.cord_X[i], this.cord_Y[i], this.radius);
				GameLib.setColor(Color.ORANGE);
				GameLib.drawCircle(this.cord_X[i], this.cord_Y[i], this.radius/2);
			}
		}
	}
}
