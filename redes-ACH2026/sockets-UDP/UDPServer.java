import java.io.*;
import java.net.*;

class UDPServer {
    public static void main(String args[]) throws Exception
    {
        //cria o socket na porta 9876
        DatagramSocket serverSocket = new DatagramSocket(9876);

        byte[] receiveData = new byte[1024];
        byte[] sendData = new byte[1024];

        while(true)
        {
            //criar espaço para receber o pacote (datagrama)
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

            //recebe o pacote
            serverSocket.receive(receivePacket);

            String sentence = new String(receivePacket.getData());

            //obtém end IP e número da porta do emissor (o cliente)
            InetAddress IPAddress = receivePacket.getAddress();
            int port = receivePacket.getPort();
                String capitalizedSentence = sentence.toUpperCase();
            sendData = capitalizedSentence.getBytes();

            //cria um pacote para enviar ao cliente
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);

            //escreve datagrama no socket
            serverSocket.send(sendPacket);
        } //fim do loop while, faz o retorno para o cliente e espera um outro pacote
    }
}
