#include "InputStream.h"
#include "OutputStream.h"
#include <iostream>
#include "Experiments/Experiment1.h"
#include "Experiments/Experiment3.h"
#include "Measurement.h"
#include "MultiwayMerge.h"
#include <windows.h>
#include <InputStreams/InputStream1.h>
#include <InputStreams/InputStream2.h>
#include <InputStreams/InputStream3.h>
#include <InputStreams/InputStream4.h>

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

    //Measurement *m = new Measurement();
    //m->testFiles(0);

//    InputStream4 *i4 = new InputStream4("../data/aka_name.csv", 4);
//    i4->open();
//    int i = 0;
//    while(i < 16267){
//        cout << i4->readln() << endl;
//        i++;
//    }
//    InputStream1 *i1 = new InputStream1("../data/aka_name.csv");
//    i1->open();
//    for (int i = 0; i < 16300; i++) {
//        string line = i1->readln();
//        cout << line << endl;
//    }

    MultiwayMerge *m = new MultiwayMerge();
    m->extsort("../data/aka_name.csv", 2, 500, 12);
    //cout << i4->readln() << endl;
    //cout << i4->readln() << endl;
//    cout << i1->readln() << endl;
//    cout << i1->readln() << endl;
//    cout << i1->readln() << endl;
    //i4->close();

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
/*
    OutputStream outputStream("file_test");
    outputStream.create();
    outputStream.writeln4("Bonjoureee grg porpe");
    outputStream.writeln4("Bonjoureee gjppppppppppppppppppppp");
   // outputStream.writeln4("eijgarejgireajglirejgalrjglkejg");
    outputStream.close();
*/

//    Experiment3 experiment4;
//    experiment4.rrmerge11("../data/aka_title.csv", "../data/aka_name.csv", NULL);

    /*
    InputStream inputStream ("../data/aka_title.csv");
    inputStream.open();
    int i =0;
    while (i<11915) {
        inputStream.readln4(5);

        i++;
    }
    inputStream.close();
     */
    return 0;
}

