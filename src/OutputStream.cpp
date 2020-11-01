#include "OutputStream.h"
#include <string>
#include <utility>
#include <cstring>
#include <io.h>

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
void OutputStream::writeln3(string text) {
    text+="\n";
    char* c = const_cast<char*>(text.c_str());
    write(fileno(file),c,strlen(c));
}
/**
 * Write a string in the file of the OutputStream class and and terminate
 * this stream with the newline character using the write system calls.
 * @param  text : string to be written in the file
 */
void OutputStream::writeln1(string text) {
    text+="\n";
    char c = text[0];
    int i = 0;
    while ((c != '\n') && (c != EOF)){
        i++;
        write(fileno(file),&c,sizeof(c));
        c = text[i];
    }

}

/**
 * Closes the file.
 */
void OutputStream::close() {
    fclose(file);
}


