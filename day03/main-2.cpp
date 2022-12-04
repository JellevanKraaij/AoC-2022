#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int calculatePrioValue(string input) {
    int result = 0;

    for (const char &c : input) {
        if (islower(c))
            result += c - 'a' + 1;
        else if (isupper(c))
            result += c - 'A' + 27;
    }
    return (result);
}

string findSharedItems(const string input[3]) {
    string sharedItems;
    string alreadyChecked;

    for (const char &c : input[0]) {
        if (alreadyChecked.find(c) == string::npos && input[1].find(c) != string::npos && input[2].find(c) != string::npos) {
            alreadyChecked += c;
            sharedItems += c;
        }
    }
    return (sharedItems);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " inputfile" << endl;
        return (EXIT_FAILURE);
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Unable to open file " << argv[1] << endl;
        return (EXIT_FAILURE);
    }
    int i = 0;
    string lines[3];
    int totalPrio;
    while (getline(inputFile, lines[i])) {
        if ((lines[i].length() % 2) != 0 || lines[i].empty() || !all_of(lines[i].begin(), lines[i].end(), ::isalpha)) {
            cerr << "backpack format error" << endl;
            return (EXIT_FAILURE);
        }
        if (++i < 3)
            continue;
        i = 0;
        const string sharedItems = findSharedItems(lines);
        totalPrio += calculatePrioValue(sharedItems);
        cout << lines[0] << " : " << lines[1] << " : " << lines[2] << " shared items = " << sharedItems << endl;
    }
    cout << endl;
    cout << "totalScore = " << totalPrio << endl;
}
