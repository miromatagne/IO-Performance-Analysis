#include <iostream>
#include <cstring>
#include "Experiment3.h"
#include <cstdarg>
#include <OutputStreams/OutputStream1.h>
#include <OutputStreams/OutputStream2.h>
#include <OutputStreams/OutputStream3.h>
#include <OutputStreams/OutputStream4.h>
#include <InputStreams/InputStream4.h>
#include <InputStreams/InputStream3.h>
#include <InputStreams/InputStream2.h>
#include <InputStreams/InputStream1.h>
#include <vector>
Experiment3::Experiment3() {
}

void Experiment3::rrmerge11 (char *fileName, ...)
{
    vector<InputStream4> readerList;
    OutputStream4 outputStream("experiment3.txt");
    outputStream.create();
    va_list vl;
    va_start(vl,fileName);
    char* arg = fileName;
    int i = 0;
    do{

        InputStream4 inputStream(arg,5);
        readerList.push_back(inputStream);
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

/*
void Experiment3::rrmerge11 (char *fileName, ...)
{
    va_list vl;
    va_start(vl,fileName);
    char* arg = fileName;
    while(arg != NULL){
        arg = va_arg(vl, char*);
        cout << "a" << endl;
    }

    va_end(vl);
}
 */

/*
void FindMax (char *n, ...)
{
  int i,val;
  va_list vl;
  va_start(vl,n);
  char* arg = n;
  i=0;
  while(arg != NULL){
  arg = va_arg(vl, char*);
  i++;
  printf("%d ",i);

  }
  va_end(vl);
}

int main ()
{
  int m;
  FindMax ("ok","caca","boudin","truc","pepe");

  return 0;
}
 */