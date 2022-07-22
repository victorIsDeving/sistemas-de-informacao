import java.util.*; 

class Chave { 

	private int id; 

	public Chave(int id){

		this.id = id; 
	} 

	public String toString(){

		return String.valueOf(id); 
	} 
} 

class Pessoa { 

	private Chave chave; 
	private String nome; 

	public Pessoa (Chave chave, String nome){ 

		this.chave = chave; 
		this.nome = nome; 
	} 

	public String toString(){

		return "[Pessoa: chave = " + chave + " nome = " + nome + "]"; 
	} 
}

public class Questao5 { 

	public static void main(String [] args){ 

		Map<Chave, Pessoa> map = new HashMap<>(); 

		int [] ids = {5000, 5010, 5020, 5030}; 
		String [] nomes = {"Joao", "Pedro", "Maria", "Ana"}; 

		for(int i = 0; i < ids.length; i++){ 

			Chave c = new Chave(ids[i]); 
			Pessoa p = new Pessoa(c, nomes[i]); 
			map.put(c, p); 
		} 

		Chave chave = new Chave(5020); 

		if(map.containsKey(chave)){ 
			
			System.out.println(map.get(chave)); 
		} 
		else{ 
			System.out.println("Chave inexistente!"); 
		} 
	} 
}

