//
// Created by Daniel Lipszyc on 4/20/25.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "MergeSort.h"

using namespace std;

void extractBMIsFromFile(vector<Patient*> &list) {
    ifstream file("../heart_attack_dataset.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file 'ONE'." << endl;
        return;
    }
    string line;
    getline(file, line); // skip header
    int count = 0;
    while (getline(file, line)) {
        size_t start = 0;
        size_t end = 0;
        int index = 0;
        float bmi = 0;
        int stressLevel = 0;
        int outcome = 0;
        string token;

        while (end != string::npos && index <= 31) {
            end = line.find(',', start);
            token = line.substr(start, end - start);

            if (index == 5) {
                bmi = stof(token);
            }

            else if(index == 13){
                stressLevel = stoi(token);
            }

            else if (index == 31) {
                outcome = (token == "Heart Attack") ? 1 : 0;
                break;
            }

            start = end + 1;
            ++index;
        }

        Patient* P = new Patient(bmi, outcome, stressLevel);
        list.push_back(P);

        ++index;
        count++;
    }
    file.close();
}

int main(){
    return 0;
}