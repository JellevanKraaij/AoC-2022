#include <fstream>
#include <iostream>
#include <istream>
#include <string>

using namespace std;

int calculateTotalSizes(istream &input, int &TotalResult) {
    string line;
    size_t total = 0;
    while (getline(input, line)) {
        if (line.compare(0, 4, "$ cd") == 0) {
            if (line.compare(5, 2, "..") == 0)
                break;
            total += calculateTotalSizes(input, TotalResult);
        }
        total += atoi(line.c_str());
    }
    if (total < 100000)
        TotalResult += total;
    return (total);
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
    int result = 0;
    calculateTotalSizes(inputFile, result);
    cout << "total folders under 1000000: " << result << endl;
}
