public class Main {
    public static void main(String[] args) {

        Vehicle.Motorcycle motorcycle =
            new Vehicle.Motorcycle("ABC123");

        Vehicle.Car car =
            new Vehicle.Car("DEF456");

        Vehicle.Bus bus =
            new Vehicle.Bus("GHI789");

        System.out.println("VEHICLE REGISTRATION TEST");
        System.out.println("-------------------------");

        System.out.println(motorcycle.getType() + " - "
            + motorcycle.getRegistrationNumber());

        System.out.println(car.getType() + " - "
            + car.getRegistrationNumber());

        System.out.println(bus.getType() + " - "
            + bus.getRegistrationNumber());
    }
}