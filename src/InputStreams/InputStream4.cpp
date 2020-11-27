#include "InputStream4.h"

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <string>
#include <cmath>

using namespace std;

extern int errno;

#define SIZE_BUFFER 1000

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream4::InputStream4(char *fName, int bufSize) {
    fileName = fName;
    B = bufSize;
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    start_file = 0;
    start = 0;
    sizePageBuffer = info.dwAllocationGranularity *
                     ceil((double) SIZE_BUFFER * sizeof(char) / (double) info.dwAllocationGranularity);
    save = 0;
    fseek(file, 0L, SEEK_END);
    sizeByteFile = ftell(file) * sizeof(char);
    rewind(file);
    fseek(file, save, SEEK_SET);
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
    map(sizePageBuffer);
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
 * Map a region into memory
 */
void InputStream4::map(int toMap) {
    /*
    cout << "my end" << end << endl;
    cout << "start" << start << endl;
    cout << "to Map" << toMapWrite << endl;
     */

    hMapFile = CreateFileMapping(
            hFile,    // use paging file
            NULL,                    // default security
            PAGE_READONLY,
            0,
            start+toMap,
            _T("INFO-H417"));                 // name of mapping object

    if (hMapFile == NULL) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of CreateFileMapping function: %s\n", strerror(err));
    }

    readBuffer = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                         FILE_MAP_READ, // read/write permission
                                         0,
                                         start,
                                         toMap); //null

    if (readBuffer == NULL) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of the MapViewOfFile function: %s\n", strerror(err));
        //CloseHandle(hMapFile);
        exit(4);
    }
}

/**
 * Unmap a region from memory
 */
void InputStream4::unmap() {
    UnmapViewOfFile(readBuffer);
    CloseHandle(hMapFile);
}

/**
 * Read the next line from the file of the InputStream class by mapping the characters
 * into internal memory through memory mapping.
 */
string InputStream4::readln() {
    int index = 0;
    save = ftell(file);
    start_file = save*sizeof(char);
    buffer = new char[B];
    strncpy(buffer, (char*) readBuffer, B);
    string currentLine = "";

    for (int i = index; i < sizeof(buffer), i++) {
        if (buffer[i] == '\n') {

        }

    }

    return currentLine;
}