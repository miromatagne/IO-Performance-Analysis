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
#include <vector>
#include <type_traits>
#include <typeinfo>

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

//    Measurement *m = new Measurement();
//    m->testFiles(0);
    //MultiwayMerge *m = new MultiwayMerge();
    //m->extsort("../data/aka_name.csv", 1, 40000, 10);
    /*
    InputStream4 inputStream4("../data/movie_companies.csv", 4);
    inputStream4.open();

    string line;
    line = inputStream4.readln();
    while (line != "") {
        line = inputStream4.readln();
        cout << line << endl;
    }
    inputStream4.close();
     */
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

//    InputStream2 inputStream2("../data/aka_title.csv", NULL);
//    inputStream2.open();
//    string line = "let's start !";
//
//    while (line != "") {
//        line = inputStream2.readln();
//        cout << line << endl;
//    }
//    inputStream2.close();

//    Experiment1 e;
//    int l = e.length<InputStream1>("../data/aka_name.csv", 100);
//    cout << l << endl;

    InputStream4 i("../data/comp_cast_type.csv", 100);
    i.open();
    cout << i.readln() << endl;


    /*
    InputStream inputStream ("../data/aka_title.csv");
    inputStream.open();
    int i =0;
    while (i<11915) {
        inputStream.readln4(5);
*/
    /*
       Experiment2 experiment2;
       int sum = experiment2.randjump1("../data/aka_name.csv", 10);
       cout << sum << endl;
       int sum2 = experiment2.randjump2("../data/aka_name.csv", 10);
       cout << sum2 << endl;
       int sum3 = experiment2.randjump3("../data/aka_name.csv", 10, 2);
       cout << sum3 << endl;

           i++;
       }
       inputStream.close();
        */


       //Experiment3 experiment4;
       //experiment4.rrmerge11<InputStream4,OutputStream4>(30,"../data/comp_cast_type.csv", "../data/aka_name.csv", NULL);
       /*
       InputStream4 i("../data/comp_cast_type.csv",30);
       i.open();
       cout << i.readln() << endl;
       i.close();
        */
    return 0;
}

