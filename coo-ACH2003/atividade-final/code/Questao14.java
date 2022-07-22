class Retangulo {

	private double w, h;
	
	public Retangulo(double w, double h){
		
		set(w, h);
	}

	public void set(double w, double h){

		this.w = w;
		this.h = h;
	}

	public double area(){

		return w * h;
	}

	public String toString(){

		return String.format("[ %10s: %5.2f, %5.2f ]", getClass().getName(), w, h);
	}
}

class Quadrado extends Retangulo {

	public Quadrado(double l){

		super(l, l);
	}

	public void set(double l){

		set(l, l);
	}
}

public class Questao14 {

	public static void imprime(Retangulo [] retangulos){

		for(Retangulo r : retangulos){

			System.out.println(r + ": " + String.format("%.2f", r.area()));
		}
	}

	public static void reshape(Retangulo [] retangulos, double aspect){

		// redimensiona os retangulos do array, 
		// mantendo a área original, de modo que a 
		// razão nova_largura/nova_altura = aspect		
			
		for(Retangulo r : retangulos){

			double h = Math.sqrt(r.area() / aspect);
			r.set(h * aspect, h);
		}
	}

	public static void main(String [] args){
	
		Retangulo [] retangulos = new Retangulo[4];

		retangulos[0] = new Retangulo(3, 4);
		retangulos[1] = new Retangulo(25, 3); 
		retangulos[2] = new Retangulo(6, 8);
		retangulos[3] = new Quadrado(5 * Math.sqrt(3));

		imprime(retangulos);
		System.out.println();
		
		reshape(retangulos, 3);		
		imprime(retangulos);
	}
}

