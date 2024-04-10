#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cctype>

using namespace std;

// Define a class to store car data
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

// Function to split a string by comma and return a vector of substrings
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to read data from CSV file and populate cars vector
vector<Car> readDataFromFile(const string& filename) {
    vector<Car> cars;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
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

// Function to display details of a car
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

// Function to merge two vectors of cars based on string header
vector<Car> mergeSortString(const vector<Car>& left, const vector<Car>& right, const string& header) {
    vector<Car> merged;
    unsigned int leftIndex = 0, rightIndex = 0;

    while (leftIndex < left.size() && rightIndex < right.size()) {
        if (header == "MAKE" || header == "MODEL" || header == "TRIM" || header == "BODY" ||
            header == "TRANSMISSION" || header == "VIN" || header == "STATE" || header == "COLOR" ||
            header == "INTERIOR" || header == "SELLER" || header == "SALEDATE") {
            if (left[leftIndex].make + "-" + left[leftIndex].model + "-" + left[leftIndex].trim +
                    "-" + left[leftIndex].body + "-" + left[leftIndex].transmission + "-" +
                    left[leftIndex].vin + "-" + left[leftIndex].state + "-" + left[leftIndex].color +
                    "-" + left[leftIndex].interior + "-" + left[leftIndex].seller + "-" +
                    left[leftIndex].saleDate <=
                right[rightIndex].make + "-" + right[rightIndex].model + "-" + right[rightIndex].trim +
                    "-" + right[rightIndex].body + "-" + right[rightIndex].transmission + "-" +
                    right[rightIndex].vin + "-" + right[rightIndex].state + "-" + right[rightIndex].color +
                    "-" + right[rightIndex].interior + "-" + right[rightIndex].seller + "-" +
                    right[rightIndex].saleDate) {
                merged.push_back(left[leftIndex]);
                leftIndex++;
            } else {
                merged.push_back(right[rightIndex]);
                rightIndex++;
            }
        } else {
            cerr << "Invalid header for string sorting." << endl;
            return merged;
        }
    }

    while (leftIndex < left.size()) {
        merged.push_back(left[leftIndex]);
        leftIndex++;
    }

    while (rightIndex < right.size()) {
        merged.push_back(right[rightIndex]);
        rightIndex++;
    }

    return merged;
}

// Function to perform merge sort on cars based on string header
vector<Car> mergeSortString(vector<Car>& cars, const string& header) {
    if (cars.size() <= 1) {
        return cars;
    }

    vector<Car> left, right;
    unsigned int middle = cars.size() / 2;
    for (unsigned int i = 0; i < middle; i++) {
        left.push_back(cars[i]);
    }
    for (unsigned int i = middle; i < cars.size(); i++) {
        right.push_back(cars[i]);
    }

    left = mergeSortString(left, header);
    right = mergeSortString(right, header);

    return mergeSortString(left, right, header);
}

// Function to partition the vector for quick sort on integer type
int partition(vector<Car>& cars, const string& header, int low, int high) {
    int pivot;
    if (header == "YEAR") {
        pivot = cars[high].year;
    } else if (header == "MMR") {
        pivot = cars[high].mmr;
    } else if (header == "SELLINGPRICE") {
        pivot = cars[high].sellingPrice;
    } else if (header == "ODOMETER") {
        pivot = cars[high].odometer;
    } else if (header == "CONDITION") {
        pivot = cars[high].condition;
    } else {
        cerr << "Invalid header for quick sort." << endl;
        return -1;
    }

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        int value;
        if (header == "YEAR") {
            value = cars[j].year;
        } else if (header == "MMR") {
            value = cars[j].mmr;
        } else if (header == "SELLINGPRICE") {
            value = cars[j].sellingPrice;
        } else if (header == "ODOMETER") {
            value = cars[j].odometer;
        } else if (header == "CONDITION") {
            value = cars[j].condition;
        } else {
            cerr << "Invalid header for quick sort." << endl;
            return -1;
        }

        if (value < pivot) {
            i++;
            swap(cars[i], cars[j]);
        }
    }
    swap(cars[i + 1], cars[high]);
    return (i + 1);
}

// Function to perform quick sort on cars based on integer header
void quickSortInteger(vector<Car>& cars, const string& header, int low, int high) {
    if (low < high) {
        int pi = partition(cars, header, low, high);

        quickSortInteger(cars, header, low, pi - 1);
        quickSortInteger(cars, header, pi + 1, high);
    }
}

// Function to print details of the first 500 cars
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

int main() {
    string filename = "car_prices.csv";
    vector<Car> cars = readDataFromFile(filename);

    cout << "Enter the header to sort the dataset (YEAR, MAKE, MODEL, TRIM, BODY, TRANSMISSION, VIN, STATE, CONDITION, ODOMETER, COLOR, INTERIOR, SELLER, MMR, SELLINGPRICE, SALEDATE): ";
    string header;
    cin >> header;

    transform(header.begin(), header.end(), header.begin(), ::toupper);

    if (header == "YEAR" || header == "MMR" || header == "SELLINGPRICE" || header == "ODOMETER" || header == "CONDITION") {
        quickSortInteger(cars, header, 0, cars.size() - 1);
    } else {
        cars = mergeSortString(cars, header);
    }

    cout << "\nFirst 500 cars after sorting:\n";
    printFirst500Cars(cars);

    return 0;
}
