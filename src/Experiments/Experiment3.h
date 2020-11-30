#ifndef INFO_H417_GROUP_15_EXPERIMENT3_H
#define INFO_H417_GROUP_15_EXPERIMENT3_H


#include <OutputStreams/OutputStream4.h>
#include <InputStreams/InputStream4.h>
#include <OutputStreams/OutputStream3.h>
#include <InputStreams/InputStream3.h>
#include <OutputStreams/OutputStream2.h>
#include <InputStreams/InputStream2.h>
#include "Chrono.h"
#include <vector>
#include <type_traits>
class Experiment3 {
public:
    Experiment3() {
    }
     template<class InputClass,class OutputClass> void rrmerge11 (char *fileName, ...)
     {
        vector<InputClass> readerList;
        OutputClass outputStream("experiment3.txt");
        outputStream.create();
        va_list vl;
        va_start(vl,fileName);
        char* arg = fileName;
        int i = 0;
        do{
            if(std::is_same<InputClass, InputStream3>::value){
                InputClass inputStream(arg,5);
                readerList.push_back(inputStream);
            }
            else{
                InputClass inputStream(arg,5);
                readerList.push_back(inputStream);
            }

            readerList[i].open();
            arg = va_arg(vl, char*);
            i++;
        } while(arg != NULL );
        va_end(vl);
        int size = i;
        i=0;
        string line = "let's start !";
        while (size !=0) {
            if(i>size-1){
                i=0;
            }
            line = readerList[i].readln();
            if(line == ""){
                readerList[i].close();
                readerList.erase(readerList.begin()+i);
                size-=1;
            }
            else{
                outputStream.writeln(line);
            }
            i++;
        }
        outputStream.close();
    }


};


#endif //INFO_H417_GROUP_15_EXPERIMENT3_H
