#include "InputStream.h"
#include <string>
#include <utility>
#include <io.h>
#include <cstring>


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
 * Read the next line from the stream by reading one character at a time
 * using the read system calls until the end-of-line symbol is reached.
 */
char *InputStream::readln1() {
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
            break;
        }
        lineBuffer[count] = c;
        count++;
    }
    lineBuffer[count] = '\0';
    return lineBuffer;
}

void InputStream::readln2() {
    char str[128];
    int B = 256;
    if (fgets(str, B, file) != NULL) {
        puts(str);
    }
}

char *InputStream::readln3() {
    char *lineBuffer = (char *) malloc(sizeof(char *));
    read(fileno(file), &lineBuffer, sizeof(lineBuffer));
    lineBuffer = lineBuffer;
    return lineBuffer;
}