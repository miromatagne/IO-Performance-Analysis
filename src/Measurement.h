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

    data getAverageTime(char *fileName, int nbRep, int B = 0, int iteration = 0);

    double *getAverageTimesB(char *fileName, int nbRep, int minB, int maxB, int step);

    double *getAverageTimesJ(char *fileName, int nbRep, int minJ, int maxJ, int step);

    std::vector<data> testFiles(int B = 0);

    std::vector<data> testIterations(char *fileName, int nbRep, int minJ, int maxJ, int step);

};


#endif //INFO_H417_GROUP_15_MEASUREMENT_H
