#ifndef INFO_H417_GROUP_15_INPUTSTREAM3_H
#define INFO_H417_GROUP_15_INPUTSTREAM3_H

class InputStream3 {
private:
    char *fileName;
    FILE *file;
    int B;
    char *buffer = nullptr;
    int index;

    int readToBuffer();

public:
    explicit InputStream3(char *fName, int B);

    void open();

    void close();

    void seek(int pos);

    char *readln();
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM3_H
