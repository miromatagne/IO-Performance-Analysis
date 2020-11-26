#ifndef INFO_H417_GROUP_15_INPUTSTREAM2_H
#define INFO_H417_GROUP_15_INPUTSTREAM2_H

#include <string>

using namespace std;

class InputStream2 {
private:
    char *fileName;
    FILE *file;

public:
    explicit InputStream2(char *fName);

    void open();

    void close();

    void seek(int pos);

    string readln();
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM2_H
