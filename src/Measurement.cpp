#include <string>
#include <vector>
#include "Measurement.h"
#include "Chrono.h"
#include "Experiments/Experiment1.h"
#include <iostream>
#include <InputStreams/InputStream1.h>
#include <Experiments/Experiment2.h>
#include <InputStreams/InputStream2.h>
#include <InputStreams/InputStream3.h>
#include <InputStreams/InputStream4.h>


using namespace std;

Measurement::Measurement() {
}

/**
 * Test function for the first experiment
 * @param fileName file on which we compute the length
 * @param nbRep number of times we repeat the process
 * @param B
 * @return object containing the file name, the length and
 * the average time of execution
 */
Measurement::data Measurement::getAverageTime(char *fileName, int nbRep, int B) {
    Chrono *chrono = new Chrono();
    Experiment1 *experiment = new Experiment1();
    double *times = new double[nbRep];
    int length = 0;
    for (int i = 0; i < nbRep; i++) {
        chrono->startChrono();
        length = experiment->length<InputStream1>(fileName, B);
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

/**
 * Computes the average tine of execution of the first experiment
 * for different B values
 * @param fileName
 * @param nbRep
 * @param minB
 * @param maxB
 * @param step
 * @return array of average lengths corresponding to each B value
 */
double *Measurement::getAverageTimesB(char *fileName, int nbRep, int minB, int maxB, int step) {
    double *averageTimes = (double *) malloc((maxB - minB + step) * sizeof(double));
    for (int i = minB; i < maxB + step; i += step) {
        averageTimes[i - minB] = getAverageTime(fileName, nbRep, i).time;
        cout << i << " " << averageTimes[i - minB] << endl;
    }
    free(averageTimes);
    return averageTimes;
}

/**
 * Tests the experiment 1 on all the files of the dataset
 * @param B
 * @return vector of objects containing each the length,
 * the file name and the average execution time
 */
vector<Measurement::data> Measurement::testFiles(int B) {
    vector<data> vec;
    char *fileNames[] = {"aka_name", "aka_title", "cast_info", "char_name", "comp_cast_type", "company_name",
                         "company_type", "complete_cast", "info_type", "keyword",
                         "kind_type", "link_type", "movie_companies", "movie_info", "movie_info_idx", "movie_keyword",
                         "movie_link", "name", "person_info", "role_type", "title"};

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

/**
 * Tests the experiment 2 on a given file a certain number of times
 * @param fileName
 * @param nbRep
 * @param B
 * @param iteration parameter J
 * @return object containing the sum, the file name and the average execution time
 */
Measurement::data Measurement::getAverageTimesJ(char *fileName, int nbRep, int B, int iteration) {
    Chrono *chrono = new Chrono();
    Experiment2 *experiment = new Experiment2();
    double *times = new double[nbRep];
    int length = 0;
    for (int i = 0; i < nbRep; i++) {
        chrono->startChrono();
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

/**
 * Computes the average time of execution of experiment 2 when varying B
 * @param fileName
 * @param nbRep
 * @param minB
 * @param maxB
 * @param step
 * @return array of average lengths corresponding to each B value
 */
double *Measurement::getAverageTimesB2(char *fileName, int nbRep, int minB, int maxB, int step) {
    double *averageTimes = (double *) malloc((((maxB - minB) / step) + 1) * sizeof(double));
    int *averageSums = (int *) malloc((((maxB - minB) / step) + 1) * sizeof(int));
    int counter = 0;
    for (int i = minB; i < maxB + step; i += step) {
        data x = getAverageTimesJ(fileName, nbRep, i, 10000);
        averageTimes[counter] = x.time;
        averageSums[counter] = x.length;
        cout << i << " " << averageTimes[counter] << " " << averageSums[counter] << endl;
        counter++;
    }
    free(averageTimes);
    free(averageSums);
    return averageTimes;
}

/**
 * Tests experiment 2 on several files
 * @param B
 * @return vector of objects containing each the sum,
 * the file name and the average execution time
 */
vector<Measurement::data> Measurement::testFiles2(int B) {
    vector<data> vec;
    char *fileNames[] = {"comp_cast_type", "aka_title", "aka_name", "cast_info", "keyword", "movie_info_idx"};

    for (int i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++) {
        char path[100];
        strcpy(path, "../data/");
        strcat(path, fileNames[i]);
        strcat(path, ".csv");
        data x;
        data y;
        x = getAverageTimesJ(path, 10, B, 10);
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
 * Tests experiment 2 with varying values of j (number of iterations)
 * @param fileName
 * @param nbRep
 * @param minJ
 * @param maxJ
 * @param step
 * @return
 */
vector<Measurement::data> Measurement::testIterations(char *fileName, int nbRep, int minJ, int maxJ, int step) {
    vector<data> vec;

    for (int i = minJ; i < maxJ + 1; i += step) {
        //cout << fileName << endl;
        data x;
        data y;
        x = getAverageTimesJ(fileName, nbRep, 65536, i); // B=100 for randjump3 B= 65536 for randjump4
        y.length = x.length;
        y.time = x.time;
        y.fileName = fileName;
        vec.push_back(y);
    }
    for (int i = 0; i < vec.size(); i++)
        cout << i + 1 << " " << vec.at(i).time << " " << vec.at(i).length << endl;
    return vec;
}