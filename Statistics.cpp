#include <map>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <string>
#include "Statistics.h"
#include "Car.h"
#include "Sorting.h"

// Function to sort cars by region and count manual and automatic transmissions for each region
void sortAndCountByRegionAndTransmission(vector<Car> &cars)
{
    mergeSortString(cars, "STATE");

    vector<TransmissionCounts> regionTransmissionCounts;
    for (const Car &car : cars)
    {
        bool found = false;
        for (const auto &counts : regionTransmissionCounts)
        {
            if (counts.state == car.state)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            regionTransmissionCounts.push_back({car.state, 0, 0});
        }
    }

    for (const Car &car : cars)
    {
        for (auto &counts : regionTransmissionCounts)
        {
            if (counts.state == car.state)
            {
                if (car.transmission == "manual")
                {
                    counts.manualCount++;
                }
                else if (car.transmission == "automatic")
                {
                    counts.automaticCount++;
                }
                break;
            }
        }
    }

    for (auto &counts : regionTransmissionCounts)
    {
        int totalTransmissions = counts.manualCount + counts.automaticCount;
        counts.manualCount = round((counts.manualCount * 100.0) / totalTransmissions);
        counts.automaticCount = 100 - counts.manualCount;
    }

    cout << "Region\tMT(%)\tAT(%)\n";
    for (const auto &counts : regionTransmissionCounts)
    {
        cout << counts.state << "\t" << counts.manualCount << "%\t" << counts.automaticCount << "%\n";
    }
}

// Function to count the best-selling model by make
void countBestSellingModelByMake(vector<Car> &cars) {
    vector<Car> sortedCars = mergeSortString(cars, "MAKE");

    string currentMake = "";
    int currentIndex = 0;

    while (currentIndex < sortedCars.size()) {
        currentMake = sortedCars[currentIndex].make;

        int endIndex = currentIndex;
        while (endIndex < sortedCars.size() && sortedCars[endIndex].make == currentMake) {
            endIndex++;
        }

        vector<Car> makeCars(sortedCars.begin() + currentIndex, sortedCars.begin() + endIndex);

        vector<string> modelList;
        vector<int> modelCounts;

        string bestSellingModel = "";
        int maxCount = 0;

        // Find unique models and count occurrences
        for (const Car &makeCar : makeCars) {
            bool found = false;
            for (size_t i = 0; i < modelList.size(); ++i) {
                if (modelList[i] == makeCar.model) {
                    modelCounts[i]++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                modelList.push_back(makeCar.model);
                modelCounts.push_back(1);
            }
        }

        // Find the best selling model
        for (size_t i = 0; i < modelList.size(); ++i) {
            if (modelCounts[i] > maxCount) {
                maxCount = modelCounts[i];
                bestSellingModel = modelList[i];
            }
        }

        cout << currentMake << ": " << bestSellingModel << endl;

        currentIndex = endIndex;
    }
}


// Function to calculate the average selling price by transmission type
pair<float, float> calculateAveragePriceByTransmission(const vector<Car> &cars) {
    vector<Car> automaticCars;
    vector<Car> manualCars;

    for (const Car &car : cars){
        if (car.transmission == "automatic"){
            automaticCars.push_back(car);
        } else if (car.transmission == "manual"){
            manualCars.push_back(car);
        }
    }

    float totalAutomaticPrice = 0.0;
    for (const Car &car : automaticCars)
    {
        totalAutomaticPrice += car.sellingPrice;
    }
    float averageAutomaticPrice = automaticCars.empty() ? 0.0 : totalAutomaticPrice / automaticCars.size();

    float totalManualPrice = 0.0;
    for (const Car &car : manualCars)
    {
        totalManualPrice += car.sellingPrice;
    }
    float averageManualPrice = manualCars.empty() ? 0.0 : totalManualPrice / manualCars.size();

    return make_pair(averageAutomaticPrice, averageManualPrice);
}

// Function to calculate the proportions of top cars by make
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

// Function to custom sort proportions in descending order
void customSortProportions(vector<pair<string, pair<int, float>>> &proportions)
{
    for (int i = 0; i < proportions.size(); ++i)
    {
        for (int j = i + 1; j < proportions.size(); ++j)
        {
            if (proportions[i].second.second < proportions[j].second.second)
            {
                swap(proportions[i], proportions[j]);
            }
        }
    }
}

// Function to calculate the proportions of top cars
void calculateTopCarsProportions(const vector<Car> &cars)
{
    int topCount = 118080;
    vector<Car> sortedCars = cars;
    mergeSortInteger(sortedCars, "CONDITION_VALUE", 0, sortedCars.size() - 1);
    vector<Car> topCars(sortedCars.begin(), sortedCars.begin() + min(topCount, static_cast<int>(sortedCars.size())));

    unordered_map<string, int> totalCounts;
    for (const auto &car : cars)
    {
        totalCounts[car.make]++;
    }

    unordered_map<string, pair<int, float>> proportions = calculateProportions(topCars, topCount, totalCounts);

    vector<pair<string, pair<int, float>>> proportionsVec(proportions.begin(), proportions.end());

    customSortProportions(proportionsVec);

    cout << "\nProportions of each make in the top " << topCount << " cars (in descending order):\n";
    for (const auto &pair : proportionsVec)
    {
        cout << pair.first << ": " << pair.second.first << "/" << totalCounts[pair.first]
            << " = " << pair.second.second << endl;
    }
}

// Function to recognize the colors of top cars
void Color_recognizer(const vector<Car> &cars)
{
    vector<Car> sortedCars = cars;
    mergeSortInteger(sortedCars, "SELLINGPRICE", 0, sortedCars.size() - 1);

    int numCarsToConsider = ceil(sortedCars.size() * 0.25);

    vector<Car> topCars(sortedCars.begin(), sortedCars.begin() + numCarsToConsider);

    vector<string> colors = {"beige", "black", "blue", "brown", "burgundy", "charcoal", "gold", "gray", "green", "lime", "off-white", "orange", "pink", "purple", "red", "silver", "turquoise", "white", "yellow"};
    vector<int> counts(colors.size(), 0);

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

    cout << "Color count for top 25% of cars based on selling price:\n";
    for (size_t i = 0; i < colors.size(); i++)
    {
        cout << colors[i] << ": " << counts[i] << '\n';
    }
}

// Function to recognize the interiors of top cars
void Interior_recognizer(const vector<Car> &cars)
{
    vector<Car> sortedCars = cars;
    mergeSortInteger(sortedCars, "SELLINGPRICE", 0, sortedCars.size() - 1);

    int numCarsToConsider = ceil(sortedCars.size() * 0.25);

    vector<Car> topCars(sortedCars.begin(), sortedCars.begin() + numCarsToConsider);

    vector<string> interiors = {"beige", "black", "blue", "brown", "burgundy", "gold", "gray", "green", "off-white", "orange", "purple", "red", "silver", "tan", "white", "yellow"};
    vector<int> counts(interiors.size(), 0);

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

    cout << "Interior count for top 25% of cars based on selling price:\n";
    for (size_t i = 0; i < interiors.size(); i++)
    {
        cout << interiors[i] << ": " << counts[i] << '\n';
    }
}



vector<YearData> calculateAverageByYear(const vector<Car>& cars) {
    // Create a vector of YearData to store data for each year
    vector<YearData> averageByYear;

    // Calculate total selling price and count for each year
    for (const Car& car : cars) {
        bool found = false;
        for (YearData& data : averageByYear) {
            if (data.year == car.year) {
                data.averageSellingPrice += car.sellingPrice;
                data.carCount++;
                found = true;
                break;
            }
        }
        if (!found) {
            averageByYear.push_back({car.year, car.sellingPrice, 1});
        }
    }

    // Calculate average selling price for each year
    for (YearData& data : averageByYear) {
        data.averageSellingPrice /= data.carCount;
    }

    return averageByYear;
}
