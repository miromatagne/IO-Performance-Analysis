//
// Created by Miro-Manuel on 26/11/2020.
//

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <io.h>
#include <string>
#include <iostream>
#include "InputStream3.h"

using namespace std;

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
string InputStream3::readln() {
    if (buffer == nullptr) {
        buffer = new char[B];
        bufferLength = readToBuffer();
        if (bufferLength == 0) {
            return nullptr;
        }
    }
    char *firstOcc;
    string currentLine = "";
    bool run = true;
    while (run) {
        for (int i = index; i < bufferLength; i++) {
            if (buffer[i] == '\n') {
                index = i + 1;
                run = false;
                break;
            }
//            cout << "currentLine: " << currentLine << endl;
//            cout << "buffer: " << buffer << endl;
//            cout << "i: " << i << endl;
//            cout << "buffer[i]: " << buffer[i] << endl;
//            cout << bufferLength << endl;
            currentLine.push_back(buffer[i]);
//            if ((i == bufferLength - 1) && (bufferLength != B)) {
//                run = false;
//                break;
//            }
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
    int nbChar = read(fileno(file), buffer, B);
    index = 0;
//    cout << "nbChar :" << nbChar << endl;
//    cout << "buffer :" << buffer << endl;
    return nbChar;
}