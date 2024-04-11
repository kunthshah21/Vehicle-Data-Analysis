#include "Statistics.h"
#include <map>

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
