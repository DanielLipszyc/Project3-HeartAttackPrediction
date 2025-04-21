#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <vector>
#include "PatientObject.h"
using namespace std;

int getMax(vector<Patient*>& P);
void countingSort(vector<Patient*>& P, int exp);
void radixSort(vector<Patient*>& P);

#endif //RADIX_SORT_H
