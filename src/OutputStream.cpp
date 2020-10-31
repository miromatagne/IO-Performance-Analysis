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
    char* c = const_cast<char*>(text.c_str());
    write(fileno(*file),c,sizeof(c)); // ici c la fonction write casse couille. fileno()  c une fonction pour avoir le file descriptor mais on a besoin d'un pointeur FILE* pour l'utiliser (faut du C pour l'avoir)
}    //
    // ce qu'il faut c pouvoir recup le file descriptor en c++
/**
 * Closes the file.
 */
void OutputStream::close() {
    file.close();
}


