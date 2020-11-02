#include "InputStream.h"
#include "OutputStream.h"
#include <iostream>

using namespace std;

int length1(char *fileName) {
    int sum = 0;
    InputStream inputStream(fileName);
    inputStream.open();
    char *line;
    line = inputStream.readln1();
    sum += strlen(line);
    int i = 0;
    while (i < 2) {
        line = inputStream.readln1();
        sum += strlen(line);
        i++;
    }
    inputStream.close();
    return sum;
}

int main() {
    InputStream inputStream("../data/comp_cast_type.csv");
    inputStream.open();
    cout << inputStream.readln1();
    inputStream.close();
    OutputStream outputStream("file_test");
    outputStream.create();
    outputStream.writeln1("Bonjour");
    outputStream.close();
    cout << length1("../data/comp_cast_type.csv");
    return 0;
}

