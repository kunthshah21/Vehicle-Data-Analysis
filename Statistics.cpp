#include "Statistics.h"
#include <map>
#include <iostream>
#include "Sorting.h"
using namespace std;

std::map<int, std::pair<float, int>> calculateAverageByYear(const std::vector<Car>& cars) {
    std::map<int, std::pair<float, int>> averageMap;

    for (const Car& car : cars) {
        averageMap[car.year].first += car.sellingPrice; // Accumulate selling prices
        averageMap[car.year].second++; // Count number of cars for each year
    }

    for (auto& entry : averageMap) {
        if (entry.second.second != 0) {
            entry.second.first /= entry.second.second; // Calculate average
        }
    }

    return averageMap;
}
// ?

void Color_recognizer(const std::vector<Car>& cars) {
    // Sort the cars vector based on selling price
    std::vector<Car> sortedCars = cars;
    mergeSortInteger(sortedCars, "SELLINGPRICE", 0, sortedCars.size() - 1); // ?

    // Determine the number of cars to consider (top 25%)
    int numCarsToConsider = std::ceil(sortedCars.size() * 0.25);

    // Consider only the top 25% of the sorted cars
    std::vector<Car> topCars(sortedCars.begin(), sortedCars.begin() + numCarsToConsider);

    // Now, count colors for top 25% cars
    std::vector<std::string> colors = {"beige", "black", "blue", "brown", "burgundy", "charcoal", "gold", "gray", "green", "lime", "off-white", "orange", "pink", "purple", "red", "silver", "turquoise", "white", "yellow"};
    std::vector<int> counts(colors.size(), 0);

    for (const Car& car : topCars) {
        for (size_t i = 0; i < colors.size(); i++) {
            if (car.color == colors[i]) {
                counts[i]++;
                break;
            }
        }
    }

    // Output color counts
    std::cout << "Color count for top 25% of cars based on selling price:\n";
    for (size_t i = 0; i < colors.size(); i++) {
        std::cout << colors[i] << ": " << counts[i] << '\n';
    }
}
