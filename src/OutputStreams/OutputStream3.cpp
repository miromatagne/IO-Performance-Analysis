#include "OutputStream3.h"
#include <string>
#include <io.h>

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream3::OutputStream3(char *fName, int B) : OutputStream(fName, B) {
}

/**
 * Write a string in the file of the OutputStream class trough a buffer
 * in internal memory and terminate this stream with the newline character.
 * @param  text : string to be written in the file
 */
void OutputStream3::writeln(string text) const {
    const char *c = text.c_str();
    int size = strlen(c);
    int start = 0;
    if (size <= BufferSize) {
        write(fileno(file), c, size);
    } else {
        while ((start + BufferSize) < size) {
            write(fileno(file), c+start, BufferSize);
            start += BufferSize;
        }
        write(fileno(file), c+start, (size - start));
    }

}

