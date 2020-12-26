//
// Created by Miro-Manuel on 22/11/2020.
//

#include <string>
#include <vector>
#include "Measurement.h"
#include "Chrono.h"
#include "Experiments/Experiment1.h"
#include "MultiwayMerge.h"
#include <iostream>
#include <InputStreams/InputStream1.h>
#include <Experiments/Experiment2.h>
#include <InputStreams/InputStream2.h>
#include <InputStreams/InputStream3.h>
#include <InputStreams/InputStream4.h>


using namespace std;

Measurement::Measurement() {
}

Measurement::data Measurement::getAverageTime(char *fileName, int nbRep, int B, int iteration) {
    Chrono *chrono = new Chrono();
    //Experiment1 *experiment = new Experiment1();
    Experiment2 *experiment = new Experiment2();
    double *times = new double[nbRep];
    int length = 0;
    for (int i = 0; i < nbRep; i++) {
        chrono->startChrono();
        //length = experiment->length<InputStream1>(fileName, B);
        //length = experiment->randjump<InputStream1>(fileName, iteration, B);
        //length = experiment->randjump<InputStream2>(fileName, iteration, B);
        //length = experiment->randjump<InputStream3>(fileName, iteration, B);
        length = experiment->randjump<InputStream4>(fileName, iteration, B);
        times[i] = chrono->getChrono();
    }
    double sum = 0;
    for (int i = 0; i < nbRep; i++) {
        sum += times[i];
    }
    double average = sum / nbRep;
    free(times);
    free(experiment);
    free(chrono);
    data x;
    x.time = average;
    x.fileName = fileName;
    x.length = length;
    return x;
}

double *Measurement::getAverageTimesB(char *fileName, int nbRep, long minB, long maxB, int step) {
    double *averageTimes = new double[maxB - minB + step];
    double *averageSums = new double[maxB - minB + step];
    for (long i = minB; i < maxB + step; i += step) {
        data x = getAverageTime(fileName, nbRep, i, 10000);
        averageTimes[i - minB] = x.time;
        averageSums[i - minB] = x.length;
        cout << i << " " << averageTimes[i - minB] << " " << averageSums[i - minB] << endl;
    }
    return averageTimes;
}

vector<Measurement::data> Measurement::testFiles(int B) {
    vector<data> vec;
    /*char *fileNames[] = {"aka_name" , "aka_title" , "cast_info", "char_name", "comp_cast_type", "company_name",
                         "company_type", "complete_cast", "info_type", "keyword",
                         "kind_type", "link_type", "movie_companies", "movie_info", "movie_info_idx", "movie_keyword",
                         "movie_link", "name", "person_info", "role_type", "title"};
    */
    char *fileNames[] = {"cast_info", "comp_cast_type", "keyword", "movie_info_idx"};
    for (int i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++) {
        char path[100];
        cout << fileNames[i] << endl;
        strcpy(path, "../data/");
        strcat(path, fileNames[i]);
        strcat(path, ".csv");
        data x;
        data y;
        x = getAverageTime(path, 10, B, 10);
        y.length = x.length;
        y.time = x.time;
        y.fileName = fileNames[i];
        vec.push_back(y);
    }
    for (int i = 0; i < vec.size(); i++)
        cout << vec.at(i).fileName << " " << vec.at(i).time << " " << vec.at(i).length << endl;
    return vec;
}

/**
 * Iteration J
 */
vector<Measurement::data> Measurement::testIterations(char *fileName, int nbRep, int minJ, int maxJ, int step) {
    vector<data> vec;

    for (int i = minJ; i < maxJ + 1; i += step) {
        //cout << fileName << endl;
        data x;
        data y;
        x = getAverageTime(fileName, nbRep, 5000 * 65536, i); // B=100 for randjump3 B= 65536 for randjump4
        y.length = x.length;
        y.time = x.time;
        y.fileName = fileName;
        vec.push_back(y);
    }
    for (int i = 0; i < vec.size(); i++)
        cout << i + 1 << " " << vec.at(i).time << " " << vec.at(i).length << endl;
    return vec;
}

void Measurement::testMergeM(char *fileName, int k, int minM, int maxM, int step, int d) {
    for (int i = minM; i < maxM + 1; i += step) {
        double x = getAverageMergeTime(fileName, 1, k, i, d);
        cout << i << " " << x << endl;
    }
}

double Measurement::getAverageMergeTime(char *fileName, int nbRep, int k, int M, int d) {
    Chrono *chrono = new Chrono();
    MultiwayMerge m;
    double *times = new double[nbRep];
    int length = 0;
    for (int i = 0; i < nbRep; i++) {
        chrono->startChrono();
        //cout << "start" << endl;
        m.extsort(fileName, k, M, d);
        times[i] = chrono->getChrono();
    }
    double sum = 0;
    for (int i = 0; i < nbRep; i++) {
        sum += times[i];
    }
    double average = sum / nbRep;
    free(times);
    free(chrono);
    return average;
}
