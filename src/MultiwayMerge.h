#ifndef INFO_H417_GROUP_15_MULTIWAYMERGE_H
#define INFO_H417_GROUP_15_MULTIWAYMERGE_H



#include <string>
#include <InputStreams/InputStream.h>
#include <InputStreams/InputStream1.h>
#include <InputStreams/InputStream2.h>
#include <InputStreams/InputStream3.h>

using namespace std;

class MultiwayMerge {
private:
    struct QueueObject {
        InputStream3 *inputStream;
        vector<string> line;
    };

    static vector<string> stringToVector(string stringLine);

    string vectorToString(vector<string> vectorLine);

public:
    MultiwayMerge();

    FILE *extsort(char *fileName, int k, int M, int d);
};


#endif //INFO_H417_GROUP_15_MULTIWAYMERGE_H
