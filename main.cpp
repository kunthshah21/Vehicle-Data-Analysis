#include "Car.h"
#include "Sorting.h"
#include "Statistics.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

int main()
{
    string filename = "car_prices.csv";
    vector<Car> cars = readDataFromFile(filename);

    // General Sorting testing
    // cout << "Enter the header to sort the dataset (YEAR, MAKE, MODEL, TRIM, BODY, TRANSMISSION, VIN, STATE, CONDITION, ODOMETER, COLOR, INTERIOR, SELLER, MMR, SELLINGPRICE, SALEDATE, CONDITION_VALUE): ";
    // string header;
    // cin >> header;

    // transform(header.begin(), header.end(), header.begin(), ::toupper);

    // if (header == "YEAR" || header == "MMR" || header == "SELLINGPRICE" || header == "ODOMETER" || header == "CONDITION" || header == "CONDITION_VALUE") {
    //     mergeSortInteger(cars, header, 0, cars.size() - 1);
    // } else {
    //     cars = mergeSortString(cars, header);
    // }

    // cout << "\nFirst 500 cars after sorting:\n";
    // printFirst500Cars(cars);

    // Calculate and display average selling price by year
    cout << "\nAverage Selling Price by Year:\n";
    auto averageMap = calculateAverageByYear(cars);
    for (const auto& entry : averageMap) {
        cout << "Year: " << entry.first << ", Average Selling Price: " << entry.second.first << ", Number of Cars: " << entry.second.second << endl;
    }

    calculateTopCarsProportions(cars);
    // cout << "\nCars sorted based on condition value:\n";
    // printFirst500Cars(cars);

    // Color Recognizer
    // Color_recognizer(cars);

    // Sort based on condition value
    

    return 0;
}
