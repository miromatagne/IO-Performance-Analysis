//
// Created by minhx on 30-11-20.
//

#include "OutputStream.h"

#include <string>
#include <io.h>


/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream::OutputStream(char *fName) {
    fileName = fName;
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

