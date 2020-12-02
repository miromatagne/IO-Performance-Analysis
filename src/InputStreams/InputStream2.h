#ifndef INFO_H417_GROUP_15_INPUTSTREAM2_H
#define INFO_H417_GROUP_15_INPUTSTREAM2_H

#include "InputStream.h"
#include <string>

using namespace std;

class InputStream2 : public InputStream {
public:
    InputStream2(char *fName);

    string readln();
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM2_H
