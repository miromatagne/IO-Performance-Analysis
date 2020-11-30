#include "OutputStream2.h"
#include <string.h>
#include <stdio.h>
/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream2::OutputStream2(char *fName) : OutputStream(fName){
}


/**
 * Write a string in the file of the OutputStream class and terminate
 * this stream with the newline character using fputs functions from the
 * C stdio library.
 * @param  text : string to be written in the file
 */
void OutputStream2::writeln(string text) const{

    if (fputs((text+"\n").c_str(), file) < 0)
    {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while writing in file: %s\n", strerror( err ));
    }
}



