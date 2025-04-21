#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "PatientObject.h"
using namespace std;

void merge(vector<Patient*>& P, int left, int mid, int right);
void mergeSort(vector<Patient*>& P, int left, int right);

#endif //MERGE_SORT_H
