#ifndef STATISTICS_H
#define STATISTICS_H

#include "Car.h"
#include <vector>
#include <map>
#include <unordered_map>


std::map<std::string, float> calculateAveragePriceByTransmission(const std::vector<Car>& cars);
std::map<std::string, std::pair<int, int>> sortAndCountByRegionAndTransmission(std::vector<Car>& cars);
unordered_map<string, pair<int, float>> calculateProportions(const vector<Car>& topCars, int topCount, const unordered_map<string, int>& totalCounts);
void calculateTopCarsProportions(const vector<Car>& cars);
std::map<int, std::pair<float, int> > calculateAverageByYear(const std::vector<Car>& cars);
void Color_recognizer(const std::vector<Car>& cars);
void Interior_recognizer(const std::vector<Car>& cars);


#endif
// ?