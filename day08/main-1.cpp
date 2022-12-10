#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

using namespace std;
using TreeRow = vector<int>;
using TreeArray = vector<TreeRow>;

bool checkDown(const TreeArray &arr, size_t x, size_t y) {
    int highest = -1;
    for (size_t i = 0; i < y; i++) {
        if (arr[i][x] > highest)
            highest = arr[i][x];
    }
    return (arr[y][x] > highest);
}

bool checkUp(const TreeArray &arr, size_t x, size_t y) {
    int highest = -1;
    for (size_t i = arr.size() - 1; i > y; i--) {
        if (arr[i][x] > highest)
            highest = arr[i][x];
    }
    return (arr[y][x] > highest);
}

bool checkLeft(const TreeArray &arr, size_t x, size_t y) {
    int highest = -1;
    for (size_t i = 0; i < x; i++) {
        if (arr[y][i] > highest)
            highest = arr[y][i];
    }
    return (arr[y][x] > highest);
}

bool checkRight(const TreeArray &arr, size_t x, size_t y) {
    int highest = -1;
    for (size_t i = arr[y].size() - 1; i > x; i--) {
        if (arr[y][i] > highest)
            highest = arr[y][i];
    }
    return (arr[y][x] > highest);
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
    TreeArray map;
    while (getline(inputFile, line)) {
        vector<int> row;
        for (char c : line)
            row.push_back(c - '0');
        map.push_back(row);
    }
    int totalVisible = 0;
    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].size(); x++) {
            if (checkDown(map, x, y) || checkUp(map, x, y) || checkLeft(map, x, y) || checkRight(map, x, y))
                totalVisible++;
        }
    }
    cout << "Visible trees: " << totalVisible << endl;
}
