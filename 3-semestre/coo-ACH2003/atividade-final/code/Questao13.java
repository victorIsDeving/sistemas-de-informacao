import java.util.*;

class FilterList {

	// Esta classe implementa uma lista linear (bem simplificada) de
	// valores inteiros que usa como espeço de armazenamento interno 
	// um vetor (array). Além disso, a inserção de um valor na lista
	// só ocorre, efetivamente, se o valor passado ao método adiciona
	// satisfaz um determinado critério (que é especificado no momento da
	// instanciação da lista). Tais critérios são implementados no
	// próprio método adiciona.

	public static final int TODOS = 0;
	public static final int POSITIVOS = 1;
	public static final int PARES = 2;
	public static final int IMPARES = 3;
	public static final int MENORES_QUE = 4;
	public static final int MAIORES_OU_IGUAIS_A = 5;

	private int [] array;
	private int criterio, parametro, livre;

	public FilterList(int n, int crit, int param){

		array = new int[n];
		livre = 0;
		criterio = crit;
		parametro = param;
	}

	public FilterList(int n, int crit){

		this(n, crit, 0);
	}

	public void adiciona(int x){

		if(livre >= array.length) throw new IllegalStateException("Lista está cheia!");

		if(criterio == TODOS){
		
			array[livre++] = x;
		}
		else if(criterio == POSITIVOS){

			if(x >= 0) array[livre++] = x;
		}
		else if(criterio == PARES) {

			if(x % 2 == 0) array[livre++] = x;
		}
		else if(criterio == IMPARES){
 
			if(x % 2 != 0) array[livre++] = x;
		}
		else if(criterio == MENORES_QUE){

			 if(x < parametro) array[livre++] = x;
		}
		else if(criterio == MAIORES_OU_IGUAIS_A){
	
			if(x >= parametro) array[livre++] = x;
		}
		else throw new IllegalArgumentException("Criterio não especificado!");
	}

	public String toString(){

		return Arrays.toString(Arrays.copyOfRange(array, 0, livre));
	}
}

public class Questao13 {

	public static void main(String [] args){

		int n = 20;
		FilterList lista = new FilterList(n, FilterList.MAIORES_OU_IGUAIS_A, n / 2);

		for(int i = 0; i < n; i++) lista.adiciona((int)(Math.random() * n));

		System.out.println(lista);			
	}
}
