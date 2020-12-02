//
// Created by Miro-Manuel on 28/11/2020.
//

#include <vector>
#include "MultiwayMerge.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <InputStreams/InputStream1.h>
#include <OutputStreams/OutputStream1.h>

using namespace std;

MultiwayMerge::MultiwayMerge() {

}


FILE *MultiwayMerge::extsort(char *fileName, int k, int M, int d) {
    InputStream1 *inputStream = new InputStream1(fileName);
    inputStream->open();
    bool run = true;
    int fileNb = 0;
    vector<OutputStream1 *> files;
    while (run) {
        vector<vector<string>> lines;
        int totalLength = 0;
        while (totalLength < M) {
            vector<string> line;
            string stringLine = inputStream->readln();
            if (stringLine.empty()) {
                run = false;
                break;
            }
            stringstream ss(stringLine);
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                line.push_back(substr);
            }
            lines.push_back(line);
            totalLength += stringLine.length();
        }
        if (lines.size() != 0) {
            sort(lines.begin(), lines.end(),
                 [k](const std::vector<string> &a, const std::vector<string> &b) {
                     return a[k] < b[k];
                 });
            string newFileName = "../bin/file" + to_string(fileNb) + ".txt";
            char *fName;
            fName = &newFileName[0];
            OutputStream1 *o = new OutputStream1(fName);
            o->create();
            for (int lineNb = 0; lineNb < lines.size(); lineNb++) {
                string line;
                for (int wordNb = 0; wordNb < lines[lineNb].size(); wordNb++) {
                    if (wordNb == lines[lineNb].size() - 1) {
                        line += lines[lineNb][wordNb];
                    } else {
                        line += lines[lineNb][wordNb] + ",";
                    }
                }
                o->writeln(line);
            }
            files.push_back(o);
        }
        fileNb++;
    }
//    files[0]->writeln("Hello");
    for (OutputStream1 *f : files) {
        f->close();
    }
    return nullptr;
}
