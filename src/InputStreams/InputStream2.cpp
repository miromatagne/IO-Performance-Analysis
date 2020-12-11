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
InputStream2::InputStream2(char *fName, int B) : InputStream(fName, B) {
// Store the chunks of text into a line buffer
    len = sizeof(chunk);
    line = (char *) malloc(len);
    if (line == NULL) {
        perror("Unable to allocate memory for the line buffer.");
        exit(1);
    }

}

/**
 * Read the next line from the file of the InputStream
 * using fgets function from the C stdio library.
 */
/*
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
       //cout << "line: " << lineString << endl;
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
*/
/**
 * Read the next line from the file of the InputStream
 * using fgets function from the C stdio library.
 */
string InputStream2::readln() {

// "Empty" the string
    line[0] = '\0';

    while (fgets(chunk, sizeof(chunk), file) != NULL) {
        size_t len_used = strlen(line);
        size_t chunk_used = strlen(chunk);

        if (len - len_used < chunk_used) {
            len *= 2; // 2 times more space (cheaper to do it that way).
            if ((line = (char *) realloc(line, len)) == NULL) {
                perror("Unable to reallocate memory for the line buffer.");
                free(line);
                exit(1);
            }
        }

        strncpy(line + len_used, chunk, len - len_used);
        len_used += chunk_used;

        if (line[len_used - 1] == '\n') {
            // "Empty" the line buffer

            return line;
        }
    }

    return line;
}

void InputStream2::test() {
    while (fgets(chunk, sizeof(chunk), file) != NULL);
}

/**
 * Closes the file.
 */
void InputStream2::close() {
    free(line);
    fclose(file);
}

