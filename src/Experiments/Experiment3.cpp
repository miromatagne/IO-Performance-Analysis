#include <iostream>
#include <cstring>
#include "Experiment3.h"
#include <cstdarg>

Experiment3::Experiment3() {
}


void Experiment3::rrmerge11 (char *fileName, ...)
{
    OutputStream outputStream("experiment3-11.txt");
    outputStream.create();
    va_list vl;
    va_start(vl,fileName);
    char* arg = fileName;
    int i = 0;
    do{

        InputStream inputStream(arg);
        inputStream.open();

        char *line;
        line = inputStream.readln4(5);
        outputStream.writeln4(line);
        while (line != nullptr) {
            line = inputStream.readln4(5);
            if (line == nullptr) {
                break;
            }
            outputStream.writeln4(line);
            free(line);
        }
        inputStream.close();
        i++;
        arg = va_arg(vl, char*);
        cout << i << endl;


    } while(arg != NULL );
    outputStream.close();
    va_end(vl);
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