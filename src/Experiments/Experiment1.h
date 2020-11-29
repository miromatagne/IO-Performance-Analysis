#ifndef INFO_H417_GROUP_15_EXPERIMENT1_H
#define INFO_H417_GROUP_15_EXPERIMENT1_H

#include "Chrono.h"

class Experiment1 {
private:
    char *fileName;

    char *(*function12)(InputStream inputStream);

    char *(*function34)(InputStream inputStream, int B);

public:
    explicit Experiment1();

    double *getDurations(char *fileName, int B);

    int length12(char *fileName);

    int length34(char *fileName, int B);

    int length1(char *fileName);

    int length2(char *fileName);

    int length3(char *fileName, int B);
};


#endif //INFO_H417_GROUP_15_EXPERIMENT1_H
