#ifndef INFO_H417_GROUP_15_INPUTSTREAM2_H
#define INFO_H417_GROUP_15_INPUTSTREAM2_H

#include "InputStream.h"

using namespace std;

class InputStream2 : public InputStream {
private:
    char *line;
    size_t len;
    char chunk[1000];
public:
    InputStream2(char *fName, int B);

    void close();

    string readln();

};


#endif //INFO_H417_GROUP_15_INPUTSTREAM2_H
