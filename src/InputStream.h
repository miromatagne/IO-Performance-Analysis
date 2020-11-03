#ifndef INFO_H417_GROUP_15_INPUTSTREAM_H
#define INFO_H417_GROUP_15_INPUTSTREAM_H

#include <string>
#include <fstream>
#include <istream>

using namespace std;

class InputStream {
private:
    char *fileName;
    FILE *file{};

public:
    explicit InputStream(char *fName);

    void open();

    char* readln1();

    void readln2();

    char* readln3();

    void close();

    void seek(int pos);
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM_H
