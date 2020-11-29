#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM1_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM1_H

#include <ostream>
#include <fstream>
#include <windows.h>

using namespace std;

//
class OutputStream1 {
private:
    const char *fileName;
    FILE *file;

public:
public:
    explicit OutputStream1(const char *fName);

    void create();

    void writeln(string text) const;

    void close();
};


#endif //INFO_H417_GROUP_15_OUTPUTSTREAM1_H
