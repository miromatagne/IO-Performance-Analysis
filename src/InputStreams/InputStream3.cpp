//
// Created by Miro-Manuel on 26/11/2020.
//

#include <io.h>
#include <string>
#include "InputStream3.h"

using namespace std;

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream3::InputStream3(char *fName, int B) : InputStream(fName, B) {
    index = 0;
}


/**
 * Read the next line from the file of the InputStream
 * through a buffer in internal memory using the read
 * system calls until the end-of-line symbol is reached.
 */
string InputStream3::readln() {
    int bufferLength = 0;
    if (buffer == nullptr) {
        buffer = new char[BufferSize];
        bufferLength = readToBuffer();
        if (bufferLength == 0) {
            return "";
        }
    }
    string currentLine = "";
    bool run = true;
    while (run) {
        for (int i = index; i < bufferLength; i++) {
            if (buffer[i] == '\n') {
                currentLine.push_back(buffer[i]);
                index = i + 1;
                run = false;
                break;
            }
            currentLine.push_back(buffer[i]);
        }
        if (run) {
            bufferLength = readToBuffer();
            if (bufferLength == 0) {
                return currentLine;
            }
        }
    }
    return currentLine;
}

int InputStream3::readToBuffer() {
    int nbChar = read(fileno(file), buffer, BufferSize);
    index = 0;
    return nbChar;
}

/**
 * Moves the cursor of the file to a certain position specified by the user.
 * @param pos : desired position of the cursor
 */
void InputStream3::seek(int pos) {
    fseek(file, pos, SEEK_SET);
    buffer = nullptr;
}