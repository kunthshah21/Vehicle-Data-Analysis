#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Define the Vehicle structure
struct Vehicle {
    int year;
    string make;
    string model;
    string trim;
    string body;
    string transmission;
    string vin;
    string state;
    int condition;
    int odometer;
    string color;
    string interior;
    string seller;
    int mmr;
    int sellingPrice;
    string saleDate;

    // Corrected constructor
    Vehicle(int y, const string& ma, const string& md, const string& t, const string& b, const string& trans,
            const string& v, const string& s, int cond, int odo, const string& col, const string& in,
            const string& sell, int m, int sp, const string& sd) : 
            year(y), make(ma), model(md), trim(t), body(b), transmission(trans),
            vin(v), state(s), condition(cond), odometer(odo), color(col), interior(in),
            seller(sell), mmr(m), sellingPrice(sp), saleDate(sd) {}
};

// Singly Linked List Node
struct Node {
    Vehicle data;
    Node* next;
    Node(const Vehicle& v) : data(v), next(nullptr) {}
};

// Singly Linked List
class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    void append(const Vehicle& v) {
        if (!head) {
            head = new Node(v);
            return;
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new Node(v);
    }

    // Print details of the vehicle at the specified index
    void printVehicleDetails(int index) {
        Node* current = head;
        int count = 0;
        while (current) {
            if (count == index) {
                cout << "Details of the " << index + 1 << "th vehicle:" << endl;
                cout << "Year: " << current->data.year << endl;
                cout << "Make: " << current->data.make << endl;
                cout << "Model: " << current->data.model << endl;
                // Print other fields as needed...
                return;
            }
            current = current->next;
            count++;
        }
        cout << "Vehicle at index " << index << " not found!" << endl;
    }

    // Destructor to clean up memory
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

private:
    Node* head;
};

// Vector wrapper
class VectorWrapper {
public:
    void add(const Vehicle& v) {
        vehicles.push_back(v);
    }

    // Print details of the vehicle at the specified index
    void printVehicleDetails(int index) {
        if (index >= 0 && index < vehicles.size()) {
            cout << "Details of the " << index + 1 << "th vehicle:" << endl;
            cout << "Year: " << vehicles[index].year << endl;
            cout << "Make: " << vehicles[index].make << endl;
            cout << "Model: " << vehicles[index].model << endl;
            // Print other fields as needed...
        } else {
            cout << "Vehicle at index " << index << " not found!" << endl;
        }
    }

private:
    vector<Vehicle> vehicles;
};

// Function to parse CSV and populate the hybrid structure
void loadCSV(const string& filename, LinkedList& linkedList, VectorWrapper& vectorWrapper) {
    ifstream file(filename);
    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        cout << "Reading line: " << line << endl; // Debug output

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 16) { // Assuming all fields are present
            int year = stoi(tokens[0]);
            string make = tokens[1];
            string model = tokens[2];
            string trim = tokens[3];
            string body = tokens[4];
            string transmission = tokens[5];
            string vin = tokens[6];
            string state = tokens[7];
            int condition = stoi(tokens[8]);
            int odometer = stoi(tokens[9]);
            string color = tokens[10];
            string interior = tokens[11];
            string seller = tokens[12];
            int mmr = stoi(tokens[13]);
            int sellingPrice = stoi(tokens[14]);
            string saleDate = tokens[15];

            Vehicle vehicle(year, make, model, trim, body, transmission, vin, state,
                            condition, odometer, color, interior, seller, mmr, sellingPrice, saleDate);
            linkedList.append(vehicle);
            vectorWrapper.add(vehicle);
        } else {
            cout << "Incomplete data in line: " << line << endl; // Debug output
        }
    }
    cout << "Data loading complete." << endl; // Debug output
}

int main() {
    LinkedList linkedList;
    VectorWrapper vectorWrapper;

    // Load data from CSV
    loadCSV("car_prices.csv", linkedList, vectorWrapper);

    // Print details of the 3rd vehicle object
    cout << "Printing details of the 3rd vehicle:" << endl; // Debug output
    linkedList.printVehicleDetails(2); // Index 2 represents the 3rd vehicle
    vectorWrapper.printVehicleDetails(2);

    return 0;
}
