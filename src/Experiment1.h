#ifndef INFO_H417_GROUP_15_EXPERIMENT1_H
#define INFO_H417_GROUP_15_EXPERIMENT1_H


#include "InputStream.h"
#include "Chrono.h"

class Experiment1 {
private:
    char *fileName;

    char *(*function)(InputStream inputStream);

public:
    explicit Experiment1();

    void getDurations(char *fileName);

    int length(char *fileName);

    int length1(char *fileName);

    int length2(char *fileName);

    int length3(char *fileName);
};


#endif //INFO_H417_GROUP_15_EXPERIMENT1_H
