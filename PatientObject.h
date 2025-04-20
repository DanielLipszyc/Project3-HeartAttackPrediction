#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#ifndef PROJECT3_HEARTATTACKPREDICTION_PATIENTOBJECT_H
#define PROJECT3_HEARTATTACKPREDICTION_PATIENTOBJECT_H


struct Patient{
    int BMI;
    int StressLevel;
    int HAO; // Heart Attack Outcome

    Patient(int BMI, int HAO, int stressLevel);


};


#endif //PROJECT3_HEARTATTACKPREDICTION_PATIENTOBJECT_H
