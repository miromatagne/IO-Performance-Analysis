#include "OutputStream3.h"
#include <string>
#include <io.h>

#define SIZE_BUFFER 10
/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream3::OutputStream3(char *fName, int B): OutputStream(fName,B) {
}

/**
 * Write a string in the file of the OutputStream class trough a buffer
 * in internal memory and terminate this stream with the newline character.
 * @param  text : string to be written in the file
 */
void OutputStream3::writeln(string text) const {
    text += "\n";
    const char *c = text.c_str();

    char buffer[SIZE_BUFFER];
    int size = strlen(c);
    int start = 0;
    if (size <= SIZE_BUFFER) {
        strcpy(buffer, c);
        write(fileno(file), buffer, size);
    } else {
        while ((start + SIZE_BUFFER) < size) {
            strncpy(buffer, c + start, SIZE_BUFFER);
            write(fileno(file), buffer, SIZE_BUFFER);
            start += SIZE_BUFFER;
        }
        strncpy(buffer, c + start, (size - start));
        write(fileno(file), buffer, (size - start));
    }

}

