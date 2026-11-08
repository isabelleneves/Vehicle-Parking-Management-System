import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class ParkingServer {

    public static void main(String[] args) {

        try (ServerSocket server = new ServerSocket(5000)) {

            System.out.println("PARKING SERVER");
            System.out.println("Waiting for client...");

            try (Socket socket = server.accept();
                 BufferedReader input = new BufferedReader(
                     new InputStreamReader(socket.getInputStream()))) {

                String message = input.readLine();

                System.out.println("Message received:");
                System.out.println(message);
            }

        } catch (Exception e) {
            System.out.println("Server error: " + e.getMessage());
        }
    }
}
