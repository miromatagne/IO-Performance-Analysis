#include "InputStream.h"
#include "OutputStream.h"

int main() {
    //InputStream inputStream("../data/aka_name.csv");
   // inputStream.open();
 //   inputStream.readln1();
   // inputStream.close();
    OutputStream outputStream("file_test");
    outputStream.create();
    outputStream.writeln1("Bonjour");
    outputStream.close();
    return 0;
}