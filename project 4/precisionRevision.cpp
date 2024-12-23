#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
using namespace std;

const int N = 8;  // Length of the N-byte sequences

void createRevision(istream& fold, istream& fnew, ostream& frevision) {
    // Read the entire contents of the old and new files into strings
    string oldContent((istreambuf_iterator<char>(fold)), istreambuf_iterator<char>());
    string newContent((istreambuf_iterator<char>(fnew)), istreambuf_iterator<char>());

    // Create a table to store the positions of N-byte sequences from the old file
    vector<vector<int> > table(256, vector<int>()); // 256 possible values for a byte
    for (int i = 0; i <= oldContent.size() - N; ++i) {
        table[oldContent[i]].push_back(i);
    }

    // Process the new file and create the revision file
    int j = 0;
    while (j < newContent.size()) {
        // Look for an N-byte sequence in the table
        int matchOffset = -1;
        int maxLength = 0;

        if (j <= newContent.size() - N) {
            for (int offset : table[newContent[j]]) {
                if (offset + N > oldContent.size()) continue;
                if (newContent.substr(j, N) == oldContent.substr(offset, N)) {
                    int matchLength = N;
                    // Extend the match as long as possible
                    while (j + matchLength < newContent.size() && offset + matchLength < oldContent.size() &&
                           newContent[j + matchLength] == oldContent[offset + matchLength]) {
                        matchLength++;
                    }
                    if (matchLength > maxLength) {
                        maxLength = matchLength;
                        matchOffset = offset;
                    }
                }
            }
        }

        if (matchOffset != -1) {
            // Write a Copy instruction
            frevision << "#" << matchOffset << "," << maxLength;
            j += maxLength;
        } else {
            // Write an Add instruction for the unmatched character(s)
            string addSeq;
            char delim = '/';
            while (j < newContent.size()) {
                bool found = false;
                for (int offset : table[newContent[j]]) {
                    if (j <= newContent.size() - N && newContent.substr(j, N) == oldContent.substr(offset, N)) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
                addSeq += newContent[j++];
            }
            while (addSeq.find(delim) != string::npos) delim++;  // Find a suitable delimiter
            frevision << "+" << delim << addSeq << delim;
        }
    }
}

bool getInt(istream& inf, int& n) {
    char ch;
    if (!inf.get(ch) || !isascii(ch) || !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, char& delim, int& length, int& offset) {
    if (!inf.get(cmd)) {
        cmd = 'x';  // signals end of file
        return true;
    }
    switch (cmd) {
        case '+':
            return inf.get(delim).good();
        case '#':
            {
                char ch;
                return getInt(inf, offset) && inf.get(ch) && ch == ',' && getInt(inf, length);
            }
        case '\r':
        case '\n':
            return true;
    }
    return false;
}

bool revise(istream& fold, istream& frevision, ostream& fnew) {
    // Read the entire contents of the old file into a string
    string oldContent((istreambuf_iterator<char>(fold)), istreambuf_iterator<char>());

    char cmd, delim;
    int length, offset;
    while (getCommand(frevision, cmd, delim, length, offset)) {
        switch (cmd) {
            case '+':
                {
                    string toAdd;
                    getline(frevision, toAdd, delim);
                    fnew.write(toAdd.c_str(), toAdd.size());
                }
                break;
            case '#':
                if (offset + length > oldContent.size())
                    return false;  // Invalid Copy instruction
                fnew.write(oldContent.c_str() + offset, length);
                break;
            case '\r':
            case '\n':
                // Do nothing
                break;
            case 'x':
                return true;  // End of file
            default:
                return false;  // Invalid command
        }
    }
    return true;
}