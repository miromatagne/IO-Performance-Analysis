#ifndef INFO_H417_GROUP_15_EXPERIMENT4_H
#define INFO_H417_GROUP_15_EXPERIMENT4_H


#include "InputStream.h"
#include "Chrono.h"

class Experiment4 {
private:
    char *fileName;

    char *(*function12)(InputStream inputStream);

    char *(*function34)(InputStream inputStream, int B);

public:
    explicit Experiment4();
    void rrmerge (char *fileName,...);
};


#endif //INFO_H417_GROUP_15_EXPERIMENT4_H
