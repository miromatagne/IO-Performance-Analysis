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
    fd = _open_osfhandle((intptr_t)hFile, _O_RDONLY);
    if (fd == -1) {
        ::CloseHandle(hFile);
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror( err ));
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
            break;
        }
        if (c != '\n') {
            lineBuffer[count] = c;
            count++;
        }
    }
    lineBuffer[count] = '\0';
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
    int sizeB = 80;
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
    while ((firstOcc = strstr(line, "\n")) == NULL && nbChar == sizeB*(i-1)) {
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
    int save = ftell(file);
    fseek(file, 0L, SEEK_END);
    int sizeByteFile = ftell(file)*sizeof(char);
    rewind(file);
    fseek(file, save, SEEK_SET);
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    DWORD sizePageBuffer = info.dwAllocationGranularity*ceil((double)SIZE_BUFFER*sizeof(char)/(double)info.dwAllocationGranularity);
    DWORD realFileMapStart = save * sizeof(char);
    /*if(ftell(file)*sizeof(char) < sizePageBuffer) {
        RealFileMapStart = 0;   //starting point within the file
    }*/


    DWORD fileMapStart       = (realFileMapStart/sizePageBuffer)*sizePageBuffer;  //Where to start the file map view
    DWORD offsetFileMapSize  = realFileMapStart;
    //DWORD offsetMapViewSize = (RealFileMapStart%sizePageBuffer);
    int iViewDelta = realFileMapStart - fileMapStart;

    HANDLE hMapFile;
    char *lineBuffer = (char *) malloc(sizePageBuffer + 1);
    DWORD start = 0;
    int i = 2;
    int end = sizePageBuffer;
    int toMapWrite = sizePageBuffer;
    char *firstOcc;
    int nbExtension = ceil((double)sizeByteFile/(double)sizePageBuffer) - (fileMapStart/sizePageBuffer);
    int lastPage = sizeByteFile - ((nbExtension + (fileMapStart/sizePageBuffer)-1)*sizePageBuffer);
    int mapSize = offsetFileMapSize + end;
    if((sizeByteFile - realFileMapStart) < sizePageBuffer) {   // fileMapStart == (sizeByteFile/sizePageBuffer)
        mapSize = fileMapStart + lastPage;  //sizeByteFile
        cout << "mapSize petit" << endl;
    }

    char *intermediary = (char*) malloc(toMapWrite + 1);
    hMapFile = CreateFileMapping(
            hFile,    // use paging file
            NULL,                       // default security
            PAGE_READONLY,
            0,
            mapSize,                        //sizePageBuffer
            _T("INFO-H417-Read"));                 // name of mapping object
    if (hMapFile == NULL) {
        int err = errno;
        fprintf(stderr, "Value of errno1: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of CreateFileMapping function: %s\n", strerror(err));
    }
    cout << toMapWrite << endl;
    cout << sizeByteFile - fileMapStart + start << endl;
    LPCTSTR readBuffer = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                        FILE_MAP_READ,      // read/write permission
                                        0,
                                        fileMapStart + start,     // start
                                        toMapWrite);   // null

    if (readBuffer == NULL) {
        int err = errno;
        fprintf(stderr, "Value of errno1: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of the MapViewOfFile function: %s\n", strerror(err));
        CloseHandle(hMapFile);
    }
    char *firstChar = (char *) readBuffer + iViewDelta;
    //cout << realFileMapStart << endl;
    //cout << sizePageBuffer - iViewDelta << endl;
    memcpy(intermediary, firstChar, sizePageBuffer - iViewDelta);
    intermediary[sizePageBuffer - iViewDelta] = '\0';
    //cout << "ok2" << endl;
    strcpy(lineBuffer, intermediary);
    lineBuffer[sizePageBuffer - iViewDelta] = '\0';
    UnmapViewOfFile(readBuffer);
    CloseHandle(hMapFile);
    start += sizePageBuffer;
    mapSize  += sizePageBuffer;
    if((sizeByteFile - realFileMapStart) < sizePageBuffer) {   // fileMapStart == (sizeByteFile/sizePageBuffer)
        toMapWrite = lastPage;  //sizeByteFile
        cout << "OKKKKKKKKf" << endl;
    }
    //i <= nbExtension && i != 1
    while(strstr((char*)lineBuffer, "\n") == NULL && (i-1) != nbExtension) {   // && counter == (i-1)*toMapWrite-iViewDelta
        if ((sizeByteFile - realFileMapStart) <= 2*sizePageBuffer) {
            toMapWrite = lastPage;
            mapSize = fileMapStart + start + lastPage;  //sizeByteFile
        }
        cout << "WHILE OK" << endl;
        cout << mapSize   << endl;
        cout << sizeByteFile << endl;  //1312551
        cout << toMapWrite + fileMapStart + start << endl;
        cout << toMapWrite << endl;
        cout << nbExtension << endl;
        cout << i << endl;
        lineBuffer = (char*) realloc(lineBuffer, i*sizePageBuffer + 1);

        hMapFile = CreateFileMapping(
                hFile,    // use paging file
                NULL,                    // default security
                PAGE_READONLY,
                0,
                mapSize,
                _T("INFO-H417-Read"));                 // name of mapping object

        if (hMapFile == NULL) {
            int err = errno;
            fprintf(stderr, "Value of errno2: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error of CreateFileMapping function: %s\n", strerror(err));
        }

        readBuffer = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                             FILE_MAP_READ, // read/write permission
                                             0,
                                             fileMapStart + start,
                                             toMapWrite); //null

        if (readBuffer == NULL) {
            int err = errno;
            fprintf(stderr, "Value of errno2: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error of the MapViewOfFile function: %s\n", strerror(err));
            CloseHandle(hMapFile);
        }
        memcpy(intermediary, readBuffer, toMapWrite);
        intermediary[toMapWrite] = '\0';
        strcat(lineBuffer, intermediary);
        lineBuffer[i * toMapWrite - iViewDelta] = '\0';
        UnmapViewOfFile(readBuffer);
        CloseHandle(hMapFile);
        start += sizePageBuffer;
        mapSize += sizePageBuffer;
        i++;
    }

    int position2 = strlen(lineBuffer);
    if ((firstOcc = strstr((char*)lineBuffer, "\n"))  != 0) {
        position2 = firstOcc - lineBuffer;
    }
    //cout << "Position" << endl;
    //cout << position2 << endl;
    char *resultLine = (char *) malloc(position2+ 1);   //i*toMapWrite + 1
    memcpy(resultLine, lineBuffer, position2);
    resultLine[position2] = '\0';
    fseek(file, position2 + 1, SEEK_CUR);  // position2 - strlen(lineBuffer) + 1
    free(lineBuffer);
    return resultLine;
}