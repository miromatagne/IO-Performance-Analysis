#ifndef INFO_H417_GROUP_15_INPUTSTREAM1_H
#define INFO_H417_GROUP_15_INPUTSTREAM1_H

#include <string>

using namespace std;

class InputStream1 {
private:
    char *fileName;
    FILE *file;

public:
    explicit InputStream1(char *fName);

    void open();

    void close();

    void seek(int pos);

    string readln();
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM1_H
