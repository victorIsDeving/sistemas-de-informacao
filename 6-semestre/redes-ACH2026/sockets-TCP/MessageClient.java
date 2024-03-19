import java.net.*;
import java.util.Scanner;
import java.io.*;
 
public class MessageClient {

    public void iniciar(String endereco, int porta) {
        ObjectOutputStream saida;
        ObjectInputStream entrada;
        Socket conexao;
        Scanner ler = new Scanner(System.in);
        String mensagem = "";
        try {
            conexao = new Socket(endereco, porta);
            System.out.println("Conectado ao servidor " + endereco + ", na porta: " + porta);
            System.out.println("Digite: FIM para encerrar a conexao");

            // ligando as conexoes de saida e de entrada
            saida = new ObjectOutputStream(conexao.getOutputStream());
            saida.flush();
            entrada = new ObjectInputStream(conexao.getInputStream());

            //lendo a mensagem enviada pelo servidor
            mensagem = (String) entrada.readObject();
            System.out.println("Servidor>> "+mensagem);

            do {
                System.out.print("..: ");
                mensagem = ler.nextLine();
                saida.writeObject(mensagem);
                saida.flush();
                //lendo a mensagem enviada pelo servidor
                mensagem = (String) entrada.readObject();
                System.out.println("Servidor>> "+mensagem);
            } while (!mensagem.equals("FIM"));

            saida.close();
            entrada.close();
            conexao.close();

        } catch (Exception e) {
            System.err.println("erro: " + e.toString());
        }

    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Uso: java tcp.Cliente <endereco-IP> <porta>");
            System.exit(1);
        }

        MessageClient c = new MessageClient();
        c.iniciar(args[0], Integer.parseInt(args[1]));
    }
}