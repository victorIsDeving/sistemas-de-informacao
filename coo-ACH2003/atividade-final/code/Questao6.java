import java.util.*;

public class Questao6 {

	public static double mediana(List<Double> lista){

		int n = lista.size();
		double mediana = lista.get(n / 2);

		if(n % 2 == 0) mediana = (mediana + lista.get(n / 2 - 1)) / 2.0; 

		return mediana;
	}
}
