#include "InputStream.h"
#include "OutputStream.h"
#include <iostream>
#include "Experiment1.h"
#include <windows.h>

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void startChrono() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
};

double getChrono() {
    LARGE_INTEGER li2;
    QueryPerformanceCounter(&li2);
    return double(li2.QuadPart - CounterStart) / PCFreq;
}

int main() {
    InputStream inputStream("../data/aka_name.csv");
    inputStream.open();

    cout << inputStream.readln3();

    /*for (int i = 0; i<5; i++) {
        cout << inputStream.readln3();
    }*/
//    inputStream.close();
//    OutputStream outputStream("file_test");
//    outputStream.create();
//    outputStream.writeln1("Bonjour");
//    outputStream.close();

    /*Experiment1 experiment1;
    startChrono();
    cout << experiment1.length1("../data/comp_cast_type.csv") << endl;
    cout << getChrono() << endl;
    */
    return 0;
}

