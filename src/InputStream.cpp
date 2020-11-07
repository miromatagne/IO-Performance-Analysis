#include "InputStream.h"
#include <string>
#include <utility>
#include <io.h>
#include <cstring>
#include <iostream>


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
        if (c != '\n') {
            lineBuffer[count] = c;
            count++;
        }
    }
    lineBuffer[count] = '\0';
    return lineBuffer;
}

/**
 * Read the next line from the file of the InputStream
 * using fgets function from the C stdio library.
 */
char *InputStream::readln2() {
    int n = 256;
    char *result = (char *) malloc(n * sizeof(char));
    char *response = fgets(result, n, file);
    int i = 1;
    while (strlen(result) >= (n - 1) * i) {
        result = (char *) realloc(result, n);
        response = fgets(result, (i + 1) * n, file);
        i++;
    }
    if (response == nullptr) {
        return nullptr;
    }
    strtok(result, "\n");
    if (result != NULL) {
        return result;
    } else {
        return nullptr;
    }
}

/**
 * Read the next line from the file of the InputStream
 * through a buffer in internal memory using the read
 * system calls until the end-of-line symbol is reached.
 */
char *InputStream::readln3() {
    int sizeB = 200;
    char *lineBuffer = (char *) malloc(sizeB + 1);
    char *line = (char *) malloc(sizeB);
    int nbChar = read(fileno(file), lineBuffer, sizeB);
    if (nbChar == 0) {
        return nullptr;
    }
    lineBuffer[nbChar] = '\0';
    strcpy(line, lineBuffer);
    int i = 2;
    char *firstOcc;
    while ((firstOcc = strstr(line, "\n")) == NULL && nbChar == sizeB * (i - 1)) {
        line = (char *) realloc(line, i * sizeB + 1);
        line[nbChar] = '\0';
        int nbRead = read(fileno(file), lineBuffer, sizeB);
        nbChar += nbRead;
        lineBuffer[nbRead] = '\0';
        strcat(line, lineBuffer);
        i++;
    }
    int position = strlen(line);
    if (firstOcc != 0) {
        position = firstOcc - line;
    }
    char *resultLine = (char *) malloc(nbChar + 1);
    memcpy(resultLine, line, position);
    resultLine[position] = '\0';
    fseek(file, position - strlen(line) + 1, SEEK_CUR);
    free(line);
    free(lineBuffer);
    return resultLine;
}

