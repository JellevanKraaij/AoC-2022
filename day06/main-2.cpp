#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

bool checkUnique(deque<char> buffer) {
    sort(buffer.begin(), buffer.end());
    return (unique(buffer.begin(), buffer.end()) == buffer.end());
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " inputfile" << endl;
        return (EXIT_FAILURE);
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Unable to open input file " << argv[1] << endl;
        return (EXIT_FAILURE);
    }
    int processedChars = 0;
    deque<char> buffer;
    char c = 0;
    while (inputFile >> c && c != '\n') {
        buffer.push_back(c);
        processedChars++;
        if (buffer.size() < 14 + 1)
            continue;
        buffer.pop_front();
        if (checkUnique(buffer))
            break;
    }
    if (inputFile.eof() || c == '\n') {
        cerr << "Stream stopped before a marker was encounderd" << endl;
        return (EXIT_FAILURE);
    }
    cout << "first marker after character " << processedChars << endl;
}
