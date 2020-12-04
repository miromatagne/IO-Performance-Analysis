
#ifndef INFO_H417_GROUP_15_INPUTSTREAM_H
#define INFO_H417_GROUP_15_INPUTSTREAM_H


#include <string>

using namespace std;

class InputStream {
protected:
    char *fileName;
    FILE *file;
    int BufferSize;

public:
    InputStream(char *fName, int B);

    void open();

    void close();

    void seek(int pos);

    FILE * getFile();
};




#endif //INFO_H417_GROUP_15_INPUTSTREAM_H
