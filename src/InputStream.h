#ifndef INFO_H417_GROUP_15_INPUTSTREAM_H
#define INFO_H417_GROUP_15_INPUTSTREAM_H

#include <string>
#include <fstream>

using namespace std;

class InputStream {
private:
    char *fileName;
    FILE *file;

public:
    explicit InputStream(char *fName);

    void open();

    void readln();

    void close();

    void seek(int pos);
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM_H
