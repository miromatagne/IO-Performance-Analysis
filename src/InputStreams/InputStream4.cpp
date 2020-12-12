//
// Created by Linho100 on 27/11/2020.
//
#include "InputStream4.h"

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <string>
#include <cmath>
#include <io.h>

using namespace std;

extern int errno;


/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream4::InputStream4(char *fName, int B) : InputStream(fName, B) {
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    start_file = 0;
    start = 0;
    sizePageBuffer = info.dwAllocationGranularity *
                     ceil((double) BufferSize * sizeof(char) / (double) info.dwAllocationGranularity);
}


/**
 * Opens the file and stores it in the file field of the InputStream class.
 */
void InputStream4::open() {
    rhFile = CreateFile(_T(fileName), GENERIC_READ, 0, NULL, OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL, NULL);
    if (rhFile == INVALID_HANDLE_VALUE) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror(err));
    }
    fd = _open_osfhandle((intptr_t) rhFile, _O_RDONLY);
    if (fd == -1) {
        ::CloseHandle(rhFile);
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror(err));
    }
    file = _fdopen(fd, "r");
    if (!file) {
        ::CloseHandle(rhFile);
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror(err));
    }


    fseek(file, 0L, SEEK_END);
    sizeByteFile = ftell(file) * sizeof(char);
    rewind(file);
    if (sizeByteFile < sizePageBuffer) {
        map(sizeByteFile);
    } else {
        map(sizePageBuffer);
    }

}

/**
 * Closes the file.
 */
void InputStream4::close() {
    unmap();
    fclose(file);
}


/**
 * Map a region into memory
 */
void InputStream4::map(DWORD toMap) {
    DWORD end = 0;
    if (start + toMap > sizeByteFile) {
        end = 0;
        toMap = NULL;
    } else {
        end = start + toMap;
    }
    rhMapFile = CreateFileMapping(
            rhFile,    // use paging file
            NULL,                    // default security
            PAGE_READONLY,
            0,
            end,
            _T(fileName));                 // name of mapping object

    if (rhMapFile == NULL) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of CreateFileMapping function: %s\n", strerror(err));
    }

    readBuffer = (LPTSTR) MapViewOfFile(rhMapFile,   // handle to map object
                                        FILE_MAP_READ, // read/write permission
                                        0,
                                        start,
                                        toMap); //null

    if (readBuffer == NULL) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of the MapViewOfFile function: %s\n", strerror(err));
        CloseHandle(rhMapFile);
    }
}

/**
 * Unmap a region from memory
 */
void InputStream4::unmap() {
    UnmapViewOfFile(readBuffer);
    CloseHandle(rhMapFile);
}


/**
 * Read the next line from the file of the InputStream class by mapping the characters
 * into internal memory through memory mapping.
 */
string InputStream4::readln() {
    string currentLine = "";
    bool run = true;
    while (run) {
        for (int i = (start_file - start); i < sizePageBuffer; i++) {
            if (readBuffer[i] == '\n') {
                currentLine[currentLine.length()-1]=readBuffer[i];
                start_file += 1;
                run = false;
                break;
            }
            else if (start_file >= sizeByteFile){
                start_file += 1;
                run = false;
                break;
            }
            currentLine.push_back(readBuffer[i]);
            start_file += 1;

        }
        if (run) {
            start += sizePageBuffer;
            unmap();
            map(sizePageBuffer);
            if (readBuffer[0] == NULL) {
                return currentLine;
            }
        }
    }
    return currentLine;
}