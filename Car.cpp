#include "Car.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<Car> readDataFromFile(const string& filename) {
    vector<Car> cars;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return cars;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        Car car;
        car.year = stoi(tokens[0]);
        car.make = tokens[1];
        car.model = tokens[2];
        car.trim = tokens[3];
        car.body = tokens[4];
        car.transmission = tokens[5];
        car.vin = tokens[6];
        car.state = tokens[7];
        car.condition = stof(tokens[8]);
        car.odometer = stof(tokens[9]);
        car.color = tokens[10];
        car.interior = tokens[11];
        car.seller = tokens[12];
        car.mmr = stof(tokens[13]);
        car.sellingPrice = stof(tokens[14]);
        car.saleDate = tokens[15];
        cars.push_back(car);
    }

    file.close();
    return cars;
}

void displayCarDetails(const Car& car) {
    cout << "Year: " << car.year << endl;
    cout << "Make: " << car.make << endl;
    cout << "Model: " << car.model << endl;
    cout << "Trim: " << car.trim << endl;
    cout << "Body: " << car.body << endl;
    cout << "Transmission: " << car.transmission << endl;
    cout << "VIN: " << car.vin << endl;
    cout << "State: " << car.state << endl;
    cout << "Condition: " << car.condition << endl;
    cout << "Odometer: " << car.odometer << endl;
    cout << "Color: " << car.color << endl;
    cout << "Interior: " << car.interior << endl;
    cout << "Seller: " << car.seller << endl;
    cout << "MMR: " << car.mmr << endl;
    cout << "Selling Price: " << car.sellingPrice << endl;
    cout << "Sale Date: " << car.saleDate << endl;
}

void printFirst500Cars(const vector<Car>& cars) {
    int count = 0;
    for (const Car& car : cars) {
        if (count >= 500) {
            break;
        }
        cout << "Car " << count + 1 << ":\n";
        displayCarDetails(car);
        cout << "-----------------------------------\n";
        count++;
    }
}
