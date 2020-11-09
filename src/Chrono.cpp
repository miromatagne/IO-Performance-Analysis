#include "Chrono.h"
#include <windows.h>
#include <iostream>

using namespace std;

void Chrono::startChrono() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
};

double Chrono::getChrono() {
    LARGE_INTEGER li2;
    QueryPerformanceCounter(&li2);
    return double(li2.QuadPart - CounterStart) / PCFreq;
}