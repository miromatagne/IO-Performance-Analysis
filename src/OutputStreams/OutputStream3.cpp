#include "OutputStream3.h"
#include <string>
#include <io.h>
#include <iostream>

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
        cout << "INDEX " << index << endl;
        strcpy(buffer+index, c);
        index+=size;
//        write(fileno(file), buffer, size);
    } else {
        while (( BufferSize ) <= remaining+index) {
//            cout << "kaka" << endl;
//            cout << c + start << endl;
            strncpy(buffer+index, c + start, BufferSize-index);
            remaining-=(BufferSize-index);
            write(fileno(file), buffer, BufferSize);
            start += BufferSize-index;
            index=0;
        }

//        cout << "la diff "<<size-start<< endl;
        strncpy(buffer, c + start, remaining);
        index=remaining;
//        cout << c+start+(size - start)-2 << endl;
//        write(fileno(file), buffer, (size - start));
    }

}
/**
 * Closes the file.
 */
void OutputStream3::close() {
    write(fileno(file), buffer, index);
    fclose(file);
}




