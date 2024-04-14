#include <map>
#include <iostream>
#include <cmath>
#include <unordered_map>

#include "Statistics.h"
#include "Car.h"
#include "Sorting.h"

using namespace std;

#include <vector>
#include <string>

struct TransmissionCounts {
    string state;
    int manualCount;
    int automaticCount;
};

void sortAndCountByRegionAndTransmission(vector<Car>& cars) {
    // Sort cars by region
    mergeSortString(cars, "STATE");

    // Initialize regionTransmissionCounts with empty TransmissionCounts objects
    vector<TransmissionCounts> regionTransmissionCounts;
    for (const Car& car : cars) {
        bool found = false;
        for (const auto& counts : regionTransmissionCounts) {
            if (counts.state == car.state) {
                found = true;
                break;
            }
        }
        if (!found) {
            regionTransmissionCounts.push_back({car.state, 0, 0});
        }
    }

    // Iterate over sorted cars and count manual and automatic transmissions for each region
    for (const Car& car : cars) {
        for (auto& counts : regionTransmissionCounts) {
            if (counts.state == car.state) {
                if (car.transmission == "manual") {
                    counts.manualCount++;
                } else if (car.transmission == "automatic") {
                    counts.automaticCount++;
                }
                break;
            }
        }
    }

    // Calculate total transmissions for each region
    for (auto& counts : regionTransmissionCounts) {
        int totalTransmissions = counts.manualCount + counts.automaticCount;
        // Adjust percentages to ensure they add up to 100
        counts.manualCount = round((counts.manualCount * 100.0) / totalTransmissions);
        counts.automaticCount = 100 - counts.manualCount; // The remaining percentage is for automatic
    }

    // Output percentages of manual and automatic transmissions for each region
    cout << "Region\tMT(%)\tAT(%)\n";
    for (const auto& counts : regionTransmissionCounts) {
        cout << counts.state << "\t" << counts.manualCount << "%\t" << counts.automaticCount << "%\n";
    }
}


void countBestSellingModelByMake(vector<Car>& cars) {
    // Sort cars by make
    vector<Car> sortedCars = mergeSortString(cars, "MAKE");

    // Initialize variables to keep track of current make
    string currentMake = "";
    int currentIndex = 0;

    // Iterate over sorted cars
    while (currentIndex < sortedCars.size()) {
        // Extract current make
        currentMake = sortedCars[currentIndex].make;

        // Find the end index of the current make
        int endIndex = currentIndex;
        while (endIndex < sortedCars.size() && sortedCars[endIndex].make == currentMake) {
            endIndex++;
        }

        // Extract cars of the current make
        vector<Car> makeCars(sortedCars.begin() + currentIndex, sortedCars.begin() + endIndex);

        // Sort cars by model
        vector<Car> sortedMakeCars = mergeSortString(makeCars, "MODEL");

        // Count occurrences of each model and find the best-selling model
        unordered_map<string, int> modelCounts;
        int maxCount = 0;
        string bestSellingModel = "";
        for (const Car& makeCar : sortedMakeCars) {
            modelCounts[makeCar.model]++;
            if (modelCounts[makeCar.model] > maxCount) {
                maxCount = modelCounts[makeCar.model];
                bestSellingModel = makeCar.model;
            }
        }

        // Output the best-selling model for the current make
        cout << "Best-selling model for " << currentMake << ": " << bestSellingModel << endl;

        // Update currentIndex to the next make
        currentIndex = endIndex;
    }
}


pair<float, float> calculateAveragePriceByTransmission(const vector<Car> &cars)
{
    // Separate cars based on transmission type
    vector<Car> automaticCars;
    vector<Car> manualCars;

    for (const Car &car : cars)
    {
        if (car.transmission == "automatic")
        {
            automaticCars.push_back(car);
        }
        else if (car.transmission == "manual")
        {
            manualCars.push_back(car);
        }
    }

    // Calculate average selling price for automatic cars
    float totalAutomaticPrice = 0.0;
    for (const Car &car : automaticCars)
    {
        totalAutomaticPrice += car.sellingPrice;
    }
    float averageAutomaticPrice = automaticCars.empty() ? 0.0 : totalAutomaticPrice / automaticCars.size();

    // Calculate average selling price for manual cars
    float totalManualPrice = 0.0;
    for (const Car &car : manualCars)
    {
        totalManualPrice += car.sellingPrice;
    }
    float averageManualPrice = manualCars.empty() ? 0.0 : totalManualPrice / manualCars.size();

    return make_pair(averageAutomaticPrice, averageManualPrice);
}

unordered_map<string, pair<int, float>> calculateProportions(const vector<Car> &topCars, int topCount, const unordered_map<string, int> &totalCounts)
{
    unordered_map<string, pair<int, float>> proportions;
    for (const auto &car : topCars)
    {
        proportions[car.make].first++;
    }

    for (auto &pair : proportions)
    {
        pair.second.second = static_cast<float>(pair.second.first) / totalCounts.at(pair.first);
    }

    return proportions;
}

void customSortProportions(vector<pair<string, pair<int, float>>> &proportions) {
    for (int i = 0; i < proportions.size(); ++i) {
        for (int j = i + 1; j < proportions.size(); ++j) {
            if (proportions[i].second.second < proportions[j].second.second) {
                swap(proportions[i], proportions[j]);
            }
        }
    }
}



void calculateTopCarsProportions(const vector<Car> &cars)
{
    int topCount = 118080;
    vector<Car> sortedCars = cars;
    mergeSortInteger(sortedCars, "CONDITION_VALUE", 0, sortedCars.size() - 1);
    vector<Car> topCars(sortedCars.begin(), sortedCars.begin() + min(topCount, static_cast<int>(sortedCars.size())));

    // Calculate total counts of cars by make
    unordered_map<string, int> totalCounts;
    for (const auto &car : cars)
    {
        totalCounts[car.make]++;
    }

    // Calculate proportions based on top counts and total counts of cars by make
    unordered_map<string, pair<int, float>> proportions = calculateProportions(topCars, topCount, totalCounts);

    // Convert unordered_map to vector for sorting
    vector<pair<string, pair<int, float>>> proportionsVec(proportions.begin(), proportions.end());

    // Sort proportions in descending order
    customSortProportions(proportionsVec);

    // Display proportions
    cout << "\nProportions of each make in the top " << topCount << " cars (in descending order):\n";
    for (const auto &pair : proportionsVec)
    {
        cout << pair.first << ": " << pair.second.first << "/" << totalCounts[pair.first]
             << " = " << pair.second.second << endl;
    }
}



void Color_recognizer(const std::vector<Car> &cars)
{
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

    for (const Car &car : topCars)
    {
        for (size_t i = 0; i < colors.size(); i++)
        {
            if (car.color == colors[i])
            {
                counts[i]++;
                break;
            }
        }
    }

    // Output color counts
    std::cout << "Color count for top 25% of cars based on selling price:\n";
    for (size_t i = 0; i < colors.size(); i++)
    {
        std::cout << colors[i] << ": " << counts[i] << '\n';
    }
}



void Interior_recognizer(const std::vector<Car> &cars)
{
    // Sort the cars vector based on selling price
    std::vector<Car> sortedCars = cars;
    mergeSortInteger(sortedCars, "SELLINGPRICE", 0, sortedCars.size() - 1);

    // Determine the number of cars to consider (top 25%)
    int numCarsToConsider = std::ceil(sortedCars.size() * 0.25);

    // Consider only the top 25% of the sorted cars
    std::vector<Car> topCars(sortedCars.begin(), sortedCars.begin() + numCarsToConsider);

    // Now, count interiors for top 25% cars
    std::vector<std::string> interiors = {"beige", "black", "blue", "brown", "burgundy", "gold", "gray", "green", "off-white", "orange", "purple", "red", "silver", "tan", "white", "yellow"};
    std::vector<int> counts(interiors.size(), 0);

    for (const Car &car : topCars)
    {
        for (size_t i = 0; i < interiors.size(); i++)
        {
            if (car.interior == interiors[i])
            {
                counts[i]++;
                break;
            }
        }
    }

    // Output interior counts
    std::cout << "Interior count for top 25% of cars based on selling price:\n";
    for (size_t i = 0; i < interiors.size(); i++)
    {
        std::cout << interiors[i] << ": " << counts[i] << '\n';
    }
}
