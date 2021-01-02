#ifndef INFO_H417_GROUP_15_EXPERIMENT2_H
#define INFO_H417_GROUP_15_EXPERIMENT2_H

#include "Chrono.h"
#include <random>

class Experiment2 {
private:
    char *fileName;
public:
    explicit Experiment2() {};

    /**
     * Computes the sum of the lengths of the lines obtained by
     * reading randomly a file j times
     * @tparam InputClass : InputStream implementation used to read the lines
     * @param fileName : name of the file to bea read
     * @param j : number of iterations (number of random reads)
     * @param B
     * @return the sum of the lengths of all the lines that were read
     */
    template<class InputClass>
    int randjump(char *fName, int j, int B = 0) {
        int sum = 0;
        InputClass input(fName, B);
        input.open();
        FILE *file = input.getFile();
        fseek(file, 0, SEEK_END);
        int fileSize = ftell(file) * sizeof(char);
        rewind(file);
        int seed = 10;
        std::mt19937 generator(seed);
        std::uniform_int_distribution<> distribute(0, fileSize);
        int position;
        for (int iteration = 0; iteration < j; j++) {
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
