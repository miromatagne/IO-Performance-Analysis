//
// Created by Miro-Manuel on 31/10/2020.
//

#include "InputStream.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

InputStream::InputStream(string fName) {
    fileName = fName;
}

string InputStream::getFileName(void) {
    return fileName;
}

void InputStream::open(void) {
    file = ifstream(fileName);
}
