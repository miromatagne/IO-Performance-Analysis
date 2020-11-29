#include <iostream>
#include <cstring>
#include <InputStreams/InputStream1.h>
#include <InputStreams/InputStream2.h>
#include <InputStreams/InputStream3.h>
#include "Experiment1.h"


Experiment1::Experiment1() {
}

int Experiment1::length1(char *fileName) {
    int sum = 0;
    InputStream1 inputStream1(fileName);
    inputStream1.open();
    string line;
    line = inputStream1.readln();
    sum += line.length();
    while (line != "") {
        line = inputStream1.readln();
        if (line != "") {
            sum += line.length();
        }
    }
    inputStream1.close();
    return sum;
}

int Experiment1::length2(char *fileName) {
    int sum = 0;
    InputStream2 inputStream2(fileName);
    inputStream2.open();
    string line;
    line = inputStream2.readln();
    sum += line.length();
    while (line != "") {
        line = inputStream2.readln();
        if (line != "") {
            sum += line.length();
        }
    }
    inputStream2.close();
    return sum;
}
/*
char *readln3(InputStream inputStream, int B) {
    return inputStream.readln3(B);
}
*/
int Experiment1::length3(char *fileName, int B) {
    int sum = 0;
    InputStream3 inputStream3(fileName, B);
    inputStream3.open();
    string line;
    line = inputStream3.readln();
    sum += line.length();
    while (line != "") {
        line = inputStream3.readln();
        if (line != "") {
            sum += line.length();
        }
    }
    inputStream3.close();
    return sum;
}

double *Experiment1::getDurations(char *fileName, int B) {
    double times[4];
    Chrono *chrono = new Chrono();
    chrono->startChrono();
    cout << "Length1: " << this->length1(fileName) << endl;
    times[0] = chrono->getChrono();
//    cout << "Time: " << times[0] << endl;
    chrono->startChrono();
    cout << "Length2: " << this->length2(fileName) << endl;
    times[1] = chrono->getChrono();
//    cout << "Time: " << times[1] << endl;
    chrono->startChrono();
    cout << "Length3: " << this->length3(fileName, B) << endl;
    times[2] = chrono->getChrono();
//    cout << "Time: " << times[2] << endl;
    return times;
}