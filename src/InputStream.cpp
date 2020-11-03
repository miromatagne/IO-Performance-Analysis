#include "InputStream.h"
#include <string>
#include <utility>
#include <io.h>
#include <cstring>


using namespace std;
extern int errno;

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
 * Read the next line from the file of the InputStream by reading one character at a time
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

/**
 * Read the next line from the file of the InputStream
 * using fgets function from the C stdio library.
 */
void InputStream::readln2() {
    char str[128];
    int n = 256;
    if (fgets(str, n, file) != NULL) {
        puts(str);
    }
    else {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while writing in file: %s\n", strerror( err ));
    }
}

/**
 * Read the next line from the file of the InputStream
 * through a buffer in internal memory using the read
 * system calls until the end-of-line symbol is reached.
 */
char *InputStream::readln3() {
    int sizeB = 512;
    char *lineBuffer2 = (char *) calloc(1, sizeB);
    read(fileno(file), lineBuffer2, sizeof(lineBuffer2));
    lineBuffer2 += '\0';
    return lineBuffer2;
}

/**
 * Read the next line from the file of the InputStream
 * through a buffer in internal memory using the read
 * system calls until the end-of-line symbol is reached.
 */
