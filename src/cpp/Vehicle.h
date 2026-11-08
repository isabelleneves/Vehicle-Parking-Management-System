#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>

class Vehicle {
protected:
    std::string registrationNumber;

public:
    Vehicle(std::string registration) {
        registrationNumber = registration;
    }

    virtual std::string getType() const = 0;

    std::string getRegistrationNumber() const {
        return registrationNumber;
    }

    virtual ~Vehicle() {}

    class Motorcycle;
    class Car;
    class Bus;
};

class Vehicle::Motorcycle : public Vehicle {
public:
    Motorcycle(std::string registration)
        : Vehicle(registration) {}

    std::string getType() const override {
        return "Motorcycle";
    }
};

class Vehicle::Car : public Vehicle {
public:
    Car(std::string registration)
        : Vehicle(registration) {}

    std::string getType() const override {
        return "Car";
    }
};

class Vehicle::Bus : public Vehicle {
public:
    Bus(std::string registration)
        : Vehicle(registration) {}

    std::string getType() const override {
        return "Bus";
    }
};

#endif