#ifndef INFO_H417_GROUP_15_EXPERIMENT2_H
#define INFO_H417_GROUP_15_EXPERIMENT2_H

#include "Chrono.h"
#include <random>

class Experiment2 {
private:
    char *fileName;
public:
    explicit Experiment2(){};

    template<class InputClass>
    int randjump(char *fileName, int iteration, int B = 0) {
        int sum = 0;
        InputClass input(fileName, B);
        input.open();
        FILE *file = input.getFile();
        fseek(file, 0, SEEK_END);
        int fileSize = ftell(file) * sizeof(char);
        rewind(file);
        int seed = 10;
        std::mt19937 generator(seed);
        std::uniform_int_distribution<> distribute(0, fileSize);
        int position;
        for (int j = 0; j < iteration; j++) {
            position = distribute(generator);
            input.seek(position);
            string line;
            line = input.readln();
            sum += line.length();
        }
        input.close();
        return sum;
    }
};


#endif //INFO_H417_GROUP_15_EXPERIMENT2_H
