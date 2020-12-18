#include "OutputStream4.h"
#include <io.h>
#include <windows.h>
#include <conio.h>
#include <tchar.h>
#include <fcntl.h>
#include <cmath>
#include <algorithm>
#include <iostream>


/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream4::OutputStream4(char *fName, int B): OutputStream(fName,B) {
    fileName = fName;
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    start_file = 0;
    sizePageBuffer = info.dwAllocationGranularity *
                     ceil((double) BufferSize * sizeof(char) / (double) info.dwAllocationGranularity);
}

/**
 * Creates a file and stores it in the file field of the OutputStream class.
 */
void OutputStream4::create() {
    hFile = CreateFile(_T(fileName), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
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
    map(sizePageBuffer);


}

/**
 * Unmap a region from memory
 */
void OutputStream4::unmap() {
    UnmapViewOfFile(writeBuffer);
    CloseHandle(hMapFile);
}

/**
 * Map a region into memory
 */
void OutputStream4::map(int toMap) {
    DWORD start = (start_file/sizePageBuffer)*sizePageBuffer;
    hMapFile = CreateFileMapping(
            hFile,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,
            0,
            start+toMap,
            _T(fileName));                 // name of mapping object

    if (hMapFile == NULL) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of CreateFileMapping function: %s\n", strerror(err));
    }

    writeBuffer = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                         FILE_MAP_ALL_ACCESS, // read/write permission
                                         0,
                                         start,
                                         toMap); //null

    if (writeBuffer == NULL) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of the MapViewOfFile function: %s\n", strerror(err));
        CloseHandle(hMapFile);
    }

}

/**
 * Write a string in the file of the OutputStream class trough a buffer
 * in internal memory and terminate this stream with the newline character.
 * @param  text : string to be written in the file
 */
void OutputStream4::writeln(string text) {
    const char *c = text.c_str();
    int sizeByteSource = strlen(c) * sizeof(c[0]);
    //adaption du SIZE_BUFFER en nombre de bytes tout en étant un multiple de la size d'une page de notre OS.
    DWORD start = (start_file/sizePageBuffer)*sizePageBuffer;
    int nbExtension = ceil(((double) sizeByteSource+(double)start_file) / ((double) sizePageBuffer+(double)start));
    int toMapWrite = sizePageBuffer;
    int lastPage = sizeByteSource - ((nbExtension - 1) * sizePageBuffer);

    if (start_file+sizeByteSource>sizePageBuffer+start){
        lastPage = (start_file+sizeByteSource-((sizePageBuffer*(nbExtension-1))+start));

    }
    else {
        toMapWrite = sizeByteSource+start_file-start;
    }
    int i =1;
    int offset=0;
    while ( i <= nbExtension) {
        if (i != nbExtension || nbExtension==1) {
            CopyMemory((PVOID) (writeBuffer+start_file-start), _T( c+offset), ((toMapWrite+start)-start_file));
            start_file = (toMapWrite+start);
            if(start_file==start+sizePageBuffer){
                start += sizePageBuffer;
                unmap();
                map(sizePageBuffer);
            }
        }
        else{
            CopyMemory((PVOID) (writeBuffer+start_file-start), _T( c+sizeByteSource-lastPage), ((lastPage+start)-start_file));
            start_file=lastPage+start;
        }
        i++;
        offset+=toMapWrite;
    }
}



/**
 * Closes the file.
 */
void OutputStream4::close() {
    unmap();
    fclose(file);
}

