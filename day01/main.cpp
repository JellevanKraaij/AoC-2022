#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " inputfile" << endl;
        return (EXIT_FAILURE);
    }

    ifstream inputFile(argv[1]);

    if (!inputFile) {
        cout << "Cannot open inputfile" << endl;
        return (EXIT_FAILURE);
    }

    vector<int> totals;
    int currentTotal = 0;

    string line;
    while (getline(inputFile, line)) {
        int current = atoi(line.c_str());
        if (current == 0) {
            totals.push_back(currentTotal);
            currentTotal = 0;
            continue;
        }
        currentTotal += current;
    }
    sort(totals.begin(), totals.end(), greater<int>());
    int total = 0;
    for (size_t i = 0; i < min(totals.size(), (size_t)3); i++) {
        total += totals[i];
        cout << i + 1 << ": " << totals[i] << endl;
    }
    cout << "total: " << total << endl;
}
