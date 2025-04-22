#include <vector>
#include "MergeSort.h"
using namespace std;

///Use our own knowledge and online resources
void merge(std::vector<Patient*>& P, int left, int mid, int right) {
    int indexLeft = mid - left + 1;
    int indexRight = right - mid;
    vector<Patient*> Left(indexLeft);
    vector<Patient*> Right(indexRight);

    for (int i = 0; i < indexLeft; i++)
        Left[i] = P[left + i];
    for (int j = 0; j < indexRight; j++)
        Right[j] = P[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < indexLeft && j < indexRight) {
        if (Left[i]->BMI <= Right[j]->BMI) {
            P[k] = Left[i];
            i++;
        } else {
            P[k] = Right[j];
            j++;
        }
        k++;
    }

    while (i < indexLeft) {
        P[k] = Left[i];
        i++;
        k++;
    }

    while (j < indexRight) {
        P[k] = Right[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<Patient*>& P, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(P, left, mid);
        mergeSort(P, mid + 1, right);
        merge(P, left, mid, right);
    }
}