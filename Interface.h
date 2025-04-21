#ifndef INTERFACE_H
#define INTERFACE_H

using namespace std;
#include <vector>
#include "PatientObject.h"


class InterfaceUI {
public:
    vector<Patient*> patients;
    void SFMLInterface();
    void ExtractBMIsFromFile();
    string MergeSortMethod();
    string RadixSortMethod();
};


#endif //INTERFACE_H
