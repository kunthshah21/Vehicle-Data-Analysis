#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
void displayCarDetails(const vector<Car>& cars, int index) {
    if (index >= 0 && index < cars.size()) {
        const Car& car = cars[index];
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
    } else {
        cout << "Invalid index." << endl;
    }
}

int main() {
    // Vector to store car objects
    vector<Car> cars = readDataFromFile("car_prices.csv");

    int index = 5; // Change index as needed
    displayCarDetails(cars, index);

    return 0;
}
