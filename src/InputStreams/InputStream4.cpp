#include "InputStream4.h"

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <string>

using namespace std;

extern int errno;

#define SIZE_BUFFER 3

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream4::InputStream4(char *fName, int bufSize) {
    fileName = fName;
    B = bufSize;
}

/**
 * Opens the file and stores it in the file field of the InputStream class.
 */
void InputStream4::open() {

    //file = fopen(fileName, "r");
    hFile = CreateFile(_T(fileName), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror(err));
    }
    fd = _open_osfhandle((intptr_t) hFile, _O_RDONLY);
    if (fd == -1) {
        ::CloseHandle(hFile);
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror(err));
    }
    file = _fdopen(fd, "r");
    if (!file) {
        ::CloseHandle(hFile);
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror(err));
    }
}

/**
 * Closes the file.
 */
void InputStream4::close() {
    fclose(file);
}

/**
 * Moves the cursor of the file to a certain position specified by the user.
 * @param pos : desired position of the cursor
 */
void InputStream4::seek(int pos) {
    fseek(file, pos, SEEK_SET);
}

/**
 * Read the next line from the file of the InputStream class by mapping the characters
 * into internal memory through memory mapping.
 */
char *InputStream4::readln() {


}