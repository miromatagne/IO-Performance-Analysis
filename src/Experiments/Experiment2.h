//
// Created by trann on 02/12/2020.
//
#ifndef INFO_H417_GROUP_15_EXPERIMENT2_H
#define INFO_H417_GROUP_15_EXPERIMENT2_H

#include "Chrono.h"

class Experiment2 {
private:
    char *fileName;

public:
    explicit Experiment2();

    int randjump1(char *fileName, int iteration);

    int randjump2(char *fileName, int iteration);

    int randjump3(char *fileName, int iteration, int B);

    int randjump4(char *fileName, int iteration, int B);
};


#endif //INFO_H417_GROUP_15_EXPERIMENT2_H
