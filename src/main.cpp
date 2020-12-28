#include <iostream>
#include "Experiments/Experiment1.h"
#include <Experiments/Experiment2.h>
#include "Experiments/Experiment3.h"
#include "MultiwayMerge.h"
#include "Chrono.h"
#include "Measurement.h"
#include <windows.h>
#include <InputStreams/InputStream.h>
#include <InputStreams/InputStream1.h>
#include <InputStreams/InputStream2.h>
#include <InputStreams/InputStream3.h>
#include <InputStreams/InputStream4.h>
#include <OutputStreams/OutputStream1.h>
#include <OutputStreams/OutputStream2.h>
#include <OutputStreams/OutputStream3.h>
#include <OutputStreams/OutputStream4.h>
#include <OutputStreams/OutputStream.h>
#include <OutputStreams/OutputStream4.h>
#include <InputStreams/InputStream4.h>
#include <OutputStreams/OutputStream3.h>
#include <InputStreams/InputStream3.h>
#include <OutputStreams/OutputStream2.h>
#include <InputStreams/InputStream2.h>




using namespace std;

int main() {

///////// ICIIIIIII
//    //randjump1
//    Measurement *m1 = new Measurement();
//    m1->testIterations("../data/cast_info.csv", 10, 1, 100, 1);
    //m1->testIterations("../data/cast_info.csv", 10, 100, 1000, 100);
//    m1->testIterations("../data/cast_info.csv", 10, 1000, 10000, 1000);
// Et celui la pour les 3 fichiers
//    m1->testFiles(0);  // faire une fois avec seed = 10 dans la classe Experiment2.h (ligne34)
//    m1->testFiles(0);  // faire une fois avec seed = 100

    //randjump2
    //   Measurement *m2 = new Measurement();
//    m2->testIterations("../data/cast_info.csv", 10, 1, 100, 1);
    //   m2->testIterations("../data/cast_info.csv", 10, 100, 1000, 100);
//    m2->testIterations("../data/cast_info.csv", 10, 1000, 10000, 1000);
// Et celui la pour les 3 fichiers
//    m2->testFiles(0);// faire une fois avec seed = 10 dans la classe Experiment2.h (ligne34)
//    m2->testFiles(0);  // faire une fois avec seed = 100

    //randjump3
    //   Measurement *m3 = new Measurement();
//    m3->testIterations("../data/cast_info.csv", 10, 1, 100, 1);
//    m3->testIterations("../data/cast_info.csv", 10, 100, 1000, 100);
//    m3->testIterations("../data/cast_info.csv", 10, 1000, 10000, 1000);
// Et celui la pour les 3 fichiers
//    m3->testFiles(100);// faire une fois avec seed = 10 dans la classe Experiment2.h (ligne34)
//    m3->testFiles(100);  // faire une fois avec seed = 100

// Varier B
//    m3->getAverageTimesB("../data/aka_name.csv", 10,  1, 10, 1);
    //     m3->getAverageTimesB("../data/aka_name.csv", 10, 100, 1000, 100);
    //long fichier
    // m3->getAverageTimesB("../data/cast_info.csv", 10, 1, 1000, 10);
    //m3->getAverageTimesB("../data/cast_info.csv", 10, 1000, 6000, 100);

   //randjump4 attention changer B à 65536 dans testIterations a la ligne 103
    //    Measurement *m4 = new Measurement();
//       m4->testIterations("../data/cast_info.csv", 10, 1, 100, 1);
 //      m4->testIterations("../data/cast_info.csv", 10, 100, 1000, 100);
//    m4->testIterations("../data/cast_info.csv", 10, 1000, 10000, 1000);
    // Et celui la pour les 3 fichiers
//    m4->testFiles(65536);// faire une fois avec seed = 10 dans la classe Experiment2.h (ligne34)
//    m4->testFiles(65536);  // faire une fois avec seed = 100
// Varier B
//    m4->getAverageTimesB("../data/aka_name.csv", 10, 10*65536, 50*65536, 1000*65536);
//    m4->getAverageTimesB("../data/aka_name.csv", 10, 1000*65536, 5000*65536, 1000*65536);
    //long fichier
    //      m4->getAverageTimesB("../data/cast_info.csv", 10, 10000*65536, 20000*65536, 1000*65536);
    //   m4->getAverageTimesB("../data/cast_info.csv", 10, 32750*65536, 32766*65536, 1*65536);
////// END





    //MultiwayMerge *m = new MultiwayMerge();
    //m->extsort("../data/aka_name.csv", 1, 40000, 10);




    Measurement measurement;
    int Bminimum = 200;
    int Bmaximum = 2000;
    int step = 200;
    int allocationGranularity=65536;
    int nbRep=100;
    for (int i=8; i<=8; i++){

        if(i<3){
            cout << "InputStream2,OutputStream1 " ;
            measurement.getAverageTime3<InputStream2,OutputStream1>(nbRep,i,Bminimum,Bmaximum,step);
            cout << "InputStream4,OutputStream1 " ;
            measurement.getAverageTime3<InputStream4,OutputStream1>(nbRep,i,Bminimum,Bmaximum,step);
        }
        cout << "InputStream2,OutputStream2 " ;
        measurement.getAverageTime3<InputStream2,OutputStream2>(nbRep,i,Bminimum,Bmaximum,step);
        cout << "InputStream4,OutputStream2 " ;
        measurement.getAverageTime3<InputStream4,OutputStream2>(nbRep,i,Bminimum,Bmaximum,step);

        cout << "InputStream2,OutputStream3 " ;
        measurement.getAverageTime3<InputStream2,OutputStream3>(nbRep,i,Bminimum,Bmaximum,step);
        cout << "InputStream4,OutputStream3 " ;
        measurement.getAverageTime3<InputStream4,OutputStream3>(nbRep,i,Bminimum,Bmaximum,step);

        cout << "InputStream4,OutputStream4 ";
        measurement.getAverageTime3<InputStream4,OutputStream4>(nbRep,i,allocationGranularity*Bminimum,allocationGranularity*Bmaximum,allocationGranularity*step);
        cout << "InputStream2,OutputStream4 ";
        measurement.getAverageTime3<InputStream2,OutputStream4>(nbRep,i,allocationGranularity*Bminimum,allocationGranularity*Bmaximum,allocationGranularity*step);

    }


    return 0;
}

