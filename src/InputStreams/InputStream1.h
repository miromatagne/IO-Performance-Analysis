#ifndef INFO_H417_GROUP_15_INPUTSTREAM1_H
#define INFO_H417_GROUP_15_INPUTSTREAM1_H

#include "InputStream.h"

using namespace std;

class InputStream1 : public InputStream {

public:
    explicit InputStream1(char *fName, int B);

    string readln();

};


#endif //INFO_H417_GROUP_15_INPUTSTREAM1_H
