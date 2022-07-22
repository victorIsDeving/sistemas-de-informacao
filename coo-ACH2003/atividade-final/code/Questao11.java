import java.io.*;

public class Questao11 {

	public static void main(String [] args) throws IOException {

		int x = 16777215;

		DataOutputStream out = new DataOutputStream(new FileOutputStream("arquivo1"));
		out.writeInt(x);
		out.close();

		Writer writer = new FileWriter("arquivo2");
		writer.write(String.valueOf(x) + "\n");
		writer.close();

	}
}
