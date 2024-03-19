import java.io.*;
import java.util.*;

public class Questao9 {

	public static void contaCaracteres(String nomeArquivo) throws IOException {

		int ch;
		______________ map = new TreeMap<>();
		______________ in = new ______________(nomeArquivo);
		
		while ( (ch = ______________) != -1 ) {

			char key = (char) ch;
			if(!map.containsKey(key)) map.put(key, 0);
			______________;
		}

		in.close();

		for(char key : map.keySet()){
	
			System.out.println("caractere '" + key + "' ocorre " + map.get(key) + " vez(es).");
		}	
	}
}
