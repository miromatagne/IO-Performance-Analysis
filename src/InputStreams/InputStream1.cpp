#include <io.h>
#include <iostream>
#include "InputStream1.h"

using namespace std;

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream1::InputStream1(char *fName) {
    fileName = fName;
}

/**
 * Opens the file and stores it in the file field of the InputStream class.
 */
void InputStream1::open() {
    file = fopen(fileName, "r");
}

/**
 * Closes the file.
 */

void InputStream1::close() {
    fclose(file);
}

/**
 * Moves the cursor of the file to a certain position specified by the user.
 * @param pos : desired position of the cursor
 */
void InputStream1::seek(int pos) {
    fseek(file, pos, SEEK_SET);
}

/**
 * Read the next line from the file of the InputStream by reading one character at a time
 * using the read system calls until the end-of-line symbol is reached.
 */
char *InputStream1::readln() {
    int count = 1;
    int maxLineLength = 128;
    char *lineBuffer = (char *) malloc(maxLineLength * sizeof(char));
    char c;

    if (read(fileno(file), &c, sizeof(c)) == 0) {
        return nullptr;
    }
    lineBuffer[0] = c;
    while (c != '\n') {
        if (count == maxLineLength) {
            maxLineLength += 128;
            lineBuffer = (char *) realloc(lineBuffer, maxLineLength);
        }
        if (read(fileno(file), &c, sizeof(c)) == 0) {
            count++;
            break;
        }
        if (c != '\n') {
            lineBuffer[count] = c;
            count++;
        }
    }
    lineBuffer[count] = '\0';
    return lineBuffer;
}