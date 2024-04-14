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
    // -----------------------------------------------------------
    // -------------- Read data from csv -------------------------
    // -----------------------------------------------------------
    string filename = "car_prices.csv";
    vector<Car> cars = readDataFromFile(filename);

    // -----------------------------------------------------------
    // ------------- General Sorting testing ---------------------
    // -----------------------------------------------------------
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

    // -----------------------------------------------------------
    // ----------- Average selling price by year -----------------
    // -----------------------------------------------------------
    // cout << "\nAverage Selling Price by Year:\n";
    // auto averageMap = calculateAverageByYear(cars);
    // for (const auto& entry : averageMap) {
    //     cout << "Year: " << entry.first << ", Average Selling Price: " << entry.second.first << ", Number of Cars: " << entry.second.second << endl;
    // }


    // calculateTopCarsProportions(cars);
    // cout << "\nAverage Selling Price by Year:\n";
    // auto averageMap = calculateAverageByYear(cars);
    // for (const auto& entry : averageMap) {
    //     cout << "Year: " << entry.first << ", Average Selling Price: " << entry.second.first << ", Number of Cars: " << entry.second.second << endl;
    // }
    // std::map<std::string, std::pair<int, int>> regionTransmissionCounts = sortAndCountByRegionAndTransmission(cars);

    // -----------------------------------------------------------
    // ------------------ Condition Value ------------------------
    // -----------------------------------------------------------
    // calculateTopCarsProportions(cars);


    // -----------------------------------------------------------
    // ------------------ Region wise Transmission----------------
    // -----------------------------------------------------------
    // sortAndCountByRegionAndTransmission(cars);



    // -----------------------------------------------------------
    // ------------------ Color Recognizer -----------------------
    // -----------------------------------------------------------

    // Color_recognizer(cars);
    // Interior_recognizer(cars);


    // -----------------------------------------------------------
    // --------------- Average Price for At/MT Cars --------------
    // -----------------------------------------------------------

    pair<float, float> averages = calculateAveragePriceByTransmission(cars);

    cout << "Average selling price for automatic cars: $" << averages.first << endl;
    cout << "Average selling price for manual cars: $" << averages.second << endl;
}
