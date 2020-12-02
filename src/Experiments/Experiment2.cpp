//
// Created by trann on 02/12/2020.
//
#include <InputStreams/InputStream.h>
#include <InputStreams/InputStream1.h>
#include <InputStreams/InputStream2.h>
#include <InputStreams/InputStream3.h>
#include <iostream>
#include <random>

#include "Experiment2.h"

using namespace std;

Experiment2::Experiment2() {

}

int Experiment2::randjump1(char *fileName, int iteration) {
    int sum = 0;
    InputStream1 inputStream1(fileName);
    inputStream1.open();

    int fileSize = inputStream1.sizeFile();
    using u32    = uint_least32_t;
    using engine = std::mt19937;
    //std::random_device os_seed;
    const u32 seed = 4; //os_seed();
    engine generator(seed);
    std::uniform_int_distribution< u32 > distribute( 0, fileSize);

    for (int j = 0; j < iteration; j++) {
        int position = distribute( generator);
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