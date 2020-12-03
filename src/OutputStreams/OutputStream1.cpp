
#include "OutputStream1.h"
#include <string>
#include <io.h>
#include <iostream>

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream1::OutputStream1(char *fName,int B) : OutputStream(fName,B) {
}


/**
 * Write a string in the file of the OutputStream class one character at a time and terminate
 * this stream with the newline character using the write system calls.
 * @param  text : string to be written in the file
 */
void OutputStream1::writeln(string text) const {
    char c = text[0];
    int i = 0;
    while (c != '\0') {
        i++;
        write(fileno(file), &c, sizeof(c));
        c = text[i];
    }
    c = '\n';
    write(fileno(file), &c, sizeof(c));
}
