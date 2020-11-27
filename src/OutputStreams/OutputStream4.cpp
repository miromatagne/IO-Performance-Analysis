#include "OutputStream4.h"
#include <io.h>
#include <windows.h>
#include <conio.h>
#include <tchar.h>
#include <fcntl.h>
#include <cmath>
#include <algorithm>
#include <iostream>

#define SIZE_BUFFER 10
/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream4::OutputStream4(const char *fName) {
    fileName = fName;
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    start_file = 0;
    start = 0;
    sizePageBuffer = info.dwAllocationGranularity *
                     ceil((double) SIZE_BUFFER * sizeof(char) / (double) info.dwAllocationGranularity);
    toMapWrite = sizePageBuffer;
    end = sizePageBuffer;
    a=0;
}

/**
 * Creates a file and stores it in the file field of the OutputStream class.
 */
void OutputStream4::create() {
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
    /*
    cout << "my end" << end << endl;
    cout << "start" << start << endl;
    cout << "to Map" << toMapWrite << endl;
     */
    if(toMapWrite+start>end){
        cout << "aie" << endl;
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
        //CloseHandle(hMapFile);
        exit(4);

    }

}

/**
 * Write a string in the file of the OutputStream class trough a buffer
 * in internal memory and terminate this stream with the newline character.
 * @param  text : string to be written in the file
 */
void OutputStream4::writeln(string text) {
    text += "\n";
    const char *c = text.c_str();
    int sizeByteSource = strlen(c) * sizeof(c[0]);
    //adaption du SIZE_BUFFER en nombre de bytes tout en étant un multiple de la size d'une page de notre OS.
    //cout << "Start_file : "<< start_file << endl;
    start = (start_file/sizePageBuffer)*sizePageBuffer;
    nbExtension = ceil((double) sizeByteSource / (double) sizePageBuffer); // si on a  un string text plus grand que allocation granularity
    bool bigText = FALSE ;
    if (nbExtension !=1){
        bigText = TRUE ;
    }

    char *buffer = (char *) malloc(sizePageBuffer);
    int i = 1;
    int newEnd = sizePageBuffer+start;
    toMapWrite = sizePageBuffer;
    int lastPage = sizeByteSource - ((nbExtension - 1) * sizePageBuffer);
    //cout << sizeByteSource << endl;


    // cas où on est entre 2 pages
    //cout << nbExtension << endl;
    if (start_file+sizeByteSource>sizePageBuffer+start){
        nbExtension+=1;
        lastPage = (start_file+sizeByteSource-(sizePageBuffer+start));
        //cout << "ok" << lastPage << endl;
    }
    else if (sizeByteSource < sizePageBuffer) {
        toMapWrite = sizeByteSource+start_file-start;
        newEnd = sizePageBuffer+start;
    }


    while (i <= nbExtension) {
        if (i == nbExtension && nbExtension != 1) {
            //cout << "last page" << endl;
            toMapWrite = lastPage;
            newEnd = start + lastPage;
            //cout << "okkkkkk" << start << endl;
            strncpy(buffer, c+(toMapWrite+start)-start_file, toMapWrite);
        }
        else{
            strncpy(buffer, c, toMapWrite);
        }
        if(bigText){
            strncpy(buffer, c + start, toMapWrite);
        }


        if(start_file>end){
            if(a==3){
                exit(4);
            }
            cout << "map" << start_file << endl;
            end = start*2;
            unmap();
            map(sizePageBuffer);
            a+=1;
        }



        //cout << "pg" << start_file << endl;
        //cout << "toMap" << toMapWrite << endl;
        //cout << "end" << toMapWrite << endl;
        CopyMemory((PVOID) (writeBuffer+start_file-start), _T( buffer), ((toMapWrite+start)-start_file));

        //cout << "bruh" << endl;
        //strcpy((char*) (writeBuffer+start_file),buffer);

        //fseek(file, (toMapWrite+start)-start_file, SEEK_CUR);


        start_file+= (toMapWrite+start)-start_file;
        start += sizePageBuffer;
        newEnd = start + sizePageBuffer;
        i++;

    }
    free(buffer);
    // position2 - strlen(lineBuffer) + 1
}

/**
 * Closes the file.
 */
void OutputStream4::close() {
    unmap();
    fclose(file);
}

