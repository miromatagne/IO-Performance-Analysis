#ifndef INFO_H417_GROUP_15_MEASUREMENT_H
#define INFO_H417_GROUP_15_MEASUREMENT_H


#include <string>
#include <vector>

class Measurement {
private:
    struct data {
        char *fileName;
        int length;
        double time;
    };
public:
    Measurement();

    data getAverageTime(char *fileName, int nbRep, int B = 0);

    double *getAverageTimesB(char *fileName, int nbRep, int minB, int maxB);

    std::vector<data> Measurement::testFiles(int B = 0);
};


#endif //INFO_H417_GROUP_15_MEASUREMENT_H
