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

    int cycleCounter = 1;
    int regX = 1;
    bool processing = false;
    int sumSignalStrength = 0;

    string line;
    while (processing || getline(inputFile, line)) {
        if ((cycleCounter + 20) % 40 == 0 && cycleCounter <= 220)
            sumSignalStrength += cycleCounter * regX;
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
    cout << "Sum singal strengths: " << sumSignalStrength << endl;
}
