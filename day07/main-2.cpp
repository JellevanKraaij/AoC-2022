#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int calculateTotalSizes(istream &input, vector<int> &folderSizes) {
    string line;
    size_t total = 0;
    while (getline(input, line)) {
        if (line.compare(0, 4, "$ cd") == 0) {
            if (line.compare(5, 2, "..") == 0)
                break;
            total += calculateTotalSizes(input, folderSizes);
        }
        total += atoi(line.c_str());
    }
    folderSizes.push_back(total);
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
    vector<int> folderSizes;
    int totalSize = calculateTotalSizes(inputFile, folderSizes);

    sort(folderSizes.begin(), folderSizes.end());
    for (int i : folderSizes)
    {
        if (totalSize - i < 40000000)
        {
            cout << "size of folder to delete " << i << endl;
            break ;
        }
    }
}
