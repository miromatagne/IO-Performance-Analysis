#include "OutputStream.h"
#include <string>


/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 * @param B : Size of the buffer
 */
OutputStream::OutputStream(char *fName,int B) {
    fileName = fName;
    BufferSize = B;
}

/**
 * Creates a file and stores it in the file field of the OutputStream class.
 */
void OutputStream::create() {
    file = fopen(fileName, "w");
}

/**
 * Closes the file.
 */
void OutputStream::close() {
    fclose(file);
}

