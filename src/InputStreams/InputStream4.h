#ifndef INFO_H417_GROUP_15_INPUTSTREAM4_H
#define INFO_H417_GROUP_15_INPUTSTREAM4_H

#include <istream>
#include <windows.h>
#include "InputStream.h"

using namespace std;

class InputStream4 : public InputStream {
private:
    void map(DWORD toMap);

    void unmap();

    HANDLE rhFile;
    int fd;
    HANDLE rhMapFile;
    LPCTSTR readBuffer;
    int start_file;
    DWORD start;
    DWORD sizePageBuffer;
    DWORD sizeByteFile;
    int test;


public:
    explicit InputStream4(char *fName, int B);

    void open();

    void close();

    void seek(int pos);

    std::string readln();

};

#endif //INFO_H417_GROUP_15_INPUTSTREAM4_H
