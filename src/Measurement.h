#ifndef INFO_H417_GROUP_15_MEASUREMENT_H
#define INFO_H417_GROUP_15_MEASUREMENT_H


#include <string>

class Measurement {
private:
public:
    Measurement();

    double getAverageTime(char *fileName, int nbRep, int B = 0);

    double *getAverageTimesB(char *fileName, int nbRep, int minB, int maxB);
};


#endif //INFO_H417_GROUP_15_MEASUREMENT_H
