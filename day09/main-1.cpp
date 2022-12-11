#include <fstream>
#include <iostream>
#include <istream>
#include <set>
#include <string>
#include <vector>

using namespace std;

void moveHead(pair<int, int> &head, const string &cmd) {
    if (cmd == "U")
        head.second--;
    else if (cmd == "D")
        head.second++;
    else if (cmd == "R")
        head.first++;
    else if (cmd == "L")
        head.first--;
    else
        throw(invalid_argument("unknown command"));
}

void moveTail(const pair<int, int> &head, pair<int, int> &tail) {
    if (abs(tail.first - head.first) + abs(tail.second - head.second) > 2) {
        tail.first += (tail.first - head.first < 0 ? 1 : -1);
        tail.second += (tail.second - head.second < 0 ? 1 : -1);
    }

    if (abs(tail.first - head.first) > 1) {
        tail.first += (tail.first - head.first < 0 ? 1 : -1);
    }
    if (abs(tail.second - head.second) > 1) {
        tail.second += (tail.second - head.second < 0 ? 1 : -1);
    }
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
    set<pair<int, int>> tailLocations;

    vector<pair<int, int>> ropes(2);

    while (getline(inputFile, line)) {
        const string cmd = line.substr(0, line.find(' '));
        const int count = stoi(line.substr(line.find(' ')));

        for (int i = 0; i < count; i++) {
            moveHead(ropes.front(), cmd);
            for (size_t i = 0; i < ropes.size() - 1; i++) {
                moveTail(ropes.at(i), ropes.at(i + 1));
            }
            tailLocations.insert(ropes.back());
        }
    }
    cout << "Visited positions count: " << tailLocations.size() << endl;
}
