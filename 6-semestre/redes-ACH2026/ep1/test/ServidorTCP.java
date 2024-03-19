import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

class Syncer {
    public void retirarLista(List<ServidorTCP.ClienteHandler> clientesProntos, ServidorTCP.ClienteHandler jogador1) {
        try {
            clientesProntos.remove(jogador1);
        } catch (Exception e) {
            System.out.println("Thread  interrupted.");
        }
    }
}

public class ServidorTCP {
    
    private static List<ClienteHandler> clientesDisponiveis = new ArrayList<>();
    private static List<ClienteHandler> clientesProntos = new ArrayList<>();
    
    public static void main(String[] args) {
        // int porta = -1;
        
        // //verificando se foi informado 1 argumento de linha de comando
        // if (args.length < 1 || args.length > 1) {
        //     System.err.println("Uso: java tcp.Servidor <porta>");
        //     System.exit(1);
        // }
        // // para garantir que somente inteiros serao atribuidos a porta
        // try { 
            //     porta = Integer.parseInt(args[0]);

        // } catch (Exception e) {
        //     System.err.println("Erro: " + e.toString());
        //     System.exit(1);
        // }

        // if (porta < 1024) {
            //     System.err.println("A porta deve ser maior que 1024.");
            //     System.exit(1);
            // }
            
            ServidorTCP s = new ServidorTCP();
            // s.startServer(porta);
            s.startServer(9090);
    }

    public static void enviarMensagem(String mensagem, ObjectOutputStream saida) {
        try {
            saida.writeObject(mensagem);
            saida.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public static String receberMensagem(ObjectInputStream entrada) {
        String mensagemRecebida = null;
        try {
            mensagemRecebida = (String) entrada.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        return mensagemRecebida;
    }

    public void startServer(int porta) {
        Syncer S = new Syncer();
        try {
            ServerSocket serverSocket = new ServerSocket(porta);
            System.out.println("Servidor aguardando conexões...");

            while (true) {
                Socket clienteSocket = serverSocket.accept();
                System.out.println("Novo cliente conectado.");

                ClienteHandler clienteHandler = new ClienteHandler(clienteSocket, S);
                clientesDisponiveis.add(clienteHandler);

                Thread threadCliente = new Thread(clienteHandler);
                threadCliente.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    static class ClienteHandler implements Runnable {
        private Socket serverSocket;
        private boolean prontoParaJogar = false;
        private String playerName = "";
        private boolean turno = false;
        private boolean inGame = false;
        static Syncer S;
        // Outros atributos e métodos necessários para a lógica do jogo
        
        public ClienteHandler(Socket socket, Syncer s) {
            this.serverSocket = socket;
            S = s;
        }

        @Override
        public void run() {
            ObjectOutputStream saida;
            ObjectInputStream entrada;
            String mensagem = "";
            try {
                //obtendo os fluxos de entrada e de saida
                saida = new ObjectOutputStream(serverSocket.getOutputStream());
                entrada = new ObjectInputStream(serverSocket.getInputStream());
                
                //confirmando a conexao ao cliente
                System.out.println("Conexao estabelecida com " + serverSocket.getInetAddress().getHostAddress());
                
                //Mensagem do nome do jogador
                enviarMensagem("Type your player name: ", saida);
                playerName = receberMensagem(entrada);

                do {
                    //Mensagem do Status
                    enviarMensagem("Set a status\n    1: online\n    2: offline\n    EXIT", saida);
                    mensagem = receberMensagem(entrada);
                    if(mensagem.equals("1")) setProntoParaJogar();
                    if (getProntoParaJogar()) {
                        adicionarProntoParaJogar(this);
                        enviarMensagem("Procurando oponente", saida);
                        emparelharClientes(entrada, saida, this);
                    }
                } while (!mensagem.equals("EXIT"));

                System.out.println("Conexao encerrada pelo cliente " + playerName);
            }  catch (Exception e) {
                System.err.println("Erro: " + e.toString());
            }
        }

        public void setProntoParaJogar() {
            prontoParaJogar = true;
        }

        public boolean getProntoParaJogar() {
            return prontoParaJogar;
        }

        public String getPlayerName() {
            return this.playerName;
        }
        
        public synchronized void adicionarProntoParaJogar(ClienteHandler cliente) {
            clientesProntos.add(cliente);
        }

        public synchronized static void retirarProntoParaJogar(ClienteHandler cliente) {
            clientesProntos.remove(cliente);
        }
        
        private static void emparelharClientes(
                                            ObjectInputStream entrada, 
                                            ObjectOutputStream saida, 
                                            ClienteHandler cliente) {
            //iterar sobre a lista dos clientes prontos para achar os clientes que não estão em jogo para parear
            while (true) {
                // Verifica se há pelo menos um oponente disponível
                if (clientesProntos.size() >= 2) {
                    ClienteHandler cliente1 = clientesProntos.get(0);
                    ClienteHandler cliente2 = clientesProntos.get(1);
                    
                    if (cliente1.equals(cliente)) {
                        // clientesProntos.remove(cliente1);
                        emJogo(cliente1, cliente2, entrada, saida); 
                    } else {
                        // clientesProntos.remove(cliente2);
                        emJogo(cliente2, cliente1, entrada, saida);
                    }
                    
                    if (clientesProntos.contains(cliente1) && clientesProntos.contains(cliente2)) {
                            retirarProntoParaJogar(cliente2);
                            retirarProntoParaJogar(cliente1);
                    }
                    
                    // Sai do loop após o jogo, volta para pedir um status
                    break; 
                }
                try {
                    // Aguarda um curto período antes de verificar novamente
                    Thread.sleep(1000); // Aguarda 1 segundo antes de verificar novamente
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        private static void emJogo(
                                        ClienteHandler jogador1, 
                                        ClienteHandler jogador2, 
                                        ObjectInputStream entrada, 
                                        ObjectOutputStream saida) {
            System.out.println("Jogo começado: " + jogador1.getPlayerName() + " x " + jogador2.getPlayerName());
            // Primeiro jogador que entrar no iniciar jogo vai preparar 
            //o turno para o segundo jogador
            if (!jogador1.inGame && !jogador2.inGame) {
                enviarMensagem("Aguardando conexão do oponente", saida);
                jogador1.inGame = true;
                jogador2.inGame = true;
                // Determina aleatoriamente quem começa com as brancas
                jogador1.turno = Math.random() < 0.5;
                jogador2.turno = !jogador1.turno;
            } else {
                enviarMensagem("Conectando ao oponente", saida);
            }

            // Sincronizar a thread dos jogadores para que ambos possam ser retirados da lista de prontos
            // synchronized (S) {
            //     S.retirarLista(clientesProntos, jogador1);
            //     S.retirarLista(clientesProntos, jogador2);
            // }            
            // retirarProntoParaJogar(jogador1);
            // retirarProntoParaJogar(jogador2);
            
            if (jogador1.turno) {
                enviarMensagem("Você vai jogar contra " + jogador2.getPlayerName() + " com as BRANCAS. Boa sorte!", saida);
            } else {
                enviarMensagem("Você vai jogar contra " + jogador2.getPlayerName() + " com as PRETAS. Boa sorte!", saida);
            }
            
            //Loop que vai esperar os jogadores terminarem a partida
            String mensagem = "";
            do {
                mensagem = receberMensagem(entrada);
            } while (!mensagem.equalsIgnoreCase("Fim de jogo"));
            
            System.out.println("Jogo terminado: " + jogador1.getPlayerName() + " x " + jogador2.getPlayerName());
            //Finaliza voltando as variáveis para o padrão
            jogador1.inGame = false;
            jogador1.turno = false;
            jogador2.inGame = false;
            jogador2.turno = false;
        }
        
        // Outros métodos para a lógica do jogo
    }
}
