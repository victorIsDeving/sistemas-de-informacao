import java.io.*;
import java.net.*;

public class TCPClient {
    public static void main(String argv[]) throws Exception
    {
        String sentence;
        String modifiedSentence;

        //criar cadeia de entrada
        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));

        //cria socket no cliente, a conexão com o servidor
        Socket clientSocket = new Socket("hostname", 6789);

        //cria uma cadeia de saída a partir do socket
        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());

        //cria uma cadeia de entrada para o socket
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        sentence = inFromUser.readLine();

        //envia linha ao servidor
        outToServer.writeBytes(sentence + "\n");

        //lê linha recebida do servidor
        modifiedSentence = inFromServer.readLine();

        System.out.println("FROM SERVER: " + modifiedSentence);

        clientSocket.close();
    }
}
