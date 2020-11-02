#include "InputStream.h"
#include "OutputStream.h"
#include <iostream>
#include "Experiment1.h"

using namespace std;

int main() {
    InputStream inputStream("../data/comp_cast_type.csv");
    inputStream.open();
    cout << inputStream.readln1();
    cout << inputStream.readln1();
    cout << inputStream.readln1();
    cout << inputStream.readln1();
    cout << inputStream.readln1();
    inputStream.close();
//    OutputStream outputStream("file_test");
//    outputStream.create();
//    outputStream.writeln1("Bonjour");
//    outputStream.close();
//    Experiment1 experiment1;
//    cout << experiment1.length1("../data/comp_cast_type.csv");
    return 0;
}

