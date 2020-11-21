#include "OutputStream.h"
#include <io.h>
#include <windows.h>
#include <conio.h>
#include <tchar.h>
#include <fcntl.h>
#include <cmath>
#include <algorithm>
#include <iostream>
//

using namespace std;

extern int errno;

#define SIZE_BUFFER 3

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream::OutputStream(const char *fName) {
    fileName = fName;
}

/**
 * Creates a file and stores it in the file field of the OutputStream class.
 */
void OutputStream::create() {
    hFile = CreateFile(_T(fileName), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror(err));
    }
    fd = _open_osfhandle((intptr_t) hFile, _O_APPEND); //(long) or (intptr_t)
    if (fd == -1) {
        ::CloseHandle(hFile);
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror(err));
    }
    file = _fdopen(fd, "w");
    if (!file) {
        ::CloseHandle(hFile);
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror(err));
    }

}

/**
 * Write a string in the file of the OutputStream class one character at a time and terminate
 * this stream with the newline character using the write system calls.
 * @param  text : string to be written in the file
 */
void OutputStream::writeln1(string text) const {
    char c = text[0];
    int i = 0;
    while (c != '\0') {
        i++;
        write(fd, &c, sizeof(c));
        c = text[i];
    }
    c = '\n';
    write(fd, &c, sizeof(c));
}

/**
 * Write a string in the file of the OutputStream class and terminate
 * this stream with the newline character using fputs functions from the
 * C stdio library.
 * @param  text : string to be written in the file
 */
void OutputStream::writeln2(string text) {
    /*
    char tmp = '\n';
    char c[strlen(text)+2];
    sprintf(c,text);
    int size = strlen(c);
    snprintf(c + size, sizeof c - size, "%c", tmp);
     */
    text += "\n";
    const char *c = text.c_str();
    if (fputs(c, file) < 0) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while writing in file: %s\n", strerror(err));
    }
}

/**
 * Write a string in the file of the OutputStream class trough a buffer
 * in internal memory and terminate this stream with the newline character.
 * @param  text : string to be written in the file
 */
void OutputStream::writeln3(string text) const {
    text += "\n";
    const char *c = text.c_str();

    char buffer[SIZE_BUFFER];
    int size = strlen(c);
    int start = 0;
    if (size <= SIZE_BUFFER) {
        strcpy(buffer, c);
        write(fd, buffer, size);
    } else {
        while ((start + SIZE_BUFFER) < size) {
            strncpy(buffer, c + start, SIZE_BUFFER);
            write(fd, buffer, SIZE_BUFFER);
            start += SIZE_BUFFER;
        }
        strncpy(buffer, c + start, (size - start));
        write(fd, buffer, (size - start));
    }

}
/**
 * Write a string in the file of the OutputStream class by mapping the characters
 * into internal memory through memory mapping and terminate this stream with
 * the newline character.
 * @param  text : string to be written in the file
 */
// com juste pr pouvoir commit
void OutputStream::writeln4(string text) {
    text += "\n";
    const char *c = text.c_str();
    int sizeByteSource = strlen(c) * sizeof(c[0]);
    //adaption du SIZE_BUFFER en nombre de bytes tout en étant un multiple de la size d'une page de notre OS.
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    DWORD sizePageBuffer = info.dwAllocationGranularity *
                           ceil((double) SIZE_BUFFER * sizeof(char) / (double) info.dwAllocationGranularity);
    int nbExtension = ceil((double) sizeByteSource / (double) sizePageBuffer);

    HANDLE hMapFile;
    char *buffer = (char *) malloc(sizePageBuffer);
    DWORD start = 0;
    int i = 1;
    int end = sizePageBuffer;
    int toMapWrite = sizePageBuffer;
    int lastPage = sizeByteSource - ((nbExtension - 1) * sizePageBuffer);
    if (sizeByteSource < sizePageBuffer) {
        toMapWrite = sizeByteSource;
        end = sizeByteSource;
    }


    while (i <= nbExtension) {

        if (i == nbExtension && nbExtension != 1) {
            toMapWrite = lastPage;
            end = start + lastPage;
        }
        hMapFile = CreateFileMapping(
                hFile,    // use paging file
                NULL,                    // default security
                PAGE_READWRITE,
                0,
                end,
                _T("INFO-H417"));                 // name of mapping object

        if (hMapFile == NULL) {
            int err = errno;
            fprintf(stderr, "Value of errno: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error of CreateFileMapping function: %s\n", strerror(err));
        }
        LPCTSTR writeBuffer;
        strncpy(buffer, c + start, toMapWrite);
        writeBuffer = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                             FILE_MAP_ALL_ACCESS, // read/write permission
                                             0,
                                             start,
                                             toMapWrite); //null

        if (writeBuffer == NULL) {
            int err = errno;
            fprintf(stderr, "Value of errno: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error of the MapViewOfFile function: %s\n", strerror(err));
            CloseHandle(hMapFile);
        }
        printf("start %d \n", start);
        printf("toMapWrite %d \n", toMapWrite);
        printf("end %d \n", end);

        CopyMemory((PVOID) (writeBuffer), _T(buffer), (toMapWrite));
        UnmapViewOfFile(writeBuffer);
        CloseHandle(hMapFile);
        start += sizePageBuffer;
        end = start + sizePageBuffer;
        i++;
    }
    free(buffer);
}

/**
 * Closes the file.
 */
void OutputStream::close() {
    fclose(file);
}


