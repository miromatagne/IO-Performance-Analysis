#ifndef INFO_H417_GROUP_15_EXPERIMENT3_H
#define INFO_H417_GROUP_15_EXPERIMENT3_H


#include <vector>

using namespace std;
class Experiment3 {
public:
    Experiment3() {
    }
/**
 * Merge files in a round robin fashion
 * @param Bo BufferSize for OutputStream class
 * @param fileName variable number of filenames
 */
    template<class InputClass, class OutputClass>
    void rrmerge(int Bo, char *fileName, ...) {
        vector<InputClass> readerList;
        OutputClass outputStream("../data/experiment3.txt", Bo);
        outputStream.create();
        va_list vl;
        va_start(vl, fileName);
        char *arg = fileName;
        int i = 0;
        do {
            InputClass inputStream(arg, 100);
            readerList.push_back(inputStream);
            readerList[i].open();
            arg = va_arg(vl, char*);
            i++;
        } while (arg != nullptr);
        va_end(vl);
        int size = i;
        i = 0;
        string line = "let's start !";
        while (size != 0) {
            if (i > size - 1) {
                i = 0;
            }
            line = readerList[i].readln();
            if (line == "") {
                readerList[i].close();
                readerList.erase(readerList.begin() + i);
                size -= 1;
            } else {
                outputStream.writeln(line);
            }
            i++;
        }
        outputStream.close();
    }


};


#endif //INFO_H417_GROUP_15_EXPERIMENT3_H
