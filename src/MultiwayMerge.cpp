#include <vector>
#include <queue>
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
    InputStream1 *inputStream = new InputStream1(fileName, 0);
    inputStream->open();
    bool run = true;
    int fileNb = 0;
    vector<InputStream1 *> files;
    while (run) {
        vector<vector<string>> lines;
        int totalLength = 0;
        while (totalLength < M) {
            string stringLine = inputStream->readln();
            if (stringLine.empty()) {
                run = false;
                break;
            }
            vector<string> line = stringToVector(stringLine);
            lines.push_back(line);
            totalLength += stringLine.length();
        }
        if (lines.size() != 0) {
            sort(lines.begin(), lines.end(),
                 [k](const std::vector<string> &a, const std::vector<string> &b) {
                     return a[k] < b[k];
                 });
            string newFileName = "../bin/file" + to_string(fileNb) + ".txt";
            char *name = new char[newFileName.length() + 1];
            for (int i = 0; i < newFileName.length(); i++) {
                name[i] = newFileName[i];
            }
            name[newFileName.length()] = '\0';
            OutputStream1 *o = new OutputStream1(name, 0);
            o->create();
            for (int lineNb = 0; lineNb < lines.size(); lineNb++) {
                string line = vectorToString(lines[lineNb]);
                o->writeln(line);
            }
            o->close();
            InputStream1 *i = new InputStream1(name, 0);
            files.push_back(i);
            fileNb++;
        }
    }
    inputStream->close();

    while (files.size() > 1) {
        int nbFilesToMerge = d;
        if (files.size() < d) {
            nbFilesToMerge = files.size();
        }
        auto comp = [k](QueueObject a, QueueObject b) {
            //cout << a.line[k] << " " << b.line[k] << endl;
            return a.line[k] > b.line[k];
        };
        priority_queue<QueueObject, vector<QueueObject>, decltype(comp)> linesQueue(comp);
        for (int i = 0; i < nbFilesToMerge; i++) {
            files[i]->open();
            string stringLine = files[i]->readln();
            //cout << "OK" << endl;
            vector<string> line = stringToVector(stringLine);
            QueueObject q = {files[i], line};
            linesQueue.push(q);
        }
        string newFileName = "../bin/file" + to_string(fileNb) + ".txt";
        char *name = new char[newFileName.length() + 1];
        for (int i = 0; i < newFileName.length(); i++) {
            name[i] = newFileName[i];
        }
        name[newFileName.length()] = '\0';
        OutputStream1 *o = new OutputStream1(name, 0);
        o->create();
        while (linesQueue.size() != 0) {
            vector<string> vectorLine = linesQueue.top().line;
            string stringLine = vectorToString(vectorLine);
            //cout << stringLine << endl;
            o->writeln(stringLine);
            string nextLine = linesQueue.top().inputStream->readln();
            InputStream1 *tempInputStream = linesQueue.top().inputStream;
            linesQueue.pop();
            if (nextLine != "") {
                QueueObject newObject = {tempInputStream, stringToVector(nextLine)};
                linesQueue.push(newObject);
            }
        }
        for (int i = 0; i < nbFilesToMerge; i++) {
            files.erase(files.begin());
        }
        o->close();
        InputStream1 *i = new InputStream1(name, 0);
        files.push_back(i);
        fileNb++;

    }
    return nullptr;
}

vector<string> MultiwayMerge::stringToVector(string stringLine) {
    vector<string> line;
    stringstream ss(stringLine);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        line.push_back(substr);
    }
    return line;
}

string MultiwayMerge::vectorToString(vector<string> vectorLine) {
    string stringLine;
    for (int wordNb = 0; wordNb < vectorLine.size(); wordNb++) {
        if (wordNb == vectorLine.size() - 1) {
            stringLine += vectorLine[wordNb];
        } else {
            stringLine += vectorLine[wordNb] + ",";
        }
    }
    return stringLine;
}