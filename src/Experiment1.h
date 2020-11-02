#ifndef INFO_H417_GROUP_15_EXPERIMENT1_H
#define INFO_H417_GROUP_15_EXPERIMENT1_H


#include "InputStream.h"

class Experiment1 {
private:
    char *fileName;

    char *(*function)(InputStream inputStream);

public:
    explicit Experiment1();

    int length(char *fileName);

    int length1(char *fileName);
};


#endif //INFO_H417_GROUP_15_EXPERIMENT1_H
