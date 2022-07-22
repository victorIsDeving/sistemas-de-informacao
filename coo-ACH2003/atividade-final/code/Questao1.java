import java.util.*;

public class Questao1 {
	/*
	 * <T extends Comparable<T>>
	 * O tipo do parâmetro DEVE suportar comparações com outras instâncias de mesmo tipo
	 */
	// List<T> significa método que retorna uma lista com objetos tipo T
	public static <T extends Comparable<T>> List<T> metodo(List<T> lista){ 

		List<T> resultado = new ArrayList<>();
		Set<T> set = new TreeSet<>(); // um Set representa um conjunto de valores que não possui elementos duplicados

		// iteração for-each das collections
		for(T x : lista) set.add(x); //adiciona em ordem crescente e sem duplicatas
		for(T x : set) resultado.add(x); //adiciona em ordem crescente na lista

		return resultado;
	}	
}
