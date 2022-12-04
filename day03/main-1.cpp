#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int calculatePrioValue(const string &input) {
    int result = 0;

    for (const char &c : input) {
        if (islower(c))
            result += c - 'a' + 1;
        else if (isupper(c))
            result += c - 'A' + 27;
    }
    return (result);
}

string findDoubleItems(const string &backpack1, const string &backpack2) {
    string doubleItems;
    string alreadyChecked;
    for (const char &c : backpack1) {
        if (alreadyChecked.find(c) == string::npos && backpack2.find(c) != string::npos) {
            alreadyChecked += c;
            doubleItems += c;
        }
    }
    return (doubleItems);
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
    string line;
    int totalPrio;
    while (getline(inputFile, line)) {
        if ((line.length() % 2) != 0 || line.empty() || !all_of(line.begin(), line.end(), ::isalpha)) {
            cerr << "backpack format error" << endl;
            return (EXIT_FAILURE);
        }
        const string backpack1 = line.substr(0, line.length() / 2);
        const string backpack2 = line.substr(line.length() / 2);

        const string doubleItems = findDoubleItems(backpack1, backpack2);
        totalPrio += calculatePrioValue(doubleItems);
        cout << backpack1 << " : " << backpack2 << " wrong items = " << doubleItems << endl;
    }
    cout << endl;
    cout << "totalScore = " << totalPrio << endl;
}
