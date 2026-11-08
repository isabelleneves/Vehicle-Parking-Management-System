public abstract class Vehicle {
    protected String registrationNumber;

    public Vehicle(String registrationNumber) {
        this.registrationNumber = registrationNumber;
    }

    public String getRegistrationNumber() {
        return registrationNumber;
    }

    public abstract String getType();

    public static class Motorcycle extends Vehicle {
        public Motorcycle(String registrationNumber) {
            super(registrationNumber);
        }

        public String getType() {
            return "Motorcycle";
        }
    }

    public static class Car extends Vehicle {
        public Car(String registrationNumber) {
            super(registrationNumber);
        }

        public String getType() {
            return "Car";
        }
    }

    public static class Bus extends Vehicle {
        public Bus(String registrationNumber) {
            super(registrationNumber);
        }

        public String getType() {
            return "Bus";
        }
    }
}
