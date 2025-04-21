#include "RadixSort.h"

using namespace std;

int getMax(vector<Patient*>& P) {
    int max = P[0]->BMI;
    for (int i = 1; i < P.size(); i++){
        if (P[i]->BMI > max){
            max = P[i]->BMI;
        }
    }
    return max;
}

void countingSort(vector<Patient*>& P, int exp){
    int n = P.size();
    vector<Patient*> output(n);
    vector<int> count(10, 0);

    for (const auto& p : P)
        count[(p->BMI / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int index = (P[i]->BMI / exp) % 10;
        output[count[index] - 1] = P[i];
        count[index]--;
    }

    P = output;
}

void radixSort(vector<Patient*>& P) {
    int maxBMI = getMax(P);
    for (int exp = 1; maxBMI / exp > 0; exp *= 10)
        countingSort(P, exp);
}
