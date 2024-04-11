#ifndef CAR_H
#define CAR_H

#include <string>
#include <vector>

using namespace std;

class Car {
public:
    int year;
    string make;
    string model;
    string trim;
    string body;
    string transmission;
    string vin;
    string state;
    float condition;
    float odometer;
    string color;
    string interior;
    string seller;
    float mmr;
    float sellingPrice;
    string saleDate;
};

vector<string> split(const string& str, char delimiter);
vector<Car> readDataFromFile(const string& filename);
void displayCarDetails(const Car& car);
void printFirst500Cars(const vector<Car>& cars);

#endif
