import java.util.ArrayList;
import java.util.List;

public class ParkingSystem {

    enum SpaceType {
        COMPACT, LARGE
    }

    static class ParkingSpace {
        int spaceNumber;
        SpaceType type;
        boolean occupied;
        String registrationNumber;

        ParkingSpace(int number, SpaceType type) {
            this.spaceNumber = number;
            this.type = type;
            this.occupied = false;
            this.registrationNumber = "";
        }
    }

    static class ParkingRow {
        int rowNumber;
        List<ParkingSpace> spaces = new ArrayList<>();

        ParkingRow(int number) {
            rowNumber = number;

            for (int i = 1; i <= 8; i++) {
                SpaceType type = (i <= 3)
                    ? SpaceType.COMPACT : SpaceType.LARGE;

                spaces.add(new ParkingSpace(i, type));
            }
        }
    }

    static class ParkingFloor {
        int floorNumber;
        List<ParkingRow> rows = new ArrayList<>();

        ParkingFloor(int number) {
            floorNumber = number;
            rows.add(new ParkingRow(1));
            rows.add(new ParkingRow(2));
        }
    }

    List<ParkingFloor> floors = new ArrayList<>();

    public ParkingSystem() {
        floors.add(new ParkingFloor(1));
        floors.add(new ParkingFloor(2));
    }

    public void parkVehicle(Vehicle vehicle) {

        if (vehicle.getType().equals("Bus")) {

            for (ParkingFloor floor : floors) {
                for (ParkingRow row : floor.rows) {

                    int availableSpaces = 0;

                    for (ParkingSpace space : row.spaces) {

                        if (space.type == SpaceType.LARGE
                                && !space.occupied) {
                            availableSpaces++;
                        } else {
                            availableSpaces = 0;
                        }

                        if (availableSpaces == 5) {

                            int start = space.spaceNumber - 4;

                            for (int i = start - 1; i < start + 4; i++) {
                                row.spaces.get(i).occupied = true;
                                row.spaces.get(i).registrationNumber =
                                    vehicle.getRegistrationNumber();
                            }

                            System.out.println(
                                "Bus parked successfully in five consecutive large spaces!"
                            );
                            return;
                        }
                    }
                }
            }

            System.out.println(
                "No five consecutive large spaces available for the bus!"
            );
            return;
        }

        for (ParkingFloor floor : floors) {
            for (ParkingRow row : floor.rows) {
                for (ParkingSpace space : row.spaces) {

                    if (!space.occupied) {
                        space.occupied = true;
                        space.registrationNumber =
                            vehicle.getRegistrationNumber();

                        System.out.println(
                            vehicle.getType()
                            + " parked successfully in space "
                            + space.spaceNumber
                        );
                        return;
                    }
                }
            }
        }

        System.out.println("No compatible parking space available!");
    }

    public void displayParking() {

        for (ParkingFloor floor : floors) {
            System.out.println("Floor " + floor.floorNumber);

            for (ParkingRow row : floor.rows) {
                System.out.print("  Row " + row.rowNumber + ": ");

                for (ParkingSpace space : row.spaces) {

                    System.out.print(
                        space.type == SpaceType.COMPACT
                        ? "[Compact" : "[Large"
                    );

                    if (space.occupied) {
                        System.out.print(
                            " - Occupied: "
                            + space.registrationNumber + "] "
                        );
                    } else {
                        System.out.print(" - Available] ");
                    }
                }

                System.out.println();
            }
        }
    }
}