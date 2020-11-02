#include "OutputStream.h"
#include <io.h>
#include <windows.h>
#include <conio.h>
#include <tchar.h>
#include <fcntl.h>



using namespace std;
extern int errno ;

/**
 * Constructor storing the chosen file's name in the fileName
 * field of the OutputStream class
 * @param fName : string corresponding to the filename the user chose
 */
OutputStream::OutputStream(const char* fName) {
    fileName = fName;
}
/**
 * Creates a file and stores it in the file field of the OutputStream class.
 */
void OutputStream::create() {
    hFile = CreateFile(_T(fileName), GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror( err ));
    }
    fd = _open_osfhandle((long)hFile, _O_APPEND);
    if (fd == -1) {
        ::CloseHandle(hFile);
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror( err ));
    }
    file = _fdopen(fd, "w");
    if (!file) {
        ::CloseHandle(hFile);
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while creating the file: %s\n", strerror( err ));
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
    while (c != '\0'){
        i++;
        write(fd,&c,sizeof(c));
        c = text[i];
    }
    c = '\n';
    write(fd,&c,sizeof(c));
}
/**
 * Write a string in the file of the OutputStream class and terminate
 * this stream with the newline character using fputs functions from the
 * C stdio library.
 * @param  text : string to be written in the file
 */
void OutputStream::writeln2(string text) {
    text+="\n";
    const char* c = text.c_str();
    if (fputs(c, file) < 0)
    {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error while writing in file: %s\n", strerror( err ));
    }
}
/**
 * Write a string in the file of the OutputStream class trough a buffer
 * in internal memory and terminate this stream with the newline character.
 * @param  text : string to be written in the file
 */
void OutputStream::writeln3(string text) const {
    text+="\n";
    const char* c = text.c_str();
    write(fd,c,strlen(c));
}
/**
 * Write a string in the file of the OutputStream class by mapping the characters
 * into internal memory through memory mapping and terminate this stream with
 * the newline character.
 * @param  text : string to be written in the file
 */

void OutputStream::writeln4(string text) {
    LPCTSTR writeBuffer;
    text+="\n";

    //TCHAR c[]=TEXT("test");
    int size = strlen(text.c_str());
    HANDLE hMapFile;
    hMapFile = CreateFileMapping(
            hFile,    // use paging file
            NULL,                    // default security
            PAGE_READWRITE,
            0,                       // max. object size
            size,                    // buffer size
            _T("INFO-H417"));                 // name of mapping object

    if (hMapFile == NULL)
    {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of CreateFileMapping function: %s\n", strerror( err ));
    }
    writeBuffer = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                  FILE_MAP_ALL_ACCESS, // read/write permission
                                  0,
                                  0,
                                  size);

    if (writeBuffer == NULL)
    {
        int err = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error of the MapViewOfFile function: %s\n", strerror( err ));
        CloseHandle(hMapFile);
    }

    CopyMemory((PVOID)writeBuffer, _T(text.c_str()), (size * sizeof(TCHAR)));
    UnmapViewOfFile(writeBuffer);
    CloseHandle(hMapFile);


}
/**
 * Closes the file.
 */
void OutputStream::close() {
    fclose(file);
}


