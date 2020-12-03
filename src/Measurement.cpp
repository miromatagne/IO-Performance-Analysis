//
// Created by Miro-Manuel on 22/11/2020.
//

#include <string>
#include <vector>
#include "Measurement.h"
#include "Chrono.h"
#include "Experiments/Experiment1.h"
#include <iostream>

using namespace std;

Measurement::Measurement() {
}

Measurement::data Measurement::getAverageTime(char *fileName, int nbRep, int B) {
    Chrono *chrono = new Chrono();
    Experiment1 *experiment = new Experiment1();
    double *times = new double[nbRep];
    int length = 0;
    for (int i = 0; i < nbRep; i++) {
        chrono->startChrono();
        length = experiment->length2(fileName);
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

double *Measurement::getAverageTimesB(char *fileName, int nbRep, int minB, int maxB) {
    double *averageTimes = (double *) malloc((maxB - minB) * sizeof(double));
    for (int i = minB; i < maxB + 1; i++) {
        averageTimes[i - minB] = getAverageTime(fileName, nbRep, i).time;
    }
    return averageTimes;
}

vector<Measurement::data> Measurement::testFiles(int B) {
    vector<data> vec;
    char *fileNames[] = {"aka_name", "aka_title", "cast_info", "char_name", "comp_cast_type", "company_name",
                         "company_type", "complete_cast", "info_type", "keyword", "kind_type", "link_type",
                         "movie_companies", "movie_info", "movie_info_idx", "movie_keyword", "movie_link", "name",
                         "person_info", "role_type", "title"};
    for (int i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++) {
        char path[100];
        cout << fileNames[i] << endl;
        strcpy(path, "../data/");
        strcat(path, fileNames[i]);
        strcat(path, ".csv");
        data x;
        data y;
        x = getAverageTime(path, 10, B);
        y.length = x.length;
        y.time = x.time;
        y.fileName = fileNames[i];
        vec.push_back(y);
    }
    for (int i = 0; i < vec.size(); i++)
        cout << vec.at(i).fileName << " " << vec.at(i).time << " " << vec.at(i).length << endl;
    return vec;
}
