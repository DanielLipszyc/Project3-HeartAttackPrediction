#include "RadixSort.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int getMax(vector<Patient*> P) {
    int max = P[0]->BMI;
    for (int i = 1; i < P.size(); i++){
        if (P[i]->BMI > max){
            max = P[i]->BMI;
        }
    }
    return max;
}

void countingSort(vector<Patient*>& patients, int exp) {
    int n = patients.size();
    vector<Patient*> output(n);
    vector<int> count(10, 0);

    for (const auto& p : patients)
        count[(p->BMI / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int index = (patients[i]->BMI / exp) % 10;
        output[count[index] - 1] = patients[i];
        count[index]--;
    }

    patients = output;
}

void radixSort(vector<Patient*>& patients) {
    int maxBMI = getMax(patients);
    for (int exp = 1; maxBMI / exp > 0; exp *= 10)
        countingSort(patients, exp);
}
