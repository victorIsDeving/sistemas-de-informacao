import java.io.*;
import java.net.*;

class UDPClient {
    public static void main (String args[]) throws Exception
    {
        //criar cadeia de entrada no cliente
        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));

        //criar o socket propriamente dito do cliente
        DatagramSocket clientSocket = new DatagramSocket();
    
        //traduzir hostname para endereço IP usando DNS
        InetAddress IPAddress = InetAddress.getByName("hostname");

        byte[] sendData = new byte[1024];
        byte[] receiveData = new byte[1024];

        String sentence = inFromUser.readLine();
        sendData = sentence.getBytes();

        //criar o pacote (datagrama) com os dados a enviar com tamanho, end IP e porta
        DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 9876);

        //envia o pacote (datagrama) ao servidor
        clientSocket.send(sendPacket);

        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

        //lê o datagrama do servidor
        String modifiedSentence = new String(receivePacket.getData());

        System.out.println("From Server: " + modifiedSentence);
        clientSocket.close();
    }
}