#include "InputStream.h"
#include <io.h>
#include <windows.h>

#include <tchar.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>


using namespace std;

extern int errno;

#define SIZE_BUFFER 3

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the InputStream class
 * @param fName : string corresponding to the filename the user chose
 */
InputStream::InputStream(char *fName) {
    fileName = fName;
}

/**
 * Opens the file and stores it in the file field of the InputStream class.
 */
void InputStream::open() {

    file = fopen(fileName, "r");
    hFile = (HANDLE) _get_osfhandle(_fileno(file));
    fd = _open_osfhandle((intptr_t) hFile, _O_RDONLY);
    if (fd == -1) {
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
void InputStream::close() {
    fclose(file);
}

/**
 * Moves the cursor of the file to a certain position specified by the user.
 * @param pos : desired position of the cursor
 */
void InputStream::seek(int pos) {
    fseek(file, pos, SEEK_SET);
}

/**
 * Read the next line from the file of the InputStream by reading one character at a time
 * using the read system calls until the end-of-line symbol is reached.
 */
char *InputStream::readln1() {
    int count = 1;
    int maxLineLength = 128;
    char *lineBuffer = (char *) malloc(maxLineLength * sizeof(char));
    char c;

    if (read(fd, &c, sizeof(c)) == 0) {
        return nullptr;
    }
    lineBuffer[0] = c;
    while (c != '\n') {
        if (count == maxLineLength) {
            maxLineLength += 128;
            lineBuffer = (char *) realloc(lineBuffer, maxLineLength);
        }
        if (read(fd, &c, sizeof(c)) == 0) {
            count++;
            break;
        }
        if (c != '\n') {
            lineBuffer[count] = c;
            count++;
        }
    }
    lineBuffer[count - 1] = '\0';
    return lineBuffer;
}

/**
 * Read the next line from the file of the InputStream
 * using fgets function from the C stdio library.
 */
char *InputStream::readln2() {
    int n = 256;
    char *result = (char *) malloc(n * sizeof(char));
    char *response = fgets(result, n, file);
    int i = 1;
    while (strlen(result) >= (n - 1) * i) {
        result = (char *) realloc(result, n);
        response = fgets(result, (i + 1) * n, file);
        i++;
    }
    if (response == nullptr) {
        return nullptr;
    }
    strtok(result, "\n");
    if (result != NULL) {
        return result;
    } else {
        return nullptr;
    }
}

/**
 * Read the next line from the file of the InputStream
 * through a buffer in internal memory using the read
 * system calls until the end-of-line symbol is reached.
 */
char *InputStream::readln3() {
    int sizeB = 10;
    char *lineBuffer = (char *) malloc(sizeB + 1);
    char *line = (char *) malloc(sizeB);
    int nbChar = read(fd, lineBuffer, sizeB);
    if (nbChar == 0) {
        return nullptr;
    }
    lineBuffer[nbChar] = '\0';
    strcpy(line, lineBuffer);
    int i = 2;
    char *firstOcc;
    while ((firstOcc = strstr(line, "\n")) == NULL && nbChar == sizeB * (i - 1)) {
        line = (char *) realloc(line, i * sizeB + 1);
        line[nbChar] = '\0';
        int nbRead = read(fd, lineBuffer, sizeB);
        nbChar += nbRead;
        lineBuffer[nbRead] = '\0';
        strcat(line, lineBuffer);
        i++;
    }
    int position = strlen(line);
    if (firstOcc != 0) {
        position = firstOcc - line;
    }
    char *resultLine = (char *) malloc(nbChar + 1);
    memcpy(resultLine, line, position);
    if (firstOcc == NULL) {
        resultLine[position] = '\0';
    } else {
        resultLine[position - 1] = '\0';
    }
    fseek(file, position - strlen(line) + 1, SEEK_CUR);
    free(line);
    free(lineBuffer);
    return resultLine;
}

/**
 * Read the next line from the file of the InputStream class by mapping the characters
 * into internal memory through memory mapping.
 */
char *InputStream::readln4() {
    int sizeLine = 10;  //Arbitrary
    char *lineBuffer = (char *) malloc(sizeLine + 1);
    //int sizeByteSource;
    int nbChar = read(fd, lineBuffer, sizeLine);
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    DWORD sizePageBuffer = info.dwAllocationGranularity *
                           ceil((double) SIZE_BUFFER * sizeof(char) / (double) info.dwAllocationGranularity);
    //int nbExtension=ceil((double)sizeByteSource/(double)sizePageBuffer);

    HANDLE hMapFile;
    //char buffer[sizePageBuffer];
    DWORD start = sizePageBuffer;
    int i = 1;
    int end = 2 * sizePageBuffer;
    int toMapWrite = sizePageBuffer;
    //int lastPage = sizeByteSource - ((nbExtension-1)*sizePageBuffer);
    LPCTSTR readBuffer;

    hMapFile = CreateFileMapping(
            hFile,    // use paging file
            NULL,                    // default security
            PAGE_READONLY,
            0,
            sizePageBuffer,                //end
            _T("INFO-H417-Read"));                 // name of mapping object
    if (hMapFile == NULL) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of CreateFileMapping function: %s\n", strerror(err));
    }
    readBuffer = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                        FILE_MAP_ALL_ACCESS, // read/write permission
                                        0,
                                        0,              //start
                                        toMapWrite); //null

    if (readBuffer == NULL) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of the MapViewOfFile function: %s\n", strerror(err));
        CloseHandle(hMapFile);
    }
    strncpy(lineBuffer, readBuffer, toMapWrite);
    UnmapViewOfFile(readBuffer);
    CloseHandle(hMapFile);

    while (strstr((char *) readBuffer, "\n") == NULL) {
        lineBuffer = (char *) realloc(lineBuffer, sizeLine);


        hMapFile = CreateFileMapping(
                hFile,    // use paging file
                NULL,                    // default security
                PAGE_READONLY,
                0,
                end,
                _T("INFO-H417-Read"));                 // name of mapping object

        if (hMapFile == NULL) {
            int err = errno;
            fprintf(stderr, "Value of errno: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error of CreateFileMapping function: %s\n", strerror(err));
        }

        readBuffer = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                            FILE_MAP_ALL_ACCESS, // read/write permission
                                            0,
                                            start,
                                            toMapWrite); //null

        if (readBuffer == NULL) {
            int err = errno;
            fprintf(stderr, "Value of errno: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error of the MapViewOfFile function: %s\n", strerror(err));
            CloseHandle(hMapFile);

        }
        strncpy(lineBuffer, readBuffer + start, toMapWrite);
        UnmapViewOfFile(readBuffer);
        CloseHandle(hMapFile);
        start += sizePageBuffer;
        end = start + sizePageBuffer;
        i++;
    }
    lineBuffer[i * toMapWrite + 1] = '\n';
    return lineBuffer;
}