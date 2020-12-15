#include <io.h>
#include <iostream>
#include "InputStream1.h"

using namespace std;

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream1::InputStream1(char *fName,int B) : InputStream(fName,B) {
}


/**
 * Read the next line from the file of the InputStream by reading one character at a time
 * using the read system calls until the end-of-line symbol is reached.
 */
string InputStream1::readln() {
    string lineBuffer = "";
    char c;
    if (read(fileno(file), &c, 1) == 0) {
        return "";
    }
    if (c != '\n') {
        lineBuffer.push_back(c);
    }
    else {
        lineBuffer.push_back(c);
        return lineBuffer;
    }
    while (c != '\n') {
        if (read(fileno(file), &c, sizeof(c)) == 0) {
            break;
        }
        lineBuffer.push_back(c);
    }
    return lineBuffer;
}

string InputStream1::getNumber() {
    string str(fileName);
    return str;
}