#include "InputStream.h"
#include "OutputStream.h"
#include <iostream>

using namespace std;

int main() {
    InputStream inputStream("../data/aka_name.csv");
    inputStream.open();
    cout << inputStream.readln1();
    inputStream.close();
    OutputStream outputStream("file_test");
    outputStream.create();
    outputStream.writeln4("Bonjoureee grg porpe");
    outputStream.close();
    return 0;
}