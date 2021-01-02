#include "InputStream4.h"
#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <string>
#include <cmath>
#include <io.h>

using namespace std;

/**
 * Call the parent's constructor and initialize attributes
 * @param fName : string corresponding to the filename the user chose
 * @param B : Size of the buffer
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
    rhFile = CreateFile(_T(fileName), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (rhFile == INVALID_HANDLE_VALUE) {
        printf("INVALID_HANDLE_VALUE");
    }
    fd = _open_osfhandle((intptr_t) rhFile, _O_RDONLY);
    if (fd == -1) {
        ::CloseHandle(rhFile);
        printf("error while opening the file");
    }
    file = _fdopen(fd, "r");
    if (!file) {
        ::CloseHandle(rhFile);
        printf("error while opening the file");
    }

    fseek(file, 0, SEEK_END);
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
        end = sizeByteFile;
        toMap=sizeByteFile-start;
    } else {
        end = start + toMap;
    }
    rhMapFile = CreateFileMapping(rhFile, NULL, PAGE_READONLY, 0, end, _T(fileName));
    if (rhMapFile == NULL) {
        printf("error with the function CreateFileMapping");
    }
    readBuffer = (LPTSTR) MapViewOfFile(rhMapFile, FILE_MAP_READ, 0, start, toMap);
    if (readBuffer == NULL) {
        printf("error with the function MapViewOfFile");
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
            if ((readBuffer[i] == '\n') || start_file >= sizeByteFile) {
                if (start_file < sizeByteFile) {
                    if (currentLine.length() == 0) {
                        currentLine = '\n';
                    } else {
                        currentLine.push_back(readBuffer[i]);
                    }
                    start_file += 1;
                }
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

/**
 * Moves the cursor of the file to a certain position specified by the user.
 * @param pos : desired position of the cursor
 */
void InputStream4::seek(int pos) {
    fseek(file, pos, SEEK_SET);
    start_file = pos;
    if (pos > start + sizePageBuffer || pos < start) {
        start = (start_file / sizePageBuffer) * sizePageBuffer;
        unmap();
        map(sizePageBuffer);
    }
}