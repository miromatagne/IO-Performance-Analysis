#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM4_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM4_H

#include <ostream>
#include <fstream>
#include <windows.h>
#include "OutputStream.h"
using namespace std;
//
class OutputStream4 : public OutputStream{
private:
    FILE* file;
    HANDLE hFile;
    int fd;
    char* addNewLine();
    void map(int toMap);
    void unmap();
    HANDLE hMapFile;
    LPCTSTR writeBuffer;
    DWORD sizePageBuffer;
    DWORD start_file;


public:
    OutputStream4(char* fName,int B);
    void create();
    void writeln(string text);
    void close();
};


#endif //INFO_H417_GROUP_15_OUTPUTSTREAM4_H
