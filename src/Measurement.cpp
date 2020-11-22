//
// Created by Miro-Manuel on 22/11/2020.
//

#include <string>
#include "Measurement.h"
#include "Chrono.h"
#include "Experiment1.h"

using namespace std;

Measurement::Measurement() {
}

double Measurement::getAverageTime(char *fileName, int nbRep, int B) {
    Chrono *chrono = new Chrono();
    Experiment1 *experiment = new Experiment1();
    double *times = (double *) malloc(nbRep * sizeof(double));
    for (int i = 0; i < nbRep; i++) {
        chrono->startChrono();
        experiment->length1(fileName);
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
    return average;
}

double *Measurement::getAverageTimesB(char *fileName, int nbRep, int minB, int maxB) {
    double *averageTimes = (double *) malloc((maxB - minB) * sizeof(double));
    for (int i = minB; i < maxB + 1; i++) {
        averageTimes[i - minB] = getAverageTime(fileName, nbRep, i);
    }
    return averageTimes;
}
