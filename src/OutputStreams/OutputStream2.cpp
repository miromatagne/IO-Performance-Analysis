#include "OutputStream2.h"
/**
 * Call the parent's constructor
 * @param fName : string corresponding to the filename the user chose
 * @param B : Size of the buffer
 */
OutputStream2::OutputStream2(char *fName,int B) : OutputStream(fName,B){
}


/**
 * Write a string in the file of the OutputStream class and terminate
 * this stream with the newline character using fputs functions from the
 * C stdio library.
 * @param  text : string to be written in the file
 */
void OutputStream2::writeln(string text){

    if (fputs((text).c_str(), file) < 0)
    {
        printf("error while writing");
    }
}



