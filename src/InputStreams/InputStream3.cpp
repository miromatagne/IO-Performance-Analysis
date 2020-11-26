//
// Created by Miro-Manuel on 26/11/2020.
//

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <io.h>
#include "InputStream3.h"

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream3::InputStream3(char *fName, int bufSize) {
    fileName = fName;
    B = bufSize;
    index = 0;
}

/**
 * Opens the file and stores it in the file field of the InputStream class.
 */
void InputStream3::open() {
    file = fopen(fileName, "r");
}

/**
 * Closes the file.
 */

void InputStream3::close() {
    fclose(file);
}

/**
 * Moves the cursor of the file to a certain position specified by the user.
 * @param pos : desired position of the cursor
 */
void InputStream3::seek(int pos) {
    fseek(file, pos, SEEK_SET);
}

/**
 * Read the next line from the file of the InputStream
 * through a buffer in internal memory using the read
 * system calls until the end-of-line symbol is reached.
 */
char *InputStream3::readln() {
    if (buffer == nullptr) {
        buffer = (char *) malloc(B * sizeof(char) + 1);
        int nbChar = readToBuffer();
        if (nbChar == 0) {
            return nullptr;
        }
    }
    char *firstOcc;
    //char *toReadBuffer = (char *) malloc(B * sizeof(char) + 1);
    //memcpy(toReadBuffer, buffer[], index);
    while ((firstOcc = strstr(toReadBuffer, "\n")) == NULL) {
        int nbChar = readToBuffer();
        if (nbChar == 0) {
            return nullptr;
        }
    }
    line = (char *) realloc(line, i * B + 1);
    line[nbChar] = '\0';
    int nbRead = read(fileno(file), lineBuffer, B);
    nbChar += nbRead;
    lineBuffer[nbRead] = '\0';
    strcat(line, lineBuffer);
    i++;
    char *firstOcc;
    char *line = (char *) malloc(B * sizeof(char) + 1);
    lineBuffer[nbChar] = '\0';
    strcpy(line, lineBuffer);
    int i = 2;
    char *firstOcc = strstr(line, "\n");
    int position = strlen(line);
    if (firstOcc != 0) {
        position = firstOcc - line;
    }
    char *resultLine = (char *) malloc(nbChar + 1);
    memcpy(resultLine, line, position);
    if (firstOcc == NULL) {
        resultLine[position] = '\0';
    } else {
        resultLine[position - 1] = '\0';
    }
    fseek(file, position - strlen(line) + 1, SEEK_CUR);
    free(line);
    free(lineBuffer);
    return resultLine;
}

int InputStream3::readToBuffer() {
    int nbChar = read(fileno(file), buffer, B);
    return nbChar;
}