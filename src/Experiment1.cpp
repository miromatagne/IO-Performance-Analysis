#include <iostream>
#include <cstring>
#include "Experiment1.h"

Experiment1::Experiment1() {
}

int Experiment1::length(char *fileName) {
    int sum = 0;
    InputStream inputStream(fileName);
    inputStream.open();
    char *line;
    line = function(inputStream);
    sum += strlen(line);
    while (line != nullptr) {
        line = function(inputStream);
        if (line != nullptr) {
            sum += strlen(line);
        }
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

char *readln2(InputStream inputStream) {
    return inputStream.readln2();
}

int Experiment1::length2(char *fileName) {
    function = readln2;
    return length(fileName);
}

char *readln3(InputStream inputStream) {
    return inputStream.readln3();
}

int Experiment1::length3(char *fileName) {
    function = readln3;
    return length(fileName);
}