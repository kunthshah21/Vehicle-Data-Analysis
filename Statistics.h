#ifndef STATISTICS_H
#define STATISTICS_H

#include "Car.h"
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

struct RegionTransmissionCounts
{
    int manualCount = 0;
    int automaticCount = 0;
};

struct TransmissionCounts
{
    string state;
    int manualCount;
    int automaticCount;
};

struct MakeProportion {
    string make;
    pair<int, float> values;  // {count, proportion}
};

struct YearData {
    int year;
    float averageSellingPrice;
    int carCount;
};

void sortAndCountByRegionAndTransmission(vector<Car> &cars);
void countBestSellingModelByMake(vector<Car> &cars);
pair<float, float> calculateAveragePriceByTransmission(const vector<Car> &cars);
unordered_map<string, pair<int, float>> calculateProportions(const vector<Car> &topCars, int topCount, const unordered_map<string, int> &totalCounts);
void calculateTopCarsProportions(const vector<Car> &cars);
vector<YearData> calculateAverageByYear(const vector<Car>& cars);
void Color_recognizer(const vector<Car> &cars);
void Interior_recognizer(const vector<Car> &cars);
void customSortProportions(vector<pair<string, pair<int, float>>> &proportions);

#endif