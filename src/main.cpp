#include "InputStream.h"
#include "OutputStream.h"
#include <iostream>
#include "Experiment1.h"
#include <windows.h>

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
    //InputStream inputStream("../data/comp_cast_type.csv");
//    InputStream inputStream("../data/movie_companies.csv");
//    inputStream.open();
//
//    int i = 0;
//    while(i<32552) {  //32552
//        cout << inputStream.readln4() << endl;
//        i++;
//    }
//    inputStream.close();
//    OutputStream outputStream("file_test");
//    outputStream.create();
//    outputStream.writeln4("LA CONSTITUTION\n");
//    outputStream.close();

    Experiment1 experiment1;
    double *times = experiment1.getDurations("../data/aka_name.csv", 70);
    cout << times[0] << " " << times[1] << " " << times[2] << endl;

//    Chrono *chrono = new Chrono();
//    chrono->startChrono();
//    cout << experiment1.length1("../data/aka_name.csv") << endl;
//    cout << chrono->getChrono() << endl;
//
//    chrono->startChrono();
//    cout << experiment1.length2("../data/aka_name.csv") << endl;
//    cout << chrono->getChrono() << endl;
//
//    chrono->startChrono();
//    cout << experiment1.length3("../data/aka_name.csv") << endl;
//    cout << chrono->getChrono() << endl;
    return 0;
}

