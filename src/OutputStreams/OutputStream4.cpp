#include "OutputStream4.h"
#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <cmath>
#include <io.h>


/**
 * Call the parent's constructor and initialize attributes
 * @param fName : string corresponding to the filename the user chose
 * @param B : Size of the buffer
 */
OutputStream4::OutputStream4(char *fName, int B) : OutputStream(fName, B) {
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
        printf("INVALID_HANDLE_VALUE");
    }
    fd = _open_osfhandle((intptr_t) hFile, _O_APPEND);
    if (fd == -1) {
        ::CloseHandle(hFile);
        printf("error while creating the file");
    }
    file = _fdopen(fd, "w");
    if (!file) {
        ::CloseHandle(hFile);
        printf("error while opening the file");
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
void OutputStream4::map(DWORD toMap) {
    DWORD start = (start_file / sizePageBuffer) * sizePageBuffer;
    hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, start + toMap, _T(fileName));
    if (hMapFile == NULL) {
        printf("error with the function CreateFileMapping");
    }
    writeBuffer = (LPTSTR) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, start, toMap);
    if (writeBuffer == NULL) {
        printf("error with the function MapViewOfFile");
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
    DWORD start = (start_file / sizePageBuffer) * sizePageBuffer;
    int nbExtension = ceil(
            ((double) sizeByteSource + (double) start_file) / ((double) sizePageBuffer + (double) start));
    int toMapWrite = sizePageBuffer;
    int lastPage = sizeByteSource - ((nbExtension - 1) * sizePageBuffer);

    if (start_file + sizeByteSource > sizePageBuffer + start) {
        lastPage = (start_file + sizeByteSource - ((sizePageBuffer * (nbExtension - 1)) + start));

    } else {
        toMapWrite = sizeByteSource + start_file - start;
    }
    int i = 1;
    int offset = 0;
    while (i <= nbExtension) {
        if (i != nbExtension || nbExtension == 1) {
            CopyMemory((PVOID) (writeBuffer + start_file - start), _T(c + offset), ((toMapWrite + start) - start_file));
            start_file = (toMapWrite + start);
            if (start_file == start + sizePageBuffer) {
                start += sizePageBuffer;
                unmap();
                map(sizePageBuffer);
            }
        } else {
            CopyMemory((PVOID) (writeBuffer + start_file - start), _T(c + sizeByteSource - lastPage),
                       ((lastPage + start) - start_file));
            start_file = lastPage + start;
        }
        i++;
        offset += toMapWrite;
    }
}


/**
 * Closes the file.
 */
void OutputStream4::close() {
    unmap();
    fclose(file);
}

