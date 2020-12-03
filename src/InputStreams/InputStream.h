
#ifndef INFO_H417_GROUP_15_INPUTSTREAM_H
#define INFO_H417_GROUP_15_INPUTSTREAM_H


#include <string>

using namespace std;

class InputStream {
protected:
    char *fileName;
    FILE *file;

public:
    InputStream(char *fName);

    void open();

    void close();

    void seek(int pos);

    FILE * getFile();

    //virtual string readln() = 0;
};




#endif //INFO_H417_GROUP_15_INPUTSTREAM_H
