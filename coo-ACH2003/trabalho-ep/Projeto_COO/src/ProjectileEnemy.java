import java.awt.Color;

public class ProjectileEnemy extends ProjectileBasic {

	double radius;					// raio (tamanho dos projéteis inimigos)

	ProjectileEnemy (int arraysSize, int states, double radius) {
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

	public void drawProjectile() {
		for(int i = 0; i < this.states.length; i++){
			if(this.states[i] == ACTIVE){

				GameLib.setColor(Color.RED);
				GameLib.drawCircle(this.cord_X[i], this.cord_Y[i], this.radius);
			}
		}
	}
}
