#ifndef INFO_H417_GROUP_15_INPUTSTREAM_H
#define INFO_H417_GROUP_15_INPUTSTREAM_H

#include <string>
#include <fstream>
#include <istream>
#include <windows.h>

using namespace std;

class InputStream {
private:
    char *fileName;
    FILE *file{};
    HANDLE hFile;
    int fd;

public:
    explicit InputStream(char *fName);

    void open();

    char *readln1();

    char *readln2();

    char *readln3(int B);

    char *readln4(int B);

    void close();

    void seek(int pos);
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM_H
