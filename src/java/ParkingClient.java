import java.io.PrintWriter;
import java.net.Socket;

public class ParkingClient {

    public static void main(String[] args) {

        try (Socket socket = new Socket("localhost", 5000);
             PrintWriter output = new PrintWriter(
                 socket.getOutputStream(), true)) {

            System.out.println("PARKING CLIENT");
            System.out.println("Connecting to server...");

            output.println("Vehicle ABC123 - Motorcycle");

            System.out.println("Message sent successfully!");

        } catch (Exception e) {
            System.out.println("Client error: " + e.getMessage());
        }
    }
}