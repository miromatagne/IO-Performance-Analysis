#include "OutputStream3.h"
#include <io.h>
#include <cstring>

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream3::OutputStream3(char *fName, int B) : OutputStream(fName, B) {
    buffer = new char[BufferSize];
    index=0;
}

/**
 * Write a string in the file of the OutputStream class trough a buffer
 * in internal memory and terminate this stream with the newline character.
 * @param  text : string to be written in the file
 */
void OutputStream3::writeln(string text){
    const char *c = text.c_str();
    int start = 0;
    int remaining = strlen(c);
    int size = strlen(c);
    if (size+index < BufferSize) {
        strcpy(buffer+index, c);
        index+=size;
    } else {
        while (( BufferSize ) <= remaining+index) {
            strncpy(buffer+index, c + start, BufferSize-index);
            remaining-=(BufferSize-index);
            write(fileno(file), buffer, BufferSize);
            start += BufferSize-index;
            index=0;
        }
        strncpy(buffer, c + start, remaining);
        index=remaining;
    }

}
/**
 * Closes the file.
 */
void OutputStream3::close() {
    write(fileno(file), buffer, index);
    fclose(file);
}




