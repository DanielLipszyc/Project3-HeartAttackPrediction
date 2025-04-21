#ifndef RADIXSORT_H
#define RADIXSORT_H

#include "PatientObject.h"
#include <vector>
using namespace std;

int getMax(vector<Patient*> P);
void countingSort(vector<Patient*>& P, int exp);
void radixSort(vector<Patient*>& P);

#endif //RADIXSORT_H
