//
// Created by Miro-Manuel on 22/11/2020.
//

#include <string>
#include <vector>
#include "Measurement.h"
#include "Chrono.h"
#include "Experiments/Experiment1.h"
#include <iostream>
#include <InputStreams/InputStream1.h>
#include <InputStreams/InputStream2.h>
#include <InputStreams/InputStream3.h>
#include <InputStreams/InputStream4.h>

#include <OutputStreams/OutputStream1.h>
#include <OutputStreams/OutputStream2.h>
#include <OutputStreams/OutputStream3.h>
#include <OutputStreams/OutputStream4.h>
#include <Experiments/Experiment2.h>
#include <Experiments/Experiment3.h>


using namespace std;

Measurement::Measurement() {
}

Measurement::data Measurement::getAverageTime(char *fileName, int nbRep, int B, int iteration) {
    Chrono *chrono = new Chrono();
    //Experiment1 *experiment = new Experiment1();
    //Experiment2 *experiment = new Experiment2();

    double *times = new double[nbRep];
    int length = 0;
    for (int i = 0; i < nbRep; i++) {
        chrono->startChrono();
        // refaire exactement la meme chose mais avec inputstream4 et outputstream 2,3,4
        // choisir le Bi optimal de l'experience 1 et 2
        // faire varier Bo pour ouputstream 3 et 4
        // 15 runs si le time pour les bigs files ( 4) et 5) ) sauf pour outputstream1 : 2 ou 3 runs déjà très long
//    k medium, size small
// 0)  experiment3.rrmerge<InputStream2,OutputStream1>(100, B, "../data/link_type.csv","../data/kind_type.csv","../data/info_type.csv", "../data/company_type.csv","../data/comp_cast_type.csv","../data/role_type.csv","../data/movie_link.csv",NULL);
//    k small, size medium
// 1)    experiment3.rrmerge<InputStream2,OutputStream1>(100, B, "../data/complete_cast.csv", "../data/keyword.csv", NULL);
//    k medium, size medium
// 2)  experiment3.rrmerge<InputStream2,OutputStream1>(100, B, "../data/complete_cast.csv", "../data/keyword.csv","../data/company_name.csv","../data/movie_info_idx.csv","../data/movie_keyword.csv","../data/movie_companies.csv","../data/aka_title.csv","../data/aka_name.csv",NULL);
//    k big, size small + medium
// 3)  experiment3.rrmerge<InputStream2,OutputStream1>(100, B, "../data/complete_cast.csv", "../data/keyword.csv","../data/movie_link.csv","../data/company_name.csv","../data/movie_info_idx.csv","../data/link_type.csv","../data/kind_type.csv","../data/info_type.csv", "../data/company_type.csv","../data/comp_cast_type.csv","../data/role_type.csv","../data/movie_keyword.csv", "../data/movie_companies.csv","../data/aka_title.csv","../data/aka_name.csv",NULL);
//    k medium, size big
//   experiment3.rrmerge<InputStream2,OutputStream4>(100, B, "../data/movie_info.csv", "../data/person_info.csv","../data/name.csv","../data/cast_info.csv","../data/title.csv", NULL);
//    all in : k maximum, size small + big + medium
// 5)   experiment3.rrmerge<InputStream2,OutputStream1>(100, B, "../data/title.csv","../data/link_type.csv","../data/kind_type.csv","../data/info_type.csv", "../data/company_type.csv","../data/comp_cast_type.csv","../data/role_type.csv", "../data/complete_cast.csv", "../data/keyword.csv","../data/movie_link.csv","../data/company_name.csv","../data/movie_info_idx.csv","../data/movie_keyword.csv","../data/movie_companies.csv","../data/aka_title.csv","../data/aka_name.csv","../data/movie_info.csv", "../data/person_info.csv","../data/name.csv","../data/cast_info.csv",NULL);



//    k =1 , size small
// 6)       experiment3.rrmerge<InputStream2,OutputStream1>(100,B, "../data/complete_cast.csv",NULL);
//    k =1 , size medium
// 7)       experiment3.rrmerge<InputStream2,OutputStream1>(100, B, "../data/company_name.csv",NULL);
//     k =1 , size big
// 8)       experiment3.rrmerge<InputStream2,OutputStream1>(100, B, "../data/cast_info.csv",NULL);

        //length = experiment->length<InputStream1>(fileName, B);
        //length = experiment->randjump<InputStream1>(fileName, iteration, B);
        //length = experiment->randjump<InputStream2>(fileName, iteration, B);
        //length = experiment->randjump<InputStream3>(fileName, iteration, B);
        //length = experiment->randjump<InputStream4>(fileName, iteration, B);
        times[i] = chrono->getChrono();
    }
    double sum = 0;
    for (int i = 0; i < nbRep; i++) {
        sum += times[i];
    }
    double average = sum / nbRep;
    free(times);
   // free(experiment);
    free(chrono);
    data x;
    x.time = average;
    x.fileName = fileName;
    x.length = length;
    return x;
}





double *Measurement::getAverageTimesB(char *fileName, int nbRep, int minB, int maxB, int step) {
    double *averageTimes = (double *) malloc((maxB - minB) * sizeof(double));
    for (int i = minB; i < maxB + 1; i += step) {
        averageTimes[i - minB] = getAverageTime(fileName, nbRep, i, 1).time;
        cout << i << " " << averageTimes[i - minB] << endl;
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
    char *fileNames[] = {"aka_name" , "cast_info", "comp_cast_type", "keyword"};
    for (int i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++) {
        char path[100];
        cout << fileNames[i] << endl;
        strcpy(path, "../data/");
        strcat(path, fileNames[i]);
        strcat(path, ".csv");
        data x;
        data y;
        cout << "ok" << endl;
        x = getAverageTime(path, 10, B, 1); // J = 10
        y.length = x.length;
        y.time = x.time;
        y.fileName = fileNames[i];
        vec.push_back(y);
        cout << "ok" << endl;
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
        x = getAverageTime(fileName, nbRep, 100, i); // B= 65536 for randjump4
        y.length = x.length;
        y.time = x.time;
        y.fileName = fileName;
        vec.push_back(y);
    }
    for (int i = 0; i < vec.size(); i++)
        cout << vec.at(i).fileName << " " << vec.at(i).time << " " << vec.at(i).length << endl;
    return vec;
}
