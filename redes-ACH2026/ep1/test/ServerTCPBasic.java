import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

class ServerTCPBasic {
    public static void main(String[] args) throws Exception {
        // Building a database for testing purposes
        List<Film> database = new ArrayList<>();
        database.add(new Film(100, "Coach Carter"));
        database.add(new Film(95, "Uncut Gems"));
        database.add(new Film(100, "Hustle"));
        database.add(new Film(97, "Glory Road"));
        database.add(new Film(85, "The Fab Five"));
        database.add(new Film(90, "White Men Can't Jump"));
        database.add(new Film(100, "Space Jam"));
        database.add(new Film(90, "The Redeem Team"));
        database.add(new Film(60, "He Got Game"));
        database.add(new Film(96, "The Last Shot"));

        // Set socket port and some basic variables that are used for connecting and transferring information
        int port = 8722;
        Socket socket;
        BufferedReader reader; // Local reader from the client
        PrintStream outputStream; // Output stream to the client
        String clientRequest;
        ServerSocket ss = new ServerSocket(port);
        System.out.println("TCP Server is starting up, listening at port " + port + ".");

        while (true) {
            // StringBuilder to create responses on the run for every loop
            StringBuilder responseToClient = new StringBuilder();

            // Get request from client
            socket = ss.accept();
            reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            clientRequest = reader.readLine();
            // Send response to client
            outputStream = new PrintStream(socket.getOutputStream());
            String finalString;
            // Treating client responses per cases
            switch (clientRequest) {
                case "0":
                    System.out.println("[TCPServer] Get request [" + clientRequest + " - Movies List] from Client.");
                    Iterator<Film> itr = database.iterator();
                    while (itr.hasNext()) {
                        Film current = itr.next();
                        responseToClient.append(" [ " + current.getName() + " " + current.getScore() + "/100" + " ] ");
                    }
                    finalString = responseToClient.toString();
                    outputStream.println(finalString);
                    System.out.println("[TCPServer] Sent full movies list with scores \n" + finalString);
                    break;
                case "1":
                    System.out.println("[TCPServer] Get request [" + clientRequest + " - Insert Movie] from Client.");

                    // Get movie name from client
                    reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    clientRequest = reader.readLine();
                    System.out.println("[TCPServer] Get request [" + clientRequest + "] from Client.");
                    Film movie = new Film(0, clientRequest);

                    // For Each Loop for iterating ArrayList, find movie in array list
                    Film newMovie = null;
                    for (Film i : database) {
                        if ( i.getName().equalsIgnoreCase(clientRequest)) {
                            newMovie = i;
                            break;
                        }
                    }

                    if ( newMovie != null ) {
                        // Send error message for Client
                        responseToClient.append("100");
                        finalString = responseToClient.toString();
                        outputStream.println(finalString);
                    } else {
                        // Send movie name confirmation for Client
                        responseToClient.append("   Movie " + clientRequest + " received!");
                        finalString = responseToClient.toString();
                        outputStream.println(finalString);

                        // Get movie score from client
                        responseToClient = new StringBuilder();
                        reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                        clientRequest = reader.readLine();
                        System.out.println("[TCPServer] Get request [" + clientRequest + "] from Client.");
                        movie.setScore(Integer.parseInt(clientRequest));
                        // Send movie score confirmation to Client
                        responseToClient.append("   Movie score " + movie.getScore() + "/100 received for movie " + movie.getName() + "!");
                        finalString = responseToClient.toString();
                        outputStream.println(finalString);

                        // Add movie to database
                        database.add(movie);
                    }
                    break;
                case "2":
                    System.out.println("[TCPServer] Get request [" + clientRequest + " - Change Movie Score] from Client.");

                    // Get movie name from client
                    reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    clientRequest = reader.readLine();
                    System.out.println("[TCPServer] Get request [" + clientRequest + "] from Client.");

                    // For Each Loop for iterating ArrayList, find movie in array list
                    Film selectedMovie = null;
                    for (Film i : database) {
                        if ( i.getName().equalsIgnoreCase(clientRequest)) {
                            selectedMovie = i;
                            break;
                        }
                    }

                    if ( selectedMovie == null ) {
                        // Send error message for Client
                        responseToClient.append("402");
                    } else {
                        // Send movie name confirmation for Client
                        responseToClient.append("   Movie " + selectedMovie.getName() + " currently has the score of " + selectedMovie.getScore() + "/100");
                        finalString = responseToClient.toString();
                        outputStream.println(finalString);

                        // Get movie score from client
                        responseToClient = new StringBuilder();
                        reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                        clientRequest = reader.readLine();
                        System.out.println("[TCPServer] Get request [" + clientRequest + "] from Client.");

                        // Change movie score
                        selectedMovie.setScore(Integer.parseInt(clientRequest));

                        // Send movie score confirmation to Client
                        responseToClient.append("   Movie " + selectedMovie.getName() + " score set to " + selectedMovie.getScore() + "/100");
                    }
                    finalString = responseToClient.toString();
                    outputStream.println(finalString);
                    break;
                default:
                    System.out.println("[TCPServer] Get request [" + clientRequest + "] from Client.");
                    responseToClient.append("   Command not recognized");
                    finalString = responseToClient.toString();
                    outputStream.println(finalString);
                    break;
            }
        }
    }
}
