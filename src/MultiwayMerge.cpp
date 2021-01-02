#include <vector>
#include <queue>
#include "MultiwayMerge.h"
#include <iostream>
#include <algorithm>
#include <InputStreams/InputStream1.h>
#include <OutputStreams/OutputStream1.h>
#include <InputStreams/InputStream2.h>
#include <OutputStreams/OutputStream4.h>
#include <sstream>

using namespace std;

MultiwayMerge::MultiwayMerge() {

}

/**
 * Sorts a file on the k-th column using an external-memory multiway
 * merge sort algorithm. InputStream2 and OutputStream4 were the used
 * implementations for reading and writing to files.
 * @param fileName : file to be sorted
 * @param k : column index on which the file has to be sorted
 * @param M : size of each subfile created when splitting the file the first time
 * @param d : number of files that can be merged at each iteration
 */
void MultiwayMerge::extsort(char *fileName, int k, int M, int d) {
    InputStream2 inputStream(fileName, 0);
    inputStream.open();
    bool run = true;
    int fileNb = 0;
    vector<InputStream2 *> files;

    //Divide the file into N/M subfiles
    while (run) {
        vector<vector<string>> lines;
        int totalLength = 0;
        while (totalLength < M) {
            string stringLine = inputStream.readln();
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
                 [k](const vector<string> &a, const vector<string> &b) {
                     return a[k] < b[k];
                 });
            string newFileName = "../bin/file" + to_string(fileNb) + ".txt";
            char *name = new char[newFileName.length() + 1];
            for (int i = 0; i < newFileName.length(); i++) {
                name[i] = newFileName[i];
            }
            name[newFileName.length()] = '\0';
            OutputStream4 o(name, 65536);
            o.create();
            for (int lineNb = 0; lineNb < lines.size(); lineNb++) {
                string line = vectorToString(lines[lineNb]);
                o.writeln(line);
            }
            o.close();
            InputStream2 *i = new InputStream2(name, 0);
            files.push_back(i);
            fileNb++;
        }

    }
    inputStream.close();

    //Add d files at a time in a priority queue and use it to merge
    //these files on the k-th column
    while (files.size() > 1) {
        int nbFilesToMerge = d;
        if (files.size() < d) {
            nbFilesToMerge = files.size();
        }
        //Comparator used to sort along the k-th column
        auto comp = [k](QueueObject a, QueueObject b) {
            return a.line[k] > b.line[k];
        };
        priority_queue<QueueObject, vector<QueueObject>, decltype(comp)> linesQueue(comp);
        for (int i = 0; i < nbFilesToMerge; i++) {
            files[i]->open();
            string stringLine = files[i]->readln();
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
        OutputStream4 o(name, 65536);
        o.create();
        //Merge the d files
        while (linesQueue.size() != 0) {
            vector<string> vectorLine = linesQueue.top().line;
            string stringLine = vectorToString(vectorLine);
            o.writeln(stringLine);
            string nextLine = linesQueue.top().inputStream->readln();
            InputStream2 *tempInputStream = linesQueue.top().inputStream;
            linesQueue.pop();
            if (nextLine != "") {
                QueueObject newObject = {tempInputStream, stringToVector(nextLine)};
                linesQueue.push(newObject);
            }
                //If a file is empty, remove it from the queue and close it
            else {
                tempInputStream->close();
                delete[] tempInputStream->getFileName();
                free(tempInputStream);
            }
        }
        //Remove the d files from the vector of files
        for (int i = 0; i < nbFilesToMerge; i++) {
            files.erase(files.begin());
        }
        o.close();
        InputStream2 *i = new InputStream2(name, 0);
        files.push_back(i);
        fileNb++;
    }
    free(files[0]);
}

/**
 * Converts a string into a vector by splitting on each comma
 * of the string
 * @param stringLine
 * @return
 */
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

/**
 * Converts a vector back into a string by adding commas in between
 * the different elements
 * @param vectorLine
 * @return
 */
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
