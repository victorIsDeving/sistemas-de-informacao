import java.io.*;
import java.net.*;


class ClientTCPBasic {
    public static void main(String[] args) throws Exception {
        String serverName = "localhost";
        int port = 8722; // Same port number with the server
        Socket socket = null;
        PrintStream toServer;
        BufferedReader fromServer;
 
        System.out.println("TCP Client launched, using server: " + serverName + ", Port: " + port);
 
        // Read from user input
        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
        String userInput;
        String responseFromServer;
        do {
            System.out.print("\nFollowing commands are available:\n");
            System.out.print("0 - See movies in catalog\n");
            System.out.print("1 - Enter new movie and score\n");
            System.out.print("2 - Change movie's score\n");
            System.out.print("Enter QUIT to leave application\n");
            System.out.flush();
            userInput = inFromUser.readLine();
            if (userInput.equalsIgnoreCase("quit")) {
                break;
            }
            // Open a new socket connection to the server with the specified port number
            socket = new Socket(serverName, port);
            // Send user input to server
            toServer = new PrintStream(socket.getOutputStream());
            toServer.println(userInput);
            switch (userInput) {
                case "0":
                    System.out.println("[TCPClient] Send out user input [" + userInput + " - Movies List ] to Server.");

                    // Get response from server
                    fromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    responseFromServer = fromServer.readLine();
                    System.out.println("[TCPClient] Get response \n" + responseFromServer);
                    break;
                case "1":
                    System.out.println("[TCPClient] Send out user input [" + userInput + " - Insert New movie ] to Server.");

                    // Read from user input movie name
                    BufferedReader newMovieName = new BufferedReader(new InputStreamReader(System.in));
                    System.out.print("What movie would you like to add?\n");
                    System.out.flush();
                    String newMovieNameInput = newMovieName.readLine();
                    // Send user input to server
                    toServer = new PrintStream(socket.getOutputStream());
                    toServer.println(newMovieNameInput);
                    System.out.println("[TCPClient] Send out user input [" + newMovieNameInput + "] to Server.");
                    // Get response from server
                    fromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    responseFromServer = fromServer.readLine();

                    if (responseFromServer.equalsIgnoreCase("100")) {
                        System.out.println("[TCPClient] Get response from server: " + responseFromServer + "\n  Movie already in the database!");
                    } else {
                        System.out.println("[TCPClient] Get response from server: \n" + responseFromServer);
                        // Read from user input movie score
                        BufferedReader newMovieScore = new BufferedReader(new InputStreamReader(System.in));
                        System.out.print("What Score would you like to set (from 0 to 100)?\n");
                        System.out.flush();
                        String newMovieScoreInput = newMovieScore.readLine();
                        // Send user input to server
                        toServer = new PrintStream(socket.getOutputStream());
                        toServer.println(newMovieScoreInput);
                        System.out.println("[TCPClient] Send out user input [" + newMovieScoreInput + "] to Server.");
                        // Get response from server
                        fromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                        responseFromServer = fromServer.readLine();
                        System.out.println("[TCPClient] Get response from server: \n" + responseFromServer);
                    }
                    break;
                case "2":
                    System.out.println("[TCPClient] Send out user input [" + userInput + " - Change Movie Score ] to Server.");

                    // Read from user input movie name
                    BufferedReader changeMovieName = new BufferedReader(new InputStreamReader(System.in));
                    System.out.print("What movie would you like to change it's score?\n");
                    System.out.flush();
                    String changeMovieNameInput = changeMovieName.readLine();
                    // Send user input to server
                    toServer = new PrintStream(socket.getOutputStream());
                    toServer.println(changeMovieNameInput);
                    System.out.println("[TCPClient] Send out user input [" + changeMovieNameInput + "] to Server.");
                    // Get response from server
                    fromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    responseFromServer = fromServer.readLine();
                    if (responseFromServer.equalsIgnoreCase("403")) {
                        System.out.println("[TCPClient] Get response from server: " + responseFromServer + "\n  Movie not found in database!");
                    } else {
                        System.out.println("[TCPClient] Get response from server: \n" + responseFromServer);

                        // Read from user new score value
                        BufferedReader changeMovieScore = new BufferedReader(new InputStreamReader(System.in));
                        System.out.print("What score do you want to set it to?\n");
                        System.out.flush();
                        String changeMovieScoreInput = changeMovieScore.readLine();
                        // Send user input to server
                        toServer = new PrintStream(socket.getOutputStream());
                        toServer.println(changeMovieScoreInput);
                        System.out.println("[TCPClient] Send out user input [" + changeMovieScoreInput + "] to Server.");
                        // Get response from server
                        fromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                        responseFromServer = fromServer.readLine();
                        System.out.println("[TCPClient] Get response from server: \n" + responseFromServer);
                    }
                    break;
                default:
                    System.out.println("[TCPClient] Send out user input [" + userInput + "] to Server.");
                    // Get response from server
                    fromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    responseFromServer = fromServer.readLine();
                    System.out.println("[TCPClient] Get response from server: \n" + responseFromServer);
            }
        } while (!userInput.equals("quit")); // End the client if 'quit' is an input
 
        // Close connection
        if (socket != null) {
            socket.close();
        }
    }
}
