#ifndef INFO_H417_GROUP_15_INPUTSTREAM4_H
#define INFO_H417_GROUP_15_INPUTSTREAM4_H

#include <istream>
#include <windows.h>

using namespace std;

class InputStream4 {
private:
    void map(DWORD toMap);
    void unmap();
    char *fileName;
    FILE *file;
    HANDLE hFile;
    int fd;
    HANDLE hMapFile;
    LPCTSTR readBuffer;
    int start_file;
    DWORD start;
    DWORD sizePageBuffer;
    DWORD sizeByteFile;


public:
    explicit InputStream4(char *fName, int B);

    void open();

    void close();

    void seek(int pos);

    std::string readln();

};

#endif //INFO_H417_GROUP_15_INPUTSTREAM4_H
