#include "InputStream.h"
#include <string>
#include <utility>


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
void InputStream::readln() {
    int count = 0;
    int maxLineLength = 128;
    char *lineBuffer = (char *)malloc(maxLineLength*sizeof(char));
    char c = fgetc(file)
    while((c != '\n') && (c != EOF)) {
        if (count == maxLineLength) {
            maxLineLength += 128;
            lineBuffer = realloc(lineBuffer, maxLineLength);
            if (lineBuffer == NULL) {
                printf("Error reallocating space for line buffer.");
                exit(1);
            }
        lineBuffer[count] = c;
        count++;
        c = getc(file);
    }
    read(fileno(file),lineBuffer, strlen(lineBuffer))
}