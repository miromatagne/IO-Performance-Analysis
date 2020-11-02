#include "Experiment1.h"

typedef void (*callback_function)(void); // type for conciseness

Experiment1::Experiment1() {
}

int Experiment1::length(char *fileName) {
    int sum = 0;
    InputStream inputStream(fileName);
    inputStream.open();
    char *line;
    line = inputStream.readln1();
    sum += strlen(line);
    int i = 0;
    while (i < 2) {
        line = function(inputStream);
        sum += strlen(line);
        i++;
    }
    inputStream.close();
    return sum;
}

char *readln1(InputStream inputStream) {
    return inputStream.readln1();
}

int Experiment1::length1(char *fileName) {
    function = readln1;
    return length(fileName);
}