#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM_H

#include <ostream>
#include <fstream>

using namespace std;

class OutputStream {
private:
    const char *fileName;
    FILE* file;

public:
    explicit OutputStream(const char* fName);

    void create();

    void writeln3(string text);
    void writeln1(string text);

    void close();
};


#endif //INFO_H417_GROUP_15_OUTPUTSTREAM_H
