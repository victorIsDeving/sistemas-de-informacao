import java.awt.Color;

class ProjectileBasic extends Basics {

	int [] states;					// estados
	double [] cord_X;				// coordenadas x
	double [] cord_Y;				// coordenadas y
	double [] speed_X;				// velocidades no eixo x
	double [] speed_Y;				// velocidades no eixo y

	ProjectileBasic (int arraysSize, int initStates) {
		this.states = new int[arraysSize];
		this.cord_X = new double[arraysSize];
		this.cord_Y = new double[arraysSize];
		this.speed_X = new double[arraysSize];
		this.speed_Y = new double[arraysSize];
		
		for(int i = 0; i < arraysSize; i++) this.states[i] = initStates;
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

	public void drawProjectile() {
		for(int i = 0; i < this.states.length; i++){
			if(this.states[i] == ACTIVE){
				GameLib.setColor(Color.GREEN);
				GameLib.drawLine(this.cord_X[i], this.cord_Y[i] - 5, this.cord_X[i], this.cord_Y[i] + 5);
				GameLib.drawLine(this.cord_X[i] - 1, this.cord_Y[i] - 3, this.cord_X[i] - 1, this.cord_Y[i] + 3);
				GameLib.drawLine(this.cord_X[i] + 1, this.cord_Y[i] - 3, this.cord_X[i] + 1, this.cord_Y[i] + 3);
			}
		}
	}
}
