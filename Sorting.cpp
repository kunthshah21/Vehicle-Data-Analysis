#include "Sorting.h"
#include "Car.h"
#include <iostream>

using namespace std;

vector<Car> mergeStringVectors(const vector<Car>& left, const vector<Car>& right, const string& header) {
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

    return mergeStringVectors(left, right, header);
}

void merge(vector<Car>& cars, const string& header, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<Car> L, R;
    for (int i = 0; i < n1; i++) {
        L.push_back(cars[left + i]);
    }
    for (int j = 0; j < n2; j++) {
        R.push_back(cars[middle + 1 + j]);
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        int value1, value2;
        if (header == "YEAR") {
            value1 = L[i].year;
            value2 = R[j].year;
        } else if (header == "MMR") {
            value1 = L[i].mmr;
            value2 = R[j].mmr;
        } else if (header == "SELLINGPRICE") {
            value1 = L[i].sellingPrice;
            value2 = R[j].sellingPrice;
        } else if (header == "ODOMETER") {
            value1 = L[i].odometer;
            value2 = R[j].odometer;
        } else if (header == "CONDITION") {
            value1 = L[i].condition;
            value2 = R[j].condition;
        } else if (header == "CONDITION_VALUE") {
            value1 = L[i].condition_value;
            value2 = R[j].condition_value;
        } else {
            cerr << "Invalid header for merge sort." << endl;
            return;
        }

        if (header == "CONDITION_VALUE") {
            if (value1 >= value2) { // Change the comparison to sort in descending order
                cars[k] = L[i];
                i++;
            } else {
                cars[k] = R[j];
                j++;
            }
        } else {
            if (value1 <= value2) { // Original comparison for other headers to sort in ascending order
                cars[k] = L[i];
                i++;
            } else {
                cars[k] = R[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1) {
        cars[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        cars[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortInteger(vector<Car>& cars, const string& header, int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;
    mergeSortInteger(cars, header, left, middle);
    mergeSortInteger(cars, header, middle + 1, right);
    merge(cars, header, left, middle, right);
}

int partition(vector<Car>& cars, const string& header, int low, int high) {
    string pivot;
    if (header == "MAKE" || header == "MODEL" || header == "TRIM" || header == "BODY" ||
        header == "TRANSMISSION" || header == "VIN" || header == "STATE" || header == "COLOR" ||
        header == "INTERIOR" || header == "SELLER" || header == "SALEDATE") {
        pivot = cars[high].make + "-" + cars[high].model + "-" + cars[high].trim +
                "-" + cars[high].body + "-" + cars[high].transmission + "-" +
                cars[high].vin + "-" + cars[high].state + "-" + cars[high].color +
                "-" + cars[high].interior + "-" + cars[high].seller + "-" +
                cars[high].saleDate;
    } else {
        cerr << "Invalid header for quick sort." << endl;
        return -1;
    }

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        string current;
        if (header == "MAKE" || header == "MODEL" || header == "TRIM" || header == "BODY" ||
            header == "TRANSMISSION" || header == "VIN" || header == "STATE" || header == "COLOR" ||
            header == "INTERIOR" || header == "SELLER" || header == "SALEDATE") {
            current = cars[j].make + "-" + cars[j].model + "-" + cars[j].trim +
                      "-" + cars[j].body + "-" + cars[j].transmission + "-" +
                      cars[j].vin + "-" + cars[j].state + "-" + cars[j].color +
                      "-" + cars[j].interior + "-" + cars[j].seller + "-" +
                      cars[j].saleDate;
        } else {
            cerr << "Invalid header for quick sort." << endl;
            return -1;
        }

        if (current <= pivot) {
            i++;
            swap(cars[i], cars[j]);
        }
    }
    swap(cars[i + 1], cars[high]);
    return (i + 1);
}

void quickSortString(vector<Car>& cars, const string& header, int low, int high) {
    if (low < high) {
        int pi = partition(cars, header, low, high);
        quickSortString(cars, header, low, pi - 1);
        quickSortString(cars, header, pi + 1, high);
    }
}

void quickSortString(vector<Car>& cars, const string& header) {
    int n = cars.size();
    quickSortString(cars, header, 0, n - 1);
}

int findMinIndex(vector<Car>& cars, const string& header, int start) {
    int minIndex = start;
    int minValue;
    if (header == "YEAR") {
        minValue = cars[start].year;
    } else if (header == "MMR") {
        minValue = cars[start].mmr;
    } else if (header == "SELLINGPRICE") {
        minValue = cars[start].sellingPrice;
    } else if (header == "ODOMETER") {
        minValue = cars[start].odometer;
    } else if (header == "CONDITION") {
        minValue = cars[start].condition;
    } else if (header == "CONDITION_VALUE") {
        minValue = cars[start].condition_value;
    } else {
        cerr << "Invalid header for selection sort." << endl;
        return -1;
    }

    for (int i = start + 1; i < cars.size(); i++) {
        int currentValue;
        if (header == "YEAR") {
            currentValue = cars[i].year;
        } else if (header == "MMR") {
            currentValue = cars[i].mmr;
        } else if (header == "SELLINGPRICE") {
            currentValue = cars[i].sellingPrice;
        } else if (header == "ODOMETER") {
            currentValue = cars[i].odometer;
        } else if (header == "CONDITION") {
            currentValue = cars[i].condition;
        } else if (header == "CONDITION_VALUE") {
            currentValue = cars[i].condition_value;
        } else {
            cerr << "Invalid header for selection sort." << endl;
            return -1;
        }

        if (currentValue < minValue) {
            minIndex = i;
            minValue = currentValue;
        }
    }
    return minIndex;
}

void selectionSortInteger(vector<Car>& cars, const string& header) {
    for (int i = 0; i < cars.size() - 1; i++) {
        int minIndex = findMinIndex(cars, header, i);
        swap(cars[i], cars[minIndex]);
    }
}