#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

using namespace std;
using TreeRow = vector<int>;
using TreeArray = vector<TreeRow>;

int checkDown(const TreeArray &arr, size_t x, size_t y) {
    int vision = 1;
    size_t i = y + 1;

    while (i < arr.size() - 1 && arr[i][x] < arr[y][x]) {
        i++;
        vision++;
    }
    return (vision == 0 ? 1 : vision);
}

int checkUp(const TreeArray &arr, size_t x, size_t y) {
    int vision = 1;
    ssize_t i = y - 1;

    while (i > 0 && arr[i][x] < arr[y][x]) {
        i--;
        vision++;
    }
    return (vision == 0 ? 1 : vision);
}

int checkRight(const TreeArray &arr, size_t x, size_t y) {
    int vision = 1;
    size_t i = x + 1;

    while (i < arr[y].size() - 1 && arr[y][i] < arr[y][x]) {
        i++;
        vision++;
    }
    return (vision == 0 ? 1 : vision);
}

int checkLeft(const TreeArray &arr, size_t x, size_t y) {
    int vision = 1;
    ssize_t i = x - 1;

    while (i > 0 && arr[y][i] < arr[y][x]) {
        i--;
        vision++;
    }
    return (vision == 0 ? 1 : vision);
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
    int biggest = 0;
    for (size_t y = 1; y < map.size() - 1; y++) {
        for (size_t x = 1; x < map[y].size() - 1; x++) {
            const int result = checkDown(map, x, y) * checkUp(map, x, y) * checkLeft(map, x, y) * checkRight(map, x, y);
            if (result > biggest)
                biggest = result;
        }
    }
    cout << "tree with most vision: " << biggest << endl;
}
