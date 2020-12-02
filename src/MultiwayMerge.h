#ifndef INFO_H417_GROUP_15_MULTIWAYMERGE_H
#define INFO_H417_GROUP_15_MULTIWAYMERGE_H


#include <cstdio>
#include <string>
#include <src/InputStreams/InputStream.h>
#include <src/InputStreams/InputStream1.h>

using namespace std;

class MultiwayMerge {
private:
    struct QueueObject {
        InputStream1 *inputStream;
        vector<string> line;
    };

    vector<string> stringToVector(string stringLine);

    string vectorToString(vector<string> vectorLine);

public:
    MultiwayMerge();

    FILE *extsort(char *fileName, int k, int M, int d);
};


#endif //INFO_H417_GROUP_15_MULTIWAYMERGE_H
