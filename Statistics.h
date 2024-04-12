#ifndef STATISTICS_H
#define STATISTICS_H

#include "Car.h"
#include <vector>
#include <map>

std::map<int, std::pair<float, int> > calculateAverageByYear(const std::vector<Car>& cars);
void Color_recognizer(const std::vector<Car>& cars);

#endif
// ?