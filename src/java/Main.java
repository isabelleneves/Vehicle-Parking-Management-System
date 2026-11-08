public class Main {
    public static void main(String[] args) {

        ParkingSystem parking = new ParkingSystem();

        Vehicle.Motorcycle motorcycle =
            new Vehicle.Motorcycle("ABC123");

        Vehicle.Car car =
            new Vehicle.Car("DEF456");

        Vehicle.Bus bus =
            new Vehicle.Bus("GHI789");

        System.out.println("VEHICLE PARKING MANAGEMENT SYSTEM");
        System.out.println("---------------------------------");

        parking.parkVehicle(motorcycle);
        parking.parkVehicle(car);
        parking.parkVehicle(bus);

        System.out.println();
        System.out.println("PARKING STATUS");

        parking.displayParking();
    }
}