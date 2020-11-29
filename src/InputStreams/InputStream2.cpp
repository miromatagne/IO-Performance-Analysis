#include <io.h>
#include <iostream>
#include "InputStream2.h"

using namespace std;

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream2::InputStream2(char *fName) {
    fileName = fName;
}

/**
 * Opens the file and stores it in the file field of the InputStream class.
 */
void InputStream2::open() {
    file = fopen(fileName, "r");
}

/**
 * Closes the file.
 */

void InputStream2::close() {
    fclose(file);
}

/**
 * Moves the cursor of the file to a certain position specified by the user.
 * @param pos : desired position of the cursor
 */
void InputStream2::seek(int pos) {
    fseek(file, pos, SEEK_SET);
}

/**
 * Read the next line from the file of the InputStream
 * using fgets function from the C stdio library.
 */
string InputStream2::readln() {
    /*
    int n = 256;
    char *result = (char *) malloc(n * sizeof(char));
    char *response = fgets(result, n, file);
    int i = 1;
    while (strlen(result) >= (n - 1) * i) {
        result = (char *) realloc(result, n * (i + 1));
        response = fgets(result, (i + 1) * n, file);
        i++;
    }
    if (response == nullptr) {
        return "";
    }
    strtok(result, "\n");
    const char c = result[strlen(result) - 1];
    if ((int) c == 13) {
        strtok(result, "\r");
    }
    string str(result);
    return str;
     */
}