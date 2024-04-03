#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Define a structure to hold the data for each row
struct CarData {
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

// Function to parse CSV line
vector<string> parseCSVLine(const string& line) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to convert CSV line tokens to CarData structure
CarData convertToCarData(const vector<string>& tokens) {
    CarData data;
    data.year = stoi(tokens[0]);
    data.make = tokens[1];
    data.model = tokens[2];
    data.trim = tokens[3];
    data.body = tokens[4];
    data.transmission = tokens[5];
    data.vin = tokens[6];
    data.state = tokens[7];
    data.condition = stof(tokens[8]);
    data.odometer = stof(tokens[9]);
    data.color = tokens[10];
    data.interior = tokens[11];
    data.seller = tokens[12];
    data.mmr = stof(tokens[13]);
    data.sellingPrice = stof(tokens[14]);
    data.saleDate = tokens[15];
    return data;
}

int main() {
    ifstream file("car_prices.csv");
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    getline(file, line); // Ignore the header line

    vector<vector<string>> carDataList;

    while (getline(file, line)) {
        vector<string> tokens = parseCSVLine(line);
        carDataList.push_back(tokens);
    }
    cout << "Data from CSV file inserted into vector of vectors successfully." << endl;
    
    int indexToDisplay = 5;
    cout << "Displaying data at index " << indexToDisplay << ":" << endl;
    for (const auto& data : carDataList[indexToDisplay]) {
        cout << data << " ";
    }
    cout << endl;

    return 0;
}
