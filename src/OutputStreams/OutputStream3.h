#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM3_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM3_H

#include <ostream>
#include <fstream>
#include <windows.h>
#include "OutputStream.h"
using namespace std;
//
class OutputStream3 : public OutputStream{
private:
private:
    char *buffer = nullptr;
    int index;
public:
   OutputStream3(char* fName,int B);

    void writeln(string text);

    void close();
};


#endif //INFO_H417_GROUP_15_OUTPUTSTREAM3_H
