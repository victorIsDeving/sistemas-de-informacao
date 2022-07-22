import java.util.*;

public class Questao3 {

	public static <T extends Comparable<T>> List<T> metodo(List<T> lista){

		List<T> resultado = new ArrayList<>();

		for(T x : lista) if(!resultado.contains(x)) resultado.add(x);

		return resultado;
	}	
}
