#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "HashTable.h"

class SearchAlgorithms {

public:

    // Linear Search
    static int linearSearch(
        const std::vector<std::string>& vehicles,
        const std::string& registration
    ) {
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i] == registration) {
                return i;
            }
        }

        return -1;
    }

    // Binary Search
    static int binarySearch(
        std::vector<std::string> vehicles,
        const std::string& registration
    ) {
        std::sort(vehicles.begin(), vehicles.end());

        int left = 0;
        int right = static_cast<int>(vehicles.size()) - 1;

        while (left <= right) {

            int middle = left + (right - left) / 2;

            if (vehicles[middle] == registration) {
                return middle;
            }

            if (vehicles[middle] < registration) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return -1;
    }

    // Hash Search
    static bool hashSearch(
        HashTable& table,
        const std::string& registration
    ) {
        return table.search(registration);
    }
};

#endif
