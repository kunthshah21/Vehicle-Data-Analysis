#ifndef SORTING_H
#define SORTING_H

#include "Car.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<Car> mergeSortString(vector<Car>& cars, const string& header);
void mergeSortInteger(vector<Car>& cars, const string& header, int left, int right);

#endif
