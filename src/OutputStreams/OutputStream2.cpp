#include "OutputStream2.h"
#include <string.h>
#include <stdio.h>
/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream2::OutputStream2(const char *fName) {
    fileName = fName;
}

/**
 * Creates a file and stores it in the file field of the OutputStream class.
 */
void OutputStream2::create() {
    file = fopen(fileName,"w");
}


/**
 * Write a string in the file of the OutputStream class and terminate
 * this stream with the newline character using fputs functions from the
 * C stdio library.
 * @param  text : string to be written in the file
 */
void OutputStream2::writeln(string text) const{
    const char* c = (text+"\n").c_str();
    if (fputs(c, file) < 0)
    {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while writing in file: %s\n", strerror( err ));
    }
}
/**
 * Closes the file.
 */
void OutputStream2::close() {
    fclose(file);
}



