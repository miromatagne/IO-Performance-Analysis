#ifndef INFO_H417_GROUP_15_EXPERIMENT1_H
#define INFO_H417_GROUP_15_EXPERIMENT1_H

#include "Chrono.h"

class Experiment1 {
private:

public:
    explicit Experiment1() {};

    template<class InputClass>
    int length(char *fileName, int B = 0) {
        int sum = 0;
        InputClass input(fileName, B);
        input.open();
        std::string line;
        line = input.readln();
        sum += line.length();
        while (line != "") {
            line = input.readln();
            sum += line.length();
        }
        input.close();
        return sum;
    }
};


#endif //INFO_H417_GROUP_15_EXPERIMENT1_H
