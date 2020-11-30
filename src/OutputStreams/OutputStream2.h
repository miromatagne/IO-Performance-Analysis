#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM2_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM2_H

#include <ostream>
#include <fstream>
#include "OutputStream.h"
using namespace std;
//
class OutputStream2  : public OutputStream{

public:
    OutputStream2(char* fName);

    void writeln(string text)const;

};


#endif //INFO_H417_GROUP_15_OUTPUTSTREAM2_H
