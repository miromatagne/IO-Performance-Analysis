//
// Created by Miro-Manuel on 31/10/2020.
//

#ifndef INFO_H417_GROUP_15_INPUTSTREAM_H
#define INFO_H417_GROUP_15_INPUTSTREAM_H

#include <iostream>
#include <fstream>

using namespace std;

class InputStream {
private:
    string fileName;
    ifstream file;
public:
    InputStream(string fName);

    string getFileName(void);

    void open(void);
};


#endif //INFO_H417_GROUP_15_INPUTSTREAM_H
