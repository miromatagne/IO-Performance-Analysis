#ifndef INFO_H417_GROUP_15_OUTPUTSTREAM_H
#define INFO_H417_GROUP_15_OUTPUTSTREAM_H

#include <ostream>
#include <fstream>

using namespace std;

class OutputStream {
private:
    string fileName;
    ofstream file;
public:
    explicit OutputStream(string fName);

    void create();

    void writeln(string text);

    void close();
};


#endif //INFO_H417_GROUP_15_OUTPUTSTREAM_H
