#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "Stacks.hpp"

using namespace std;

ostream &operator<<(ostream &stream, const Stacks &stacks) {
    stacks.printStacks(stream);
    return (stream);
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

    string line;
    vector<string> preset;
    while (getline(inputFile, line) && !line.empty())
        preset.push_back(line);
    if (!inputFile || preset.empty()) {
        cerr << "Input file error" << endl;
        return (EXIT_FAILURE);
    }
    Stacks stacks;

    if (!stacks.parseStacks(preset)) {
        cerr << "failed to parse stacks" << endl;
        return (EXIT_FAILURE);
    }

    int i = 1;
    while (getline(inputFile, line)) {
        cout << stacks << endl;
        if (!stacks.executeMove(line, Stacks::AllInOne)) {
            cerr << "failed to exec move" << endl;
            return (EXIT_FAILURE);
        }
        cout << "line " << i++ << ": " << line << endl;
        usleep(10 * 1000);
    }

    cout << stacks << endl;
}
