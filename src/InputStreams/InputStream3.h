#ifndef INFO_H417_GROUP_15_INPUTSTREAM3_H
#define INFO_H417_GROUP_15_INPUTSTREAM3_H

#include <string>
#include "InputStream.h"

class InputStream3 : public InputStream {
private:
    char *buffer = nullptr;
    int index;
    int bufferLength;

    int readToBuffer();

public:
    InputStream3(char *fName, int B);

    void seek(int pos);

    std::string readln();
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM3_H
