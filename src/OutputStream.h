#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM_H

#include <ostream>
#include <fstream>
#include <windows.h>
using namespace std;
//
class OutputStream {
private:
    const char *fileName;
    FILE* file;
    HANDLE hFile;
    int fd;

public:
    explicit OutputStream(const char* fName);
    void create();
    void writeln1(string text) const;
    void writeln2(string text);
    void writeln3(string text) const;
    void writeln4(string text);
    void close();
};


#endif //INFO_H417_GROUP_15_OUTPUTSTREAM_H
