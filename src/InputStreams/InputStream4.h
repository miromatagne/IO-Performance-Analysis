#ifndef INFO_H417_GROUP_15_INPUTSTREAM4_H
#define INFO_H417_GROUP_15_INPUTSTREAM4_H

#include <istream>
#include <windows.h>

using namespace std;

class InputStream4 {
private:
    int sizeFile();
    void map(int toMap);
    void unmap();

    char *fileName;
    FILE *file;
    HANDLE hFile;
    int fd;
    int B;
    HANDLE hMapFile;
    LPCTSTR readBuffer;
    int start_file;
    DWORD start;
    DWORD sizePageBuffer;
    int save;
    int nbMap;
    int sizeByteFile;
    int position;
    char *buffer = nullptr;

public:
    explicit InputStream4(char *fName, int B);

    void open();

    void close();

    void seek(int pos);

    std::string readln();

};

#endif //INFO_H417_GROUP_15_INPUTSTREAM4_H
