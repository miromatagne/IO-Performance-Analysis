#ifndef INFO_H417_GROUP_15_EXPERIMENT1_H
#define INFO_H417_GROUP_15_EXPERIMENT1_H

#include "Chrono.h"

class Experiment1 {
private:
    char *fileName;


public:
    explicit Experiment1();

    double *getDurations(char *fileName, int B);

    int length1(char *fileName);

    int length2(char *fileName);

    int length3(char *fileName, int B);
};


#endif //INFO_H417_GROUP_15_EXPERIMENT1_H
