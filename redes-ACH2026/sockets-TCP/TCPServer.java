import java.io.*;
import java.net.*;

public class TCPServer {
    public static void main(String argv[]) throws Exception
    {
        String clientSentence;
        String capitalizedSentence;

        //cria socket na porta 6789
        ServerSocket welcomeSocket = new ServerSocket(6789);

        while(true)
        {
            //espera pelo contato do cliente no socket criado anteriormente
            Socket connectionSocket = welcomeSocket.accept();

            //cria uma cadeia de entrada no socket
            BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));

            //cria cadeia de saída conectada ao socket
            DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());

            //ler a linha do socket
            clientSentence = inFromClient.readLine();

            capitalizedSentence = clientSentence.toUpperCase() + "\n";

            //escrever a linha no socket
            outToClient.writeBytes(capitalizedSentence);
        } //fim do loop while que espera por uma nova conexão do cliente
    }
}
