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
InputStream3::InputStream3(char *fName, int B) : InputStream(fName,B) {
    index = 0;
}


/**
 * Read the next line from the file of the InputStream
 * through a buffer in internal memory using the read
 * system calls until the end-of-line symbol is reached.
 */
string InputStream3::readln() {

    if (buffer == nullptr) {
        buffer = new char[BufferSize];
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
            //cout << "index : " << index << endl;
            //cout << "length : "<< bufferLength << endl;
            if (buffer[i] == '\n') {
                currentLine.push_back(buffer[i]);
                index = i + 1;
                run = false;
                //cout << "ok" << endl;
                break;
            }
            currentLine.push_back(buffer[i]);
        }
        if (run) {
            bufferLength = readToBuffer();
            //cout << "buffer : " << buffer << endl;
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
//    cout << "nbChar :" << nbChar << endl;
//    cout << "buffer :" << buffer << endl;
    return nbChar;
}