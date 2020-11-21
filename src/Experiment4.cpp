#include <iostream>
#include <cstring>
#include "Experiment4.h"
#include <cstdarg>

Experiment4::Experiment4() {
}


void Experiment4::rrmerge (char *fileName, ...)
{
    va_list vl;
    va_start(vl,fileName);
    char* arg = fileName;
    do{
        arg = va_arg(vl, char*);
    } while(arg != NULL);

    va_end(vl);
}
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