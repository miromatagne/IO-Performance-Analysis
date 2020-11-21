#include <iostream>
#include <cstring>
#include "Experiment1.h"


Experiment1::Experiment1() {
}

double *Experiment1::getDurations(char *fileName, int B) {
    double times[4];
    Chrono *chrono = new Chrono();
    chrono->startChrono();
    cout << "Length1: " << this->length1(fileName) << endl;
    times[0] = chrono->getChrono();
    cout << "Time: " << times[0] << endl;
    chrono->startChrono();
    cout << "Length2: " << this->length2(fileName) << endl;
    times[1] = chrono->getChrono();
    cout << "Time: " << times[1] << endl;
    chrono->startChrono();
    cout << "Length3: " << this->length3(fileName, B) << endl;
    times[2] = chrono->getChrono();
    cout << "Time: " << times[2] << endl;
    return times;
}

int Experiment1::length12(char *fileName) {
    int sum = 0;
    InputStream inputStream(fileName);
    inputStream.open();
    char *line;
    line = function12(inputStream);
    sum += strlen(line);
    while (line != nullptr) {
        line = function12(inputStream);
        if (line != nullptr) {
            sum += strlen(line);
        }
    }
    inputStream.close();
    return sum;
}

int Experiment1::length34(char *fileName, int B) {
    int sum = 0;
    InputStream inputStream(fileName);
    inputStream.open();
    char *line;
    line = function34(inputStream, B);
    sum += strlen(line);
    while (line != nullptr) {
        line = function34(inputStream, B);
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
    function12 = readln1;
    return length12(fileName);
}

char *readln2(InputStream inputStream) {
    return inputStream.readln2();
}

int Experiment1::length2(char *fileName) {
    function12 = readln2;
    return length12(fileName);
}

char *readln3(InputStream inputStream, int B) {
    return inputStream.readln3(B);
}

int Experiment1::length3(char *fileName, int B) {
    function34 = readln3;
    return length34(fileName, B);
}