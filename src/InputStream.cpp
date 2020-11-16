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
    const char c = result[strlen(result) - 1];
    if (result != NULL) {
        const char c = result[strlen(result) - 1];
        if ((int) c == 13) {
            strtok(result, "\r");
        }
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
    int B = 40;
    char *lineBuffer = (char *) malloc(B + 1);
    char *line = (char *) malloc(B + 1);
    int nbChar = read(fd, lineBuffer, B);
    if (nbChar == 0) {
        return nullptr;
    }
    lineBuffer[nbChar] = '\0';
    strcpy(line, lineBuffer);
    //cout << line << endl;
    int i = 2;
    char *firstOcc = strstr(line, "\n");
    while ((firstOcc = strstr(line, "\n")) == NULL && nbChar == B * (i - 1)) {
        line = (char *) realloc(line, i * B + 1);
        line[nbChar] = '\0';
        int nbRead = read(fd, lineBuffer, B);
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
    int saveCursor = ftell(file);
    fseek(file, 0L, SEEK_END);
    int sizeByteFile = ftell(file)*sizeof(char);
    rewind(file);
    fseek(file, saveCursor, SEEK_SET);
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    DWORD sizePageBuffer   = info.dwAllocationGranularity*ceil((double)SIZE_BUFFER*sizeof(char)/(double)info.dwAllocationGranularity);
    DWORD realFileMapStart = saveCursor * sizeof(char);    //Current position of the cursor converted into bytes

    DWORD fileMapStart     = (realFileMapStart/sizePageBuffer)*sizePageBuffer;  //Where to start the file map view
    DWORD ViewDelta       = realFileMapStart - fileMapStart;                   //the offset into the view where the line starts

    HANDLE hMapFile;
    LPCTSTR readBuffer;

    char *lineBuffer = (char *) malloc(sizePageBuffer + 1);
    DWORD start = 0;
    int i = 1;
    DWORD MapViewSize = sizePageBuffer;
    char *firstOcc;
    int nbExtension = sizeByteFile/sizePageBuffer;
    DWORD lastPageByte =  sizeByteFile - realFileMapStart;
    int mapSize;

    if((nbExtension)==(realFileMapStart/sizePageBuffer)) {  // The current page is the last one
        MapViewSize = sizeByteFile-((nbExtension)*sizePageBuffer);
        mapSize = 0;
    }
    else if(lastPageByte < sizePageBuffer) {
        mapSize = 0;  //Map until the end of the file
    }
    else {
        mapSize = realFileMapStart + sizePageBuffer;
    }

    do {
        hMapFile = CreateFileMapping(
                hFile,                      // use paging file
                NULL,                       // default security
                PAGE_READONLY,
                0,
                mapSize,
                _T("INFO-H417-Read"));   // name of mapping object

        if (hMapFile == NULL) {
            fprintf(stderr, "Error of CreateFileMapping function: %s\n");
        }

        readBuffer = (LPTSTR) MapViewOfFile(hMapFile,       // handle to map object
                                            FILE_MAP_READ,  // read permission
                                            0,
                                            fileMapStart + start,
                                            MapViewSize);

        if (readBuffer == NULL) {
            fprintf(stderr, "Error of the MapViewOfFile function: %s\n");
        }

        if(i==1){
            char *firstChar = (char *) malloc(MapViewSize-ViewDelta+ 1);
            strncpy(firstChar, (char*) readBuffer + ViewDelta,MapViewSize-ViewDelta);
            firstChar[MapViewSize-ViewDelta] = '\0';
            strcpy(lineBuffer, firstChar);
            free(firstChar);
            lineBuffer[sizePageBuffer] = '\0';

            if(lastPageByte < sizePageBuffer) {
                MapViewSize = sizeByteFile-((nbExtension)*sizePageBuffer);
            }
            else if(lastPageByte < 2*sizePageBuffer && lastPageByte > sizePageBuffer) {
                MapViewSize = lastPageByte-sizePageBuffer;
                mapSize = realFileMapStart + lastPageByte;  //sizeByteFile
            }
            else{
                mapSize  += sizePageBuffer;
            }
        }

        else{
            char *intermediary = (char*) malloc(MapViewSize+1);
            lineBuffer = (char*) realloc(lineBuffer, i*sizePageBuffer + 1);
            cout << MapViewSize << endl;
            strncpy(intermediary, (char*) readBuffer, MapViewSize);
            intermediary[MapViewSize] = '\0';
            strcat(lineBuffer, intermediary);
            lineBuffer[i * MapViewSize - ViewDelta] = '\0';
            mapSize += MapViewSize;
            free(intermediary);
        }
        start += sizePageBuffer;
        i++;
        UnmapViewOfFile(readBuffer);
        CloseHandle(hMapFile);

    }while((strstr((char*)lineBuffer, "\n") == NULL) && ((nbExtension)!=(realFileMapStart/sizePageBuffer)));

    int position2 = strlen(lineBuffer);
    if ((firstOcc = strstr((char*)lineBuffer, "\n"))  != 0) {
        position2 = firstOcc - lineBuffer;
    }

    char *resultLine = (char *) malloc(position2+ 1);   //i*MapViewSize + 1
    strncpy(resultLine, lineBuffer, position2);
    resultLine[position2] = '\0';
    fseek(file, position2 + 1, SEEK_CUR);  // position2 - strlen(lineBuffer) + 1
    free(lineBuffer);

    return resultLine;
}