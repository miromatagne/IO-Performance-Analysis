#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM2_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM2_H

#include <ostream>
#include <fstream>

using namespace std;
//
class OutputStream2 {
private:
    const char *fileName;
    FILE* file;

public:
public:
    explicit OutputStream2(const char* fName);
    void create();
    void writeln(string text)const;
    void close();
};


#endif //INFO_H417_GROUP_15_OUTPUTSTREAM2_H
