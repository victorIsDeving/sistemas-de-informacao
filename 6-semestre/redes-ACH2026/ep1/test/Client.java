import java.net.*;
import java.io.*;
import java.util.Scanner;
 
public class Client {
    public static void main(String[] args) {
        // if (args.length < 2) {
        //     System.err.println("Uso: java tcp.Cliente <endereco-IP> <porta>");
        //     System.exit(1);
        // }
        
        Client c = new Client();
        // c.iniciar(args[0], Integer.parseInt(args[1]));
        c.iniciar("localhost", 9090);
    }

    public void iniciar(String endereco, int porta) {
        
        Socket conexaoServidor;
        ObjectOutputStream saidaServidor;
        ObjectInputStream entradaServidor;
        Socket conexaoJogo;
        ObjectOutputStream saidaJogo;
        ObjectInputStream entradaJogo;
        Scanner ler = new Scanner(System.in);
        String mensagem = "";
        Boolean turno = false;
        
        try {
            conexaoServidor = new Socket(endereco, porta);
            System.out.println("Conectado ao servidor " + endereco + ", na porta: " + porta);

            // ligando as conexoes de saida e de entrada
            saidaServidor = new ObjectOutputStream(conexaoServidor.getOutputStream());
            saidaServidor.flush();
            entradaServidor = new ObjectInputStream(conexaoServidor.getInputStream());
            
            // Recebe a mensagem de boas-vindas do servidor
            mensagem = receberMensagem(entradaServidor);
            System.out.println(mensagem);
            mensagem = ler.nextLine();
            enviarMensagem(mensagem, saidaServidor);
            
            do {
                //Mensagem do status
                mensagem = receberMensagem(entradaServidor);
                System.out.println(mensagem);
                if (mensagem.contains("status")) {
                    mensagem = ler.nextLine();
                    enviarMensagem(mensagem, saidaServidor);
                }
                if (mensagem.equals("Procurando oponente")){
                    mensagem = receberMensagem(entradaServidor);
                    System.out.println(mensagem);
                    if (mensagem.equals("Aguardando conexão do oponente")) {
                        //parte que vai atuar como servidor do jogo
                        mensagem = receberMensagem(entradaServidor);
                        System.out.println(mensagem);
                        if(mensagem.contains("BRANCAS")) turno = true;
                        // System.out.println("Servidor do jogo");
                        try {
                            //Fluxos do servidor do jogo
                            ServerSocket serverGameSocket = new ServerSocket(2525);
                            conexaoJogo = serverGameSocket.accept();
                            System.out.println("conectado");
                            saidaJogo = new ObjectOutputStream(conexaoJogo.getOutputStream());
                            entradaJogo = new ObjectInputStream(conexaoJogo.getInputStream());                            
                            //função em que ocorre a partida com intercalçao de turnos
                            partida(turno, saidaJogo, entradaJogo, saidaServidor);
                            //fim de jogo
                            System.out.println("Fim de jogo!");
                            enviarMensagem("Fim de Jogo", saidaServidor);
                            saidaJogo.close();
                            entradaJogo.close();
                            conexaoJogo.close();
                            serverGameSocket.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }    
                    } else {
                        //parte que vai atuar como cliente do jogo
                        mensagem = receberMensagem(entradaServidor);
                        System.out.println(mensagem);
                        if (mensagem.contains("BRANCAS")) turno = true;
                        // System.out.println("Cliente do jogo");
                        try {
                            //FLuxos de cliente da partida
                            conexaoJogo = new Socket("localhost", 2525);
                            System.out.println("conectado");
                            saidaJogo = new ObjectOutputStream(conexaoJogo.getOutputStream());
                            entradaJogo = new ObjectInputStream(conexaoJogo.getInputStream());                            
                            //Função da partida
                            partida(turno, saidaJogo, entradaJogo, saidaServidor);
                            //Finalizando o jogo
                            System.out.println("Fim de jogo!");
                            enviarMensagem("Fim de Jogo", saidaServidor);
                            saidaJogo.close();
                            entradaJogo.close();
                            conexaoJogo.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                    //Volta o turno para o padrão
                    turno = false;
                }
            } while (!mensagem.equals("EXIT"));

            saidaServidor.close();
            entradaServidor.close();
            conexaoServidor.close();

        } catch (Exception e) {
            System.err.println("erro: " + e.toString());
        }

    }

    public void enviarMensagem(String mensagem, ObjectOutputStream saida) {
        try {
            saida.writeObject(mensagem);
            saida.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public String receberMensagem(ObjectInputStream entrada) {
        String mensagemRecebida = null;
        try {
            mensagemRecebida = (String) entrada.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        return mensagemRecebida;
    }

    public void partida(Boolean turno, ObjectOutputStream saidaJogo, ObjectInputStream entradaJogo, ObjectOutputStream saidaServidor) {
        String mensagem = "";
        Scanner ler = new Scanner(System.in);
        //aqui teria um timer de cronômetro para controlar o tempo de jogo do jogador
        do {
            if (turno) {
                System.out.println("Seu turno");
                System.out.println("MOVE >> ");
                //se a mensagem não vier antes do cronômetro acabar o jogo acaba
                mensagem = ler.nextLine();
                //AQUI ENTRARIA UMA FUNCAO PARA VERIFICAR SE O MOVIMENTO EH VALIDO OU NÃO
                //caso seja válido, envia a mensagem, se não for, pede por um movimento válido
                enviarMensagem(mensagem, saidaJogo);
                //após enviar a mensagem o tempo pausa
                turno = !turno;
            } else {
                System.out.println("Turno do oponente");
                mensagem = receberMensagem(entradaJogo);
                //após receber uma mensagem o tempo começa a rodar
                System.out.println("MOVE >> " + mensagem);
                turno = !turno;
            }
        } while (!mensagem.contains("#")); //partida termina com a mensagem que tenha o sinal de cheque mate #
    }
}