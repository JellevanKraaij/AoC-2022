#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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

    int cycleCounter = 0;
    int regX = 1;
    bool processing = false;

    string line;
    while (processing || getline(inputFile, line)) {
        cout << (abs((cycleCounter % 40) - regX) < 2 ? '#' : '.');
        if ((cycleCounter % 40 == 39))
            cout << endl;
        if (line.compare(0, 5, "addx ") == 0) {
            cycleCounter++;
            if (processing == false) {
                processing = true;
                continue;
            }
            processing = false;
            regX += stoi(line.substr(5));
        } else if (line == "noop")
            cycleCounter++;
        else {
            cerr << "unkown instruction" << endl;
            return (EXIT_FAILURE);
        }
    }
}
