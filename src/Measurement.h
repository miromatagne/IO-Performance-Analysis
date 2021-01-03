#ifndef INFO_H417_GROUP_15_MEASUREMENT_H
#define INFO_H417_GROUP_15_MEASUREMENT_H


#include <string>
#include <vector>
# include "InputStreams/InputStream.h"
# include "InputStreams/InputStream1.h"
# include "InputStreams/InputStream2.h"
# include "InputStreams/InputStream3.h"
# include "InputStreams/InputStream4.h"
# include "OutputStreams/OutputStream.h"
# include "OutputStreams/OutputStream1.h"
# include "OutputStreams/OutputStream2.h"
# include "OutputStreams/OutputStream3.h"
# include "OutputStreams/OutputStream4.h"
#include <Experiments/Experiment3.h>
#include "Chrono.h"
#include <iostream>
#include <cmath>

class Measurement {
private:
    struct data {
        char *fileName;
        int length;
        double time;
    };
public:
    Measurement();

    data getAverageTime(char *fileName, int nbRep, int B = 0);

    //data getAverageTime3(int nbRep, int B, InputStream inputStream, OutputStream outputStream);

    double *getAverageTimesB(char *fileName, int nbRep, int minB, int maxB, int step);

    double *getAverageTimesB2(char *fileName, int nbRep, int minB, int maxB, int step);

    data getAverageTimesJ(char *fileName, int nbRep, int B = 0, int iteration = 0);

    std::vector<data> testFiles(int B = 0);

    std::vector<data> testFiles2(int B = 0);

    std::vector<data> testIterations(char *fileName, int nbRep, int minJ, int maxJ, int step);
/**
 * Tests experiment 3 on several set of files
 * @param nbRep
 * @param submeasurement different set of files depending on the submeasurement parameter
 * @param minB minimum size buffer
 * @param maxB maximum size buffer
 * @param step value used to increase the size of the buffer
 */
    template<class InputClass, class OutputClass>
    void getAverageTime3(int nbRep,int submeasurement ,int minB, int maxB, int step) {
        Experiment3 experiment3;
        Chrono *chrono = new Chrono();
        int B =minB;
        double times=0;
        double *timesB = new double[((maxB-minB)/step)+1];
        string filenames = "";
        int k =0;
        for (int i = 0; i <(maxB-minB)/step+1; i++) {
            timesB[i]=0;
        }
        bool needBuffer = (std::is_same<OutputClass, OutputStream3>::value) || (std::is_same<OutputClass, OutputStream4>::value);
        for (int i = 0; i < nbRep; i++) {
            int j=0;
            //    k = 2, size small
            if(submeasurement==1) {
                do {
                    chrono->startChrono();

                    experiment3.rrmerge<InputClass, OutputClass>(B, "../data/link_type.csv", "../data/kind_type.csv",
                                                                 NULL);
                    timesB[j] += chrono->getChrono();
                    j++;
                    B+=step;
                }while ((needBuffer) && B<maxB+1);
                filenames = " link_type,kind_type ";
                k = 2;
            }
            //    k = 7, size small
            else if(submeasurement==2) {
                do {
                    chrono->startChrono();
                    experiment3.rrmerge<InputClass, OutputClass>(B, "../data/link_type.csv", "../data/kind_type.csv",
                                                                 "../data/info_type.csv", "../data/company_type.csv",
                                                                 "../data/comp_cast_type.csv", "../data/role_type.csv",
                                                                 "../data/movie_link.csv", NULL);
                    timesB[j] += chrono->getChrono();
                    j++;
                    B+=step;
                }while ((needBuffer) && B<maxB+1);
                filenames = " link_type,kind_type,info_type,company_type,comp_cast_type,role_type,movie_link ";
                k = 7;
            }

            //    k = 2, size medium
            else if(submeasurement==3){
                do {
                    chrono->startChrono();
                    experiment3.rrmerge<InputClass, OutputClass>(B, "../data/complete_cast.csv", "../data/keyword.csv",
                                                                 NULL);
                    timesB[j] += chrono->getChrono();
                    j++;
                    B+=step;
                }while ((needBuffer) && B<maxB+1);
                filenames = " complete_cast,keyword ";
                k=2;
            }
            //    k =7, size medium
            else if(submeasurement==4) {
                do {
                    chrono->startChrono();
                    experiment3.rrmerge<InputClass, OutputClass>(B, "../data/keyword.csv",
                                                                 "../data/company_name.csv", "../data/movie_info_idx.csv",
                                                                 "../data/movie_keyword.csv", "../data/movie_companies.csv",
                                                                 "../data/aka_title.csv", "../data/aka_name.csv", NULL);
                    timesB[j] += chrono->getChrono();
                    j++;
                    B+=step;
                }while ((needBuffer) && B<maxB+1);
                filenames = " keyword,company_name,movie_info_idx,movie_keyword,movie_companies,aka_title,aka_name ";
                k=7;

            }
             //    k = 15, size small + medium
            else if(submeasurement==5) {
                do {
                    chrono->startChrono();
                    experiment3.rrmerge<InputClass, OutputClass>(B, "../data/complete_cast.csv", "../data/keyword.csv",
                                                                 "../data/movie_link.csv", "../data/company_name.csv",
                                                                 "../data/movie_info_idx.csv", "../data/link_type.csv",
                                                                 "../data/kind_type.csv", "../data/info_type.csv",
                                                                 "../data/company_type.csv", "../data/comp_cast_type.csv",
                                                                 "../data/role_type.csv", "../data/movie_keyword.csv",
                                                                 "../data/movie_companies.csv", "../data/aka_title.csv",
                                                                 "../data/aka_name.csv", NULL);
                    timesB[j] += chrono->getChrono();
                    j++;
                    B+=step;
                }while ((needBuffer) && B<maxB+1);
                filenames = " complete_cast,keyword,movie_link,company_name,movie_info_idx,link_type,kind_type,info_type,company_type,comp_cast_type,role_type,movie_keyword,movie_companies,aka_title,aka_name ";
                k=15;

            }
            //    k = 2, size big;
            else if(submeasurement==6) {
                do {
                    chrono->startChrono();
                    experiment3.rrmerge<InputClass, OutputClass>(B, "../data/movie_info.csv", "../data/person_info.csv",
                                                                    NULL);
                    timesB[j] += chrono->getChrono();
                    j++;
                    B+=step;
                }while ((needBuffer) && B<maxB+1);
                filenames = " movie_info,person_info ";
                k=2;
            }
            //    k = 7, size big;
            else if(submeasurement==7) {
                do {
                    chrono->startChrono();
                    experiment3.rrmerge<InputClass, OutputClass>(B, "../data/movie_info.csv", "../data/person_info.csv",
                                                                 "../data/name.csv", "../data/cast_info.csv",
                                                                 "../data/title.csv","../data/movie_keyword.csv", "../data/char_name.csv",NULL);
                    timesB[j] += chrono->getChrono();
                    j++;
                    B+=step;
                }while ((needBuffer) && B<maxB+1);
                filenames = " movie_info,person_info,name,cast_info,title,movie_keyword,char_name";
                k=7;
            }
            //    k= 21, size small + big + medium;
            else if(submeasurement==8) {
                do {
                    chrono->startChrono();
                    experiment3.rrmerge<InputClass, OutputClass>(B, "../data/title.csv", "../data/link_type.csv",
                                                                 "../data/kind_type.csv", "../data/info_type.csv",
                                                                 "../data/company_type.csv", "../data/comp_cast_type.csv",
                                                                 "../data/role_type.csv", "../data/complete_cast.csv",
                                                                 "../data/keyword.csv", "../data/movie_link.csv",
                                                                 "../data/company_name.csv", "../data/movie_info_idx.csv",
                                                                 "../data/movie_keyword.csv", "../data/movie_companies.csv",
                                                                 "../data/aka_title.csv", "../data/aka_name.csv",
                                                                 "../data/movie_info.csv", "../data/person_info.csv",
                                                                 "../data/name.csv", "../data/cast_info.csv","../data/char_name.csv", NULL);
                    timesB[j] += chrono->getChrono();
                    j++;
                    B+=step;
                }while ((needBuffer) && B<maxB+1);
                filenames = " title,link_type,kind_type,info_type,company_type,comp_cast_type,role_type,complete_cast,keyword,movie_link,company_name,movie_info_idx,movie_keyword,movie_companies,aka_title,aka_name,movie_info,person_info,name,cast_info,char_name ";
                k=21;
            }

            times += chrono->getChrono();
            B=minB;
        }
        cout << k << filenames << endl;
        if(needBuffer){
            for (int i = 0; i <(maxB-minB)/step+1; i++) {
                timesB[i]=timesB[i]/nbRep;
                cout << B << " " << timesB[i] << " " << endl;
                B+=step;
            }
        }
        else{
             times= times/nbRep;
             cout << times << endl;
        }
        free(timesB);
        free(chrono);



    }

};


#endif //INFO_H417_GROUP_15_MEASUREMENT_H
