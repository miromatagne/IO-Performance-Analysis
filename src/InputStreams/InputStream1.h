#ifndef INFO_H417_GROUP_15_INPUTSTREAM1_H
#define INFO_H417_GROUP_15_INPUTSTREAM1_H

#include <string>
#include "InputStream.h"

using namespace std;

class InputStream1 : public InputStream{

public:
    InputStream1(char *fName);

    string readln();
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM1_H
