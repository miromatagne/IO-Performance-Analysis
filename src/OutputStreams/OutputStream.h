//
// Created by minhx on 30-11-20.
//

#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM_H

#include <ostream>
#include <fstream>
#include <windows.h>

using namespace std;

//
class OutputStream {
protected:
    const char *fileName;
    FILE *file;
    int BufferSize;

public:
    OutputStream(char *fName,int B);

    void create();

    void close();

   // virtual void writeln(string text) const = 0;

};



#endif //INFO_H417_GROUP_15_OUTPUTSTREAM_H
