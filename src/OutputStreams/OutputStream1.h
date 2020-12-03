#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM1_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM1_H

#include <ostream>
#include <fstream>
#include <windows.h>
#include "OutputStream.h"

using namespace std;

//
class OutputStream1 : public OutputStream{

public:
    OutputStream1(char *fName,int B);

    void writeln(string text) const;

};


#endif //INFO_H417_GROUP_15_OUTPUTSTREAM1_H
