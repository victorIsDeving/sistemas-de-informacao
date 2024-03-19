import java.awt.Color;

public class Player extends Basics{
    int state;						// estado
	double cord_X;					// coordenada x
	double cord_Y;				    // coordenada y
	double speed_X;					// velocidade no eixo x
	double speed_Y;					// velocidade no eixo y
	double radius;					// raio (tamanho aproximado do player)	
	double explosion_start = 0;		// instante do início da explosão
	double explosion_end = 0;		// instante do final da explosão
	long next_shot;					// instante a partir do qual pode haver um próximo tiro
	int power_up_state;				// estado do power up

	Player (int initState, double cordX, double cordY, double speedX, double speedY, double radius, long nextShot){
		this.state = initState;
		this.cord_X = cordX;
		this.cord_Y = cordY;
		this.speed_X = speedX;
		this.speed_Y = speedY;
		this.radius = radius;
		this.next_shot = nextShot;
	}

	//setter/getter states
	public void setState(int state) {
		this.state = state;
	}

	public int getState() {
		return this.state;
	}

	//setter/getter coordenadas X
	public void setCordX(double cord_X) {
		this.cord_X = cord_X;
	}

	public double getCordX() {
		return this.cord_X;
	}

	//setter/getter coordenadas Y
	public void setCordY(double cord_Y) {
		this.cord_Y = cord_Y;
	}

	public double getCordY() {
		return this.cord_Y;
	}

	//getter radius
	public double getRadius() {
		return this.radius;
	}

	//setter/getter explosion start
	public void setExplosionStart(long start) {
		this.explosion_start = start;
	}

	public double getExplosionStart() {
		return this.explosion_start;
	}

	//setter/getter explosion end
	public void setExplosionEnd(long end) {
		this.explosion_end = end;
	}

	public double getExplosionEnd() {
		return this.explosion_end;
	}

	//getter speed X
	public double getVX() {
		return this.speed_X;
	}

	//getter speed Y
	public double getVY() {
		return this.speed_Y;
	}

	//setter/getter next shot
	public void setNextShot(long nextShot) {
		this.next_shot = nextShot;
	}

	public long getNextShot() {
		return this.next_shot;
	}

	//setter/getter power up
	public void setPowerUpState(int powerUp) {
		this.power_up_state = powerUp;
	}

	public int getPowerUpState() {
		return this.power_up_state;
	}

	public void exploding(long currentTime) {
		this.setState(EXPLODING);
		this.setExplosionStart(currentTime);
		this.setExplosionEnd(currentTime + 2000);
	}

	public void moving(boolean keyUp, boolean keyDown, boolean keyLeft, boolean keyRight, long delta) {
		if(keyUp) this.setCordY(this.getCordY() - delta * this.getVY());
		if(keyDown) this.setCordY(this.getCordY() + delta * this.getVY());
		if(keyLeft) this.setCordX(this.getCordX() - delta * this.getVX());
		if(keyRight) this.setCordX(this.getCordX() + delta * this.getVX());
	}

	public void shooting( ProjectileBasic playerProjectile, long currentTime) {
		if(currentTime > this.getNextShot()){
			int free = findFreeIndex(playerProjectile.states);
			if(free < playerProjectile.states.length){
								
				playerProjectile.cord_X[free] = this.getCordX();
				playerProjectile.cord_Y[free] = this.getCordY() - 2 * this.getRadius();
				playerProjectile.speed_X[free] = 0.0;
				playerProjectile.speed_Y[free] = -1.0;
				playerProjectile.states[free] = ACTIVE;
				this.setNextShot(currentTime+100);
			}
		}
		
	}

	public void playerInside(int screenWidth, int screenHeight) { 
		if(this.getCordX() < 0.0) this.setCordX(0.0);
		if(this.getCordX() >= screenWidth) this.setCordX(screenWidth - 1);
		if(this.getCordY() < 25.0) this.setCordY(25.0);
		if(this.getCordY() >= screenHeight) this.setCordY(screenHeight - 1);
	}

	public void drawPlayer(long currentTime) {
		if(this.getState() == EXPLODING){
			double alpha = (currentTime - this.getExplosionStart()) / (this.getExplosionEnd() - this.getExplosionStart());
			GameLib.drawExplosion(this.getCordX(), this.getCordY(), alpha);
		} else {
			if (this.power_up_state == 1) {
				GameLib.setColor(Color.YELLOW);
			} else {
				GameLib.setColor(Color.BLUE);
			}
			GameLib.drawPlayer(this.getCordX(), this.getCordY(), this.getRadius());
		}
	}
}
