#include "Statistics.h"
#include <map>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include "Sorting.h"

using namespace std;

unordered_map<string, pair<int, float>> calculateProportions(const vector<Car>& topCars, int topCount, const unordered_map<string, int>& totalCounts);

std::map<std::string, float> calculateAveragePriceByTransmission(const std::vector<Car>& cars) {
    // Separate cars based on transmission type
    std::vector<Car> automaticCars;
    std::vector<Car> manualCars;
    
    for (const Car& car : cars) {
        if (car.transmission == "automatic") {
            automaticCars.push_back(car);
        } else if (car.transmission == "manual") {
            manualCars.push_back(car);
        }
    }

    // Calculate average selling price for automatic cars
    float totalAutomaticPrice = 0.0;
    for (const Car& car : automaticCars) {
        totalAutomaticPrice += car.sellingPrice;
    }
    float averageAutomaticPrice = automaticCars.empty() ? 0.0 : totalAutomaticPrice / automaticCars.size();

    // Calculate average selling price for manual cars
    float totalManualPrice = 0.0;
    for (const Car& car : manualCars) {
        totalManualPrice += car.sellingPrice;
    }
    float averageManualPrice = manualCars.empty() ? 0.0 : totalManualPrice / manualCars.size();

    // Store average prices in a map
    std::map<std::string, float> averagePrices;
    averagePrices["AUTOMATIC"] = averageAutomaticPrice;
    averagePrices["MANUAL"] = averageManualPrice;

    return averagePrices;
}


std::map<std::string, std::pair<int, int>> sortAndCountByRegionAndTransmission(std::vector<Car>& cars) {
    // Sort cars by region
    std::vector<Car> sortedCars = mergeSortString(cars, "STATE");

    // Map to store counts of manual and automatic transmissions for each state
    std::map<std::string, std::pair<int, int>> regionTransmissionCounts;

    // Iterate over sorted cars and count manual and automatic transmissions for each state
    for (const Car& car : sortedCars) {
        if (car.transmission == "manual") {
            regionTransmissionCounts[car.state].first++; // Increment manual count for the state
        } else if (car.transmission == "automatic") {
            regionTransmissionCounts[car.state].second++; // Increment automatic count for the state
        }
    }

    return regionTransmissionCounts;
}

unordered_map<string, pair<int, float>> calculateProportions(const vector<Car> &topCars, int topCount, const unordered_map<string, int> &totalCounts)
{
    unordered_map<string, pair<int, float>> proportions;
    for (const auto& car : topCars) {
        proportions[car.make].first++;
    }

    for (auto& pair : proportions) {
        pair.second.second = static_cast<float>(pair.second.first) / totalCounts.at(pair.first);
    }

    return proportions;
}

void calculateTopCarsProportions(const vector<Car>& cars) {
    // Sort cars based on condition value
    vector<Car> sortedCars = cars;
    mergeSortInteger(sortedCars, "CONDITION_VALUE", 0, sortedCars.size() - 1);

    // Get top 3000 cars
    int topCount = 3000;
    vector<Car> topCars(sortedCars.begin(), sortedCars.begin() + min(topCount, static_cast<int>(sortedCars.size())));

    // Calculate total counts of cars by make
    unordered_map<string, int> totalCounts;
    for (const auto& car : cars) {
        totalCounts[car.make]++;
    }

    // Calculate proportions based on top counts and total counts of cars by make
    unordered_map<string, pair<int, float>> proportions = calculateProportions(topCars, topCount, totalCounts);

    // Display proportions
    cout << "\nProportions of each make in the top " << topCount << " cars:\n";
    for (const auto& pair : proportions) {
        cout << pair.first << ": " << pair.second.first << "/" << totalCounts[pair.first] << " = " << pair.second.second << endl;
    }
}


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
