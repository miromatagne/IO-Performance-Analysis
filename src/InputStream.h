#ifndef INFO_H417_GROUP_15_INPUTSTREAM_H
#define INFO_H417_GROUP_15_INPUTSTREAM_H

#include <istream>
#include <fstream>

using namespace std;

class InputStream {
private:
    string fileName;
    ifstream file;
public:
    explicit InputStream(string fName);

    void open();

    void close();

    void seek(int pos);
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM_H
