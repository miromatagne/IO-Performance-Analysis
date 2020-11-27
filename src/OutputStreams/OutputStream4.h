#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM4_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM4_H

#include <ostream>
#include <fstream>
#include <windows.h>
using namespace std;
//
class OutputStream4 {
private:
    const char *fileName;
    FILE* file;
    HANDLE hFile;
    int fd;
    char* addNewLine();
    void map(int toMap);
    void unmap();
    HANDLE hMapFile;
    LPCTSTR writeBuffer;
    DWORD sizePageBuffer;
    DWORD start;
    int toMapWrite;
    int nbExtension;
    int start_file;
    int end;
    int a;


public:
    explicit OutputStream4(const char* fName);
    void create();
    void writeln(string text);
    void close();
};


#endif //INFO_H417_GROUP_15_OUTPUTSTREAM4_H
