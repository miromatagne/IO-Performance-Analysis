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
//    Experiment1 experiment1;
//    double *times = experiment1.getDurations("../data/aka_name.csv", 70);
//    cout << times[0] << " " << times[1] << " " << times[2] << endl;

    //randjump1
//    Measurement *m1 = new Measurement();
//    m1->testIterations("../data/aka_name.csv", 10, 10, 10000, 100);
// Et celui la pour les 4 fichiers
//    m1->testFiles(0);

    //randjump2
//    Measurement *m2 = new Measurement();
//    m2->testIterations("../data/aka_name.csv", 10, 10, 10000, 100);
// Et celui la pour les 4 fichiers
//    m2->testFiles(0);

    //randjump3
//    Measurement *m3 = new Measurement();
//    m3->testIterations("../data/aka_name.csv", 10, 10, 10000, 100);
// Et celui la pour les 4 fichiers
//m3->testFiles(100);
// Varier B
//    m3->getAverageTimesB("../data/aka_name.csv", 10, 0, 200, 50);

    //randjump4 attention changer B à 65536 dans testIterations a la ligne 98
//    Measurement *m4 = new Measurement();
//    m4->testIterations("../data/aka_name.csv", 10, 10, 10000, 100);
// Et celui la pour les 4 fichiers
//    m4->testFiles(65536);
// Varier B
//    m4->getAverageTimesB("../data/aka_name.csv", 10, 65536, 50*65536, 65536);



    //MultiwayMerge *m = new MultiwayMerge();
    //m->extsort("../data/aka_name.csv", 1, 40000, 10);


//    Experiment1 *e = new Experiment1();
//    cout << e->length3("../data/comp_cast_type.csv", 10) << endl;

//    InputStream *inputStream = new InputStream("../data/person_info.csv");
//    inputStream->open();
//    for (int i = 0; i < 1; i++) {
//        inputStream->readln2();
//    }
    MultiwayMerge m;
    m.extsort("../data/aka_name.csv", 1, 10000, 50);
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

/*
    OutputStream2 outputStream("file_test");
    outputStream.create();
    InputStream4 inputStream("../data/aka_title.csv",5);
    inputStream.open();

    cout << inputStream.readln() << endl;

    cout << inputStream.readln() << endl;
    outputStream.writeln("okijgoijeg");
    outputStream.close();
    inputStream.close();
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

//    Measurement m;
//    m.getAverageTimesB("../data/movie_link.csv", 3, 10, 1000, 10);

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

//    InputStream3 inputStream("../data/comp_cast_type.csv", 2);
//    inputStream.open();
//    inputStream.seek(13);
//    cout << inputStream.readln() << endl;

//    Experiment3 experiment4;
//    experiment4.rrmerge11<InputStream2,OutputStream4>(80000,"../data/company_name.csv","../data/aka_title.csv", NULL);

    return 0;
}

