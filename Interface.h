#ifndef INTERFACE_H
#define INTERFACE_H

using namespace std;
#include <vector>
#include "PatientObject.h"


class InterfaceUI {
private:
    double GetAverageScore(int filter);
public:
    vector<Patient*> patients;
    void SFMLInterface();
    void ExtractBMIsFromFile();
    pair<string, string> MergeSortMethod(int filterValue);
    pair<string, string> RadixSortMethod(int filterValue);
};


#endif //INTERFACE_H
