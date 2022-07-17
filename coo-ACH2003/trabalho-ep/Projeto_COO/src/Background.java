import java.awt.Color;

public class Background {
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

	public void drawBackground(int screenHeight, long delta, Color setColor, int j) {
		GameLib.setColor(setColor);
		this.count += this.speed * delta;
		
		for(int i = 0; i < this.x.length; i++){
			
			GameLib.fillRect(this.x[i], (this.y[i] + this.count) % screenHeight, j, j);
		}
	}
}
