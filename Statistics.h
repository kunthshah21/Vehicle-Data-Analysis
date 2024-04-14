#ifndef STATISTICS_H
#define STATISTICS_H

#include "Car.h"
#include <vector>
#include <map>
#include <unordered_map>
struct RegionTransmissionCounts
{
    int manualCount = 0;
    int automaticCount = 0;
};

void sortAndCountByRegionAndTransmission(vector<Car>& cars);
void countBestSellingModelByMake(vector<Car>& cars);
pair<float, float> calculateAveragePriceByTransmission(const vector<Car>& cars);
unordered_map<string, pair<int, float>> calculateProportions(const vector<Car>& topCars, int topCount, const unordered_map<string, int>& totalCounts);
void calculateTopCarsProportions(const vector<Car>& cars);
std::map<int, std::pair<float, int> > calculateAverageByYear(const std::vector<Car>& cars);
void Color_recognizer(const std::vector<Car>& cars);
void Interior_recognizer(const std::vector<Car>& cars);

#endif
// ?