#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <sys/stat.h>

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

    // Open the CSV file
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return cars;
    }

    string line;
    getline(file, line); // Skip header line

    // Read each line of the file
    while (getline(file, line)) {
        // Split the line by comma
        vector<string> tokens = split(line, ',');

        // Create a Car object and assign values
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

        // Push the car object into the vector
        cars.push_back(car);
    }

    // Close the file
    file.close();

    return cars;
}

// Function to display details of a car at a given index
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

// Function to sort cars by make using Bucket Sort
void sortCarsByMake(vector<Car>& cars) {
    // Create an unordered_map to hold buckets
    unordered_map<string, vector<Car>> buckets;

    // Distribute cars into buckets based on make
    for (const Car& car : cars) {
        buckets[car.make].push_back(car);
    }

    // Sort each bucket individually
    for (auto& pair : buckets) {
        sort(pair.second.begin(), pair.second.end(), [](const Car& a, const Car& b) {
            return a.make < b.make;
        });
    }

    // Merge sorted buckets back into the original vector
    cars.clear();
    for (const auto& pair : buckets) {
        cars.insert(cars.end(), pair.second.begin(), pair.second.end());
    }
}

// Function to write cars to separate CSV files for each make
void writeCarsToCSVFiles(const vector<Car>& cars) {
    string folderName = "MAKE_WISE_CSV/";

    unordered_map<string, ofstream> makeFiles;

    // Create a separate CSV file for each make
    for (const Car& car : cars) {
        if (makeFiles.find(car.make) == makeFiles.end()) {
            string filename = folderName + car.make + ".csv";
            makeFiles[car.make].open(filename);
            makeFiles[car.make] << "Year,Make,Model,Trim,Body,Transmission,VIN,State,Condition,Odometer,Color,Interior,Seller,MMR,SellingPrice,SaleDate\n";
        }

        makeFiles[car.make] << car.year << "," << car.make << "," << car.model << ","
                            << car.trim << "," << car.body << "," << car.transmission << ","
                            << car.vin << "," << car.state << "," << car.condition << ","
                            << car.odometer << "," << car.color << "," << car.interior << ","
                            << car.seller << "," << car.mmr << "," << car.sellingPrice << ","
                            << car.saleDate << "\n";
    }

    // Close all file streams
    for (auto& pair : makeFiles) {
        pair.second.close();
    }

    cout << "Cars sorted and written to separate CSV files for each make in folder: " << folderName << endl;
}

int main() {
    // Vector to store car objects
    vector<Car> cars = readDataFromFile("car_prices.csv");

    // Sort cars by make
    sortCarsByMake(cars);

    // Write sorted cars to separate CSV files for each make
    writeCarsToCSVFiles(cars);

    return 0;
}
