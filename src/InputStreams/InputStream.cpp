//
// Created by minhx on 30-11-20.
//

#include "InputStream.h"
#include <io.h>
#include <iostream>

using namespace std;

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream::InputStream(char *fName) {
    fileName = fName;
}

/**
 * Opens the file and stores it in the file field of the InputStream class.
 */
void InputStream::open() {
    file = fopen(fileName, "r");
}

/**
 * Closes the file.
 */

void InputStream::close() {
    fclose(file);
}

/**
 * Moves the cursor of the file to a certain position specified by the user.
 * @param pos : desired position of the cursor
 */
void InputStream::seek(int pos) {
    fseek(file, pos, SEEK_SET);
}

/**
 * Returns the file
 */
FILE * InputStream::getFile() {
    return file;
}

/*int InputStream::sizeFile() {
    fseek(file, 0, SEEK_END);
    int sizeByteFile = ftell(file) * sizeof(char);
    rewind(file);
    fseek(file, 0, SEEK_SET);
    return sizeByteFile;
}*/