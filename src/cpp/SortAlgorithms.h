#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class SortAlgorithms {

public:

    // Bubble Sort
    static void bubbleSort(std::vector<std::string>& vehicles) {

        for (int i = 0; i < vehicles.size(); i++) {
            for (int j = 0; j < vehicles.size() - i - 1; j++) {

                if (vehicles[j] > vehicles[j + 1]) {
                    std::swap(vehicles[j], vehicles[j + 1]);
                }
            }
        }
    }

    // Selection Sort
    static void selectionSort(std::vector<std::string>& vehicles) {

        for (int i = 0; i < vehicles.size(); i++) {

            int minimum = i;

            for (int j = i + 1; j < vehicles.size(); j++) {
                if (vehicles[j] < vehicles[minimum]) {
                    minimum = j;
                }
            }

            std::swap(vehicles[i], vehicles[minimum]);
        }
    }

    // Insertion Sort
    static void insertionSort(std::vector<std::string>& vehicles) {

        for (int i = 1; i < vehicles.size(); i++) {

            std::string current = vehicles[i];
            int j = i - 1;

            while (j >= 0 && vehicles[j] > current) {
                vehicles[j + 1] = vehicles[j];
                j--;
            }

            vehicles[j + 1] = current;
        }
    }

    // Sort vehicles by type using Insertion Sort and a comparator
template <typename VehicleType>
static void sortByVehicleType(
    std::vector<VehicleType>& vehicles
) {
    for (int i = 1; i < vehicles.size(); i++) {

        VehicleType current = vehicles[i];
        int j = i - 1;

        while (j >= 0 &&
               current->getType() < vehicles[j]->getType()) {

            vehicles[j + 1] = vehicles[j];
            j--;
        }

        vehicles[j + 1] = current;
    }
}
};

#endif
