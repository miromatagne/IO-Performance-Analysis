#include <io.h>
#include <iostream>
#include "InputStream2.h"
#include <cstdio>
#include <cstring>

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
    if (response == nullptr) {
        return "";
    }
    string lineString(result);
    while (lineString.length() >= n * i - 1) {
        cout << "line: " << lineString << endl;
        response = fgets(result, n, file);
        string temp(result);
        lineString += temp;
        i++;
        if (response == nullptr) {
            return "";
        }
    }
    string res = lineString;
    char c = lineString[lineString.size() - 1];
    if ((int) c == 10) {
        res = lineString.substr(0, lineString.size() - 1);
    }
    free(result);
    return res;

}
