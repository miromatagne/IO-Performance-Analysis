#include "InputStream.h"
#include <string>
#include <utility>

using namespace std;

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream::InputStream(string fName) {
    fileName = move(fName);
}

/**
 * Opens the file and stores it in the file field of the InputStream class.
 */
void InputStream::open() {
    file = ifstream(fileName);
}

/**
 * Closes the file.
 */
void InputStream::close() {
    file.close();
}

/**
 * Moves the cursor of the file to a certain position specified by the user.
 * @param pos : desired position of the cursor
 */
void InputStream::seek(int pos) {
    file.seekg(pos);
}
