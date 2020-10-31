#include "InputStream.h"
#include "OutputStream.h"
int main() {
    InputStream inputStream("../data/aka_name.csv");
    inputStream.open();
    return 0;
}