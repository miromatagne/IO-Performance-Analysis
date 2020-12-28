#include <io.h>
#include "InputStream1.h"

using namespace std;

/**
 * Call the parent's constructor
 * @param fName : string corresponding to the filename the user chose
 * @param B : Size of the buffer
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
