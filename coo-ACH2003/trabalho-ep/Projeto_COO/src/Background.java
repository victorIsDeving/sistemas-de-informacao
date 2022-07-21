import java.awt.Color;
import java.util.ArrayList;

public class Background {
    ArrayList <Double> x;
	ArrayList <Double> y;
	double speed;
	double count;

	Background (int arraySize, double speed, double count) {
		this.x = new ArrayList<>(arraySize);
		this.y = new ArrayList<>(arraySize);
		this.speed = speed;
		this.count = count;

		for(int i = 0; i < arraySize; i++){
			x.add(i, Math.random() * GameLib.WIDTH);
			y.add(i, Math.random() * GameLib.WIDTH); 
		}
	}

	public void drawBackground(int screenHeight, long delta, Color setColor, int j) {
		GameLib.setColor(setColor);
		this.count += this.speed * delta;
		
		for(int i = 0; i < this.x.size(); i++){
			GameLib.fillRect(this.x.get(i), (this.y.get(i) + this.count) % screenHeight, j, j);
		}
	}
}
