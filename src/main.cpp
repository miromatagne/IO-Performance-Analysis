#include "InputStream.h"
#include "OutputStream.h"
int main() {
    InputStream inputStream("../data/aka_name.csv");
    inputStream.open();
    OutputStream outputStream("file_test");
    outputStream.create();
    outputStream.writeln("Bonjour");
    outputStream.close();
    return 0;
}