#include "OutputStream.h"
#include <string>
#include <utility>
#include <io.h>
#include <cstring>

using namespace std;

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream::OutputStream(const char* fName) {
    fileName = move(fName);
}
/**
 * Creates a file and stores it in the file field of the OutputStream class.
 */
void OutputStream::create() {
    file = fopen(fileName,"w");
}
/**
 * Write a string in the file of the OutputStream class and and terminate
 * this stream with the newline character using the write system calls.
 * @param  text : string to be written in the file
 */
void OutputStream::writeln(string text) {
    text+="\n";
    char* c = const_cast<char*>(text.c_str());
    write(fileno(file),c,strlen(c));
}

/**
 * Closes the file.
 */
void OutputStream::close() {
    fclose(file);
}


