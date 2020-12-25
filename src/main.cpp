#include <iostream>
#include "Experiments/Experiment1.h"
#include "Experiments/Experiment3.h"
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
#include "Chrono.h"
#include "MultiwayMerge.h"
#include <vector>
#include <type_traits>
#include <typeinfo>
#include <Experiments/Experiment2.h>


using namespace std;

//double PCFreq = 0.0;
//__int64 CounterStart = 0;
//
//void startChrono() {
//    LARGE_INTEGER li;
//    if (!QueryPerformanceFrequency(&li))
//        cout << "QueryPerformanceFrequency failed!\n";
//
//    PCFreq = double(li.QuadPart) / 1000.0;
//
//    QueryPerformanceCounter(&li);
//    CounterStart = li.QuadPart;
//};
//
//double getChrono() {
//    LARGE_INTEGER li2;
//    QueryPerformanceCounter(&li2);
//    return double(li2.QuadPart - CounterStart) / PCFreq;
//}

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


//    Experiment1 *e = new Experiment1();
//    cout << e->length3("../data/comp_cast_type.csv", 10) << endl;

//    InputStream *inputStream = new InputStream("../data/person_info.csv");
//    inputStream->open();
//    for (int i = 0; i < 1; i++) {
//        inputStream->readln2();
//    }
/*
    Experiment1 experiment1;
    Chrono *chrono = new Chrono();
    double *times = (double *) malloc(110 * sizeof(double));
    for (int i = 10; i < 121; i++) {
        chrono->startChrono();
        experiment1.length3("../data/aka_name.csv", i);
        times[i - 10] = chrono->getChrono();
    }
    double sum = 0;
    for (int i = 0; i < 110; i++) {
        cout << times[i] << endl;
    }
    free(times);
    //cout << sum / 100 << endl;
*/



//    Experiment1 e;
//   int l = e.length<InputStream2>("../data/aka_name.csv", 100);
//   cout << l << endl;

//    Measurement m;
//    m.testFiles();

//    for (int i = 0; i < 1000; i++) {
//        Chrono *chrono = new Chrono();
//        InputStream2 i2("../data/cast_info.csv", 0);
//        i2.open();
//        chrono->startChrono();
//        i2.test();
//        cout << chrono->getChrono() << endl;
//        free(chrono);
//        i2.close();
//    }

//    Experiment1 experiment1;
//    cout << experiment1.length<InputStream4>("../data/aka_title.csv", 100) << endl;



    //InputStream4 i("../data/comp_cast_type", 100);
//    OutputStream3 os("../data/company_name3.csv", 2000);
//    InputStream3 is("../data/company_name.csv", 2000);
//    is.open();
//    os.create();
//    for (int i = 0; i < 156664; i++) {
//        string line = is.readln();
//        os.writeln(line);
//    }
//    os.close();
//    is.close();
//    InputStream2 i("../data/aka_name.csv", 100);
//    i.open();
//    cout << i.readln().length() << endl;


    /*
    InputStream inputStream ("../data/aka_title.csv");
    inputStream.open();
    int i =0;
    while (i<11915) {
        inputStream.readln4(5);
*/

   /* Experiment2 experiment2;
    cout << experiment2.randjump<InputStream1>("../data/aka_name.csv", 50000, 2) << endl;
    cout << experiment2.randjump<InputStream2>("../data/aka_name.csv", 50000, 2) << endl;
    cout << experiment2.randjump<InputStream3>("../data/aka_name.csv", 50000, 2) << endl;
    cout << experiment2.randjump<InputStream4>("../data/aka_name.csv", 50000, 2) << endl;
*/


/*    int sum = experiment2.randjump1("../data/aka_name.csv", 10000); //8000
    cout << "sum: " << sum << endl;
    int sum2 = experiment2.randjump2("../data/aka_name.csv", 10000);
    cout << "sum: " << sum2 << endl;
    int sum3 = experiment2.randjump3("../data/aka_name.csv", 10000, 2);
    cout << "sum: " << sum3 << endl;
    int sum4 = experiment2.randjump4("../data/aka_name.csv", 10000, 2);
    cout << "sum: " << sum4 << endl;
    if(sum==sum2 && sum3==sum4 && sum2==sum3){
        cout << "ok2" << endl;
    }
    */
    //MultiwayMerge multiwayMerge;
    //multiwayMerge.extsort("../data/aka_name.csv",1,10000,50);
//    InputStream3 inputStream("../data/comp_cast_type.csv", 2);
//    inputStream.open();
//    inputStream.seek(13);
//    cout << inputStream.readln() << endl;

//    Experiment3 experiment3;
//    Chrono chrono;
//    chrono.startChrono();
    //k small, size medium
//    experiment3.rrmerge<InputStream2,OutputStream1>(40, 80000, "../data/movie_link.csv", NULL);
//    //k big, size small
//    experiment3.rrmerge<InputStream4,OutputStream4>(40, 80000, "../data/link_type.csv","../data/kind_type.csv","../data/info_type.csv", "../data/company_type.csv","../data/comp_cast_type.csv","../data/role_type.csv",NULL);
//    //k big, size medium
//    experiment3.rrmerge<InputStream4,OutputStream4>(100, 8000, "../data/complete_cast.csv", "../data/keyword.csv","../data/movie_link.csv","../data/company_name.csv","../data/movie_info_idx.csv","../data/movie_keyword.csv","../data/movie_companies.csv","../data/aka_title.csv","../data/aka_name.csv",NULL);
      // k very big, size small + medium
//    experiment3.rrmerge<InputStream2,OutputStream4>(100, 8000, "../data/complete_cast.csv", "../data/keyword.csv","../data/movie_link.csv","../data/company_name.csv","../data/movie_info_idx.csv","../data/link_type.csv","../data/kind_type.csv","../data/info_type.csv", "../data/company_type.csv","../data/comp_cast_type.csv","../data/role_type.csv","../data/movie_keyword.csv", "../data/movie_companies.csv","../data/aka_title.csv","../data/aka_name.csv",NULL);
      // k medium, size big
//    experiment3.rrmerge<InputStream4,OutputStream4>(40, 80000, "../data/movie_info.csv", "../data/person_info.csv","../data/name.csv","../data/cast_info.csv","../data/title.csv", NULL);
      // all in : k big, size small + big + medium
//    experiment3.rrmerge<InputStream2,OutputStream1>(40, 80000, "../data/title.csv","../data/link_type.csv","../data/kind_type.csv","../data/info_type.csv", "../data/company_type.csv","../data/comp_cast_type.csv","../data/role_type.csv", "../data/complete_cast.csv", "../data/keyword.csv","../data/movie_link.csv","../data/company_name.csv","../data/movie_info_idx.csv","../data/movie_keyword.csv","../data/movie_companies.csv","../data/aka_title.csv","../data/aka_name.csv","../data/movie_info.csv", "../data/person_info.csv","../data/name.csv","../data/cast_info.csv",NULL);
//    cout << chrono.getChrono() << endl;

    Measurement measurement;
    int Bminimum = 200;
    int Bmaximum = 2000;
    int step = 200;
    int allocationGranularity=65536;
    for (int i=1; i<=8; i++){

        if(i<3){
            cout << "InputStream2,OutputStream1 " ;
            measurement.getAverageTime3<InputStream2,OutputStream1>(1,i,Bminimum,Bmaximum,step);
            cout << "InputStream4,OutputStream1 " ;
            measurement.getAverageTime3<InputStream4,OutputStream1>(1,i,Bminimum,Bmaximum,step);
        }
        cout << "InputStream2,OutputStream2 " ;
        measurement.getAverageTime3<InputStream2,OutputStream2>(1,i,Bminimum,Bmaximum,step);
        cout << "InputStream4,OutputStream2 " ;
        measurement.getAverageTime3<InputStream4,OutputStream2>(1,i,Bminimum,Bmaximum,step);

        cout << "InputStream2,OutputStream3 " ;
        measurement.getAverageTime3<InputStream2,OutputStream3>(1,i,20,200,20);
        cout << "InputStream2,OutputStream3 " ;
        measurement.getAverageTime3<InputStream2,OutputStream3>(1,i,Bminimum,Bmaximum,step);
        cout << "InputStream4,OutputStream3 " ;
        measurement.getAverageTime3<InputStream4,OutputStream3>(1,i,20,200,20);
        cout << "InputStream4,OutputStream3 " ;
        measurement.getAverageTime3<InputStream4,OutputStream3>(1,i,Bminimum,Bmaximum,step);


        cout << "InputStream4,OutputStream4 ";
        measurement.getAverageTime3<InputStream4,OutputStream4>(1,i,allocationGranularity,allocationGranularity,allocationGranularity);
        measurement.getAverageTime3<InputStream4,OutputStream4>(1,i,allocationGranularity*200,allocationGranularity*200,allocationGranularity*200);

        cout << "InputStream2,OutputStream4 ";
        measurement.getAverageTime3<InputStream2,OutputStream4>(1,i,allocationGranularity,allocationGranularity,allocationGranularity);
        measurement.getAverageTime3<InputStream2,OutputStream4>(1,i,allocationGranularity*200,allocationGranularity*200,allocationGranularity*200);

    }

//   // measurement.getAverageTime3<InputStream2,OutputStream2>(3,1,20,500,20);
//    cout << "InputStream2,OutputStream1 " ;
//    measurement.getAverageTime3<InputStream2,OutputStream1>(1,1,Bminimum,Bmaximum,step);
//    cout << "InputStream2,OutputStream2 " ;
//    measurement.getAverageTime3<InputStream2,OutputStream2>(10,1,Bminimum,Bmaximum,step);
//    cout << "InputStream2,OutputStream3 " ;
//    measurement.getAverageTime3<InputStream2,OutputStream3>(3,1,Bminimum,Bmaximum,step);
//    cout << "InputStream2,OutputStream4 ";
//    measurement.getAverageTime3<InputStream2,OutputStream4>(3,1,Bminimum,Bmaximum,step);
//
//    cout << "InputStream4,OutputStream1 " ;
//    measurement.getAverageTime3<InputStream4,OutputStream1>(1,1,Bminimum,Bmaximum,step);
//    cout << "InputStream4,OutputStream2 " ;
//    measurement.getAverageTime3<InputStream4,OutputStream2>(10,1,Bminimum,Bmaximum,step);
//    cout << "InputStream4,OutputStream3 " ;
//    measurement.getAverageTime3<InputStream4,OutputStream3>(3,1,Bminimum,Bmaximum,step);
//    cout << "InputStream4,OutputStream4 ";
//    measurement.getAverageTime3<InputStream4,OutputStream4>(3,1,65536,Bmaximum*65536,Bmaximum*65536-65536);
    return 0;
}

