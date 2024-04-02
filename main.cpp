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

// Define a node structure for the Singly Linked List
struct Node {
    CarData data;
    Node* next;
};

// Define a class for the Singly Linked List
class SLL {
public:
    SLL() : head(nullptr) {}
    ~SLL() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
    void insert(const CarData& data) {
        Node* newNode = new Node{data, nullptr};
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    void display(int index) {
        Node* current = head;
        int currentIndex = 0;
         while (current && currentIndex < index) {
            current = current->next;
            currentIndex++;
        }
        if (current && currentIndex == index) {
            displayCarData(current->data);
        } else {
            cout << "Index out of range." << endl;
        }
    }

    private:
    Node* head;

    void displayCarData(const CarData& data) {
        cout << "Year: " << data.year << ", Make: " << data.make << ", Model: " << data.model
             << ", Trim: " << data.trim << ", Body: " << data.body << ", Transmission: " << data.transmission
             << ", VIN: " << data.vin << ", State: " << data.state << ", Condition: " << data.condition
             << ", Odometer: " << data.odometer << ", Color: " << data.color << ", Interior: " << data.interior
             << ", Seller: " << data.seller << ", MMR: " << data.mmr << ", Selling Price: " << data.sellingPrice
             << ", Sale Date: " << data.saleDate << endl;
    }
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

    SLL carList;

    while (getline(file, line)) {
        vector<string> tokens = parseCSVLine(line);
        CarData carData = convertToCarData(tokens);
        carList.insert(carData);
    }
    cout << "Data from CSV file inserted into Singly Linked List successfully." << endl;
    
    int indexToDisplay = 5;
    cout << "Displaying data at index " << indexToDisplay << ":" << endl;
    carList.display(indexToDisplay);

    return 0;
}
