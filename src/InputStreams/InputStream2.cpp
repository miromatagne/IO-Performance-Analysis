#include "InputStream2.h"
#include <cstring>

using namespace std;

/**
 * Call the parent's constructor and initialize attributes
 * @param fName : string corresponding to the filename the user chose
 * @param B : Size of the buffer
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
            return line;
        }
    }

    return line;
}


/**
 * Closes the file.
 */
void InputStream2::close() {
    free(line);
    fclose(file);
}

