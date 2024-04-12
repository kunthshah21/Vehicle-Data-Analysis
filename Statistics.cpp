#include "Statistics.h"
#include <map>
#include <iostream>
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

void Color_recognizer(const vector<Car>& cars) {
    vector<string> colors = {"beige", "black", "blue", "brown", "burgundy", "charcoal", "gold", "gray", "green", "lime", "off-white", "orange", "pink", "purple", "red", "silver", "turquoise", "white", "yellow"};
    vector<int> counts(colors.size(), 0);

    for (const Car& car : cars) {
        for (unsigned int i = 0; i < colors.size(); i++) {
            if (car.color == colors[i]) {
                counts[i]++;
                break;
            }
        }
    }

    cout << "Color count:\n";
    for (unsigned int i = 0; i < colors.size(); i++) {
        cout << colors[i] << ": " << counts[i] << '\n';
    }
}