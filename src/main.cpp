#include "InputStream.h"
#include "OutputStream.h"
#include <iostream>
#include "src/Experiments/Experiment1.h"
#include "src/Experiments/Experiment3.h"
#include "Measurement.h"
#include <windows.h>
#include <src/InputStreams/InputStream1.h>
#include <src/InputStreams/InputStream2.h>
#include <src/InputStreams/InputStream3.h>

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

    InputStream2 *i1 = new InputStream2("../data/person_info.csv");
    i1->open();
    cout << i1->readln() << endl;
    cout << i1->readln() << endl;
    cout << i1->readln() << endl;
    cout << i1->readln() << endl;
    i1->close();

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

