#include <io.h>
#include <iostream>
#include "InputStream2.h"
#include <stdio.h>
#include <string.h>

using namespace std;

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream2::InputStream2(char *fName) : InputStream(fName) {
}

/**
 * Read the next line from the file of the InputStream
 * using fgets function from the C stdio library.
 */
string InputStream2::readln() {
    int n = 100;
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

}