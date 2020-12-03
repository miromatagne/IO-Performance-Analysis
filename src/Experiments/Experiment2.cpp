//
// Created by trann on 02/12/2020.
//
#include <InputStreams/InputStream.h>
#include <InputStreams/InputStream1.h>
#include <InputStreams/InputStream2.h>
#include <InputStreams/InputStream3.h>
#include <InputStreams/InputStream4.h>
#include <iostream>
#include <random>
#include <ctime>

#include "Experiment2.h"

using namespace std;

Experiment2::Experiment2() {

}

int Experiment2::randjump1(char *fileName, int iteration) {
    int sum = 0;
    InputStream1 inputStream1(fileName);
    inputStream1.open();
    FILE *file = inputStream1.getFile();
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file) * sizeof(char);
    rewind(file);
    fseek(file, 0, SEEK_SET);
    cout << "size : " << fileSize << endl;
    //std::random_device os_seed;
    //std::mt19937 generator(os_seed());
    //std::uniform_int_distribution<> distribute( 0, fileSize);

    srand(time(NULL));
    int position;
    for (int j = 0; j < iteration; j++) {
        //int position = distribute( generator);
        position = (rand() % fileSize);
        inputStream1.seek(position);
        string line;
        line = inputStream1.readln();
        sum += line.length();
        cout << "pos : " << position << endl;
        cout << "line : " << line << endl;
    };
    inputStream1.close();
    return sum;
}

int Experiment2::randjump2(char *fileName, int iteration) {
    int sum = 0;
    InputStream2 inputStream2(fileName);
    inputStream2.open();
    FILE *file = inputStream2.getFile();
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file) * sizeof(char);
    rewind(file);
    fseek(file, 0, SEEK_SET);

    srand(time(NULL));
    int position;
    for (int j = 0; j < iteration; j++) {
        position = (rand() % fileSize);
        inputStream2.seek(position);
        string line;
        line = inputStream2.readln();
        sum += line.length();
        cout << "pos : " << position << endl;
        cout << "line : " << line << endl;
    };
    inputStream2.close();
    return sum;
}

int Experiment2::randjump3(char *fileName, int iteration, int B) {
    int sum = 0;
    InputStream3 inputStream3(fileName, B);
    inputStream3.open();
    FILE *file = inputStream3.getFile();
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file) * sizeof(char);
    rewind(file);
    fseek(file, 0, SEEK_SET);

    srand(time(NULL));
    int position;
    for (int j = 0; j < iteration; j++) {
        position = (rand() % fileSize);
        inputStream3.seek(position);
        string line;
        line = inputStream3.readln();
        sum += line.length();
        cout << "pos : " << position << endl;
        cout << "line : " << line << endl;
    };
    inputStream3.close();
    return sum;
}

/*int Experiment2::randjump4(char *fileName, int iteration, int B) {
    int sum = 0;
    InputStream4 inputStream4(fileName, B);
    inputStream4.open();
    FILE *file = inputStream4.getFile();
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file) * sizeof(char);
    rewind(file);
    fseek(file, 0, SEEK_SET);

    srand(time(NULL));
    int position;
    for (int j = 0; j < iteration; j++) {
        position = (rand() % fileSize);
        inputStream4.seek(position);
        string line;
        line = inputStream4.readln();
        sum += line.length();
    };
    inputStream4.close();
    return sum;
}*/