#include "OutputStream.h"
#include <string>
#include <utility>

using namespace std;

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream::OutputStream(string fName) {
    fileName = move(fName);
}
/**
 * Creates a file and stores it in the file field of the OutputStream class.
 */
void OutputStream::create() {
    file = ofstream(fileName);
}
/**
 * Write a string in the file of the OutputStream class and and terminate
 * this stream with the newline character using the write system calls.
 * @param  text : string to be written in the file
 */
void OutputStream::writeln(string text) {
    text = text + "\n";
    file.write( (char *) &text, sizeof(text) );
}
/**
 * Closes the file.
 */
void OutputStream::close() {
    file.close();
}


