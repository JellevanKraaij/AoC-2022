#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <char C>
istream &expect(istream &s) {
    if (s.flags() & ios_base::skipws)
        s >> ws;
    if (s.peek() == C)
        s.ignore();
    else
        s.setstate(std::ios_base::failbit);
    return (s);
}

struct Monkey {
    int divisionValue;
    int trueMonkey;
    int falseMonkey;
    string operation;
    list<uint64_t> items;

    bool executeItem(int &monkey, uint64_t &item);
    void executeOperation();
    void addItem(uint64_t item);
};

void Monkey::addItem(uint64_t item) {
    items.push_back(item);
}

void Monkey::executeOperation() {
    const string lhs = operation.substr(0, operation.find(' '));
    const char opp = operation[operation.find(' ') + 1];
    const string rhs = operation.substr(operation.find(' ') + 3);

    uint64_t lhs_i = atoi(lhs.c_str());
    uint64_t rhs_i = atoi(rhs.c_str());

    uint64_t *lhs_p = &lhs_i;
    uint64_t *rhs_p = &rhs_i;

    if (lhs == "old")
        lhs_p = &items.front();
    if (rhs == "old")
        rhs_p = &items.front();

    switch (opp) {
        case '+':
            items.front() = *lhs_p + *rhs_p;
            break;
        case '*':
            items.front() = *lhs_p * *rhs_p;
            break;
    }
    items.front() /= 3;
}

bool Monkey::executeItem(int &monkey, uint64_t &item) {
    if (items.empty())
        return (false);
    executeOperation();
    item = items.front();
    items.pop_front();
    if (item % divisionValue == 0)
        monkey = trueMonkey;
    else
        monkey = falseMonkey;
    return (true);
}

Monkey parseMonkey(istream &stream) {
    string line;
    Monkey monkey;

    while (getline(stream, line) && !line.empty()) {
        uint64_t num;
        if (line.compare(0, 18, "  Starting items: ") == 0) {
            istringstream input(line.substr(18));
            while (input >> num) {
                monkey.items.push_back(num);
                input >> expect<','>;
            }
        } else if (line.compare(0, 19, "  Operation: new = ") == 0) {
            monkey.operation = line.substr(19);
        } else if (line.compare(0, 21, "  Test: divisible by ") == 0) {
            monkey.divisionValue = stoi(line.substr(21));
        } else if (line.compare(0, 29, "    If true: throw to monkey ") == 0) {
            monkey.trueMonkey = stoi(line.substr(29));
        } else if (line.compare(0, 30, "    If false: throw to monkey ") == 0) {
            monkey.falseMonkey = stoi(line.substr(30));
        } else
            throw(invalid_argument("invalid file format"));
    }
    return (monkey);
}

void printMonkey(const Monkey &monkey) {
    cout << "Starting items: ";
    for (const uint64_t &i : monkey.items) {
        cout << i << " ";
    }
    cout << endl;
    cout << " Operation: " << monkey.operation << endl;
    cout << " Test: divisible by " << monkey.divisionValue << endl;
    cout << "  If true: throw to monkey " << monkey.trueMonkey << endl;
    cout << "  If false: throw to monkey " << monkey.falseMonkey << endl;
    ;
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
    vector<pair<Monkey, uint64_t>> monkeys;
    while (getline(inputFile, line)) {
        monkeys.push_back(make_pair<Monkey, int>(parseMonkey(inputFile), 0));
    }

    for (size_t i = 0; i < monkeys.size(); i++) {
        cout << "Monkey " << i << endl;
        printMonkey(monkeys.at(i).first);
    }
    cout << endl;

    for (size_t rounds = 0; rounds < 20; rounds++) {
        for (size_t i = 0; i < monkeys.size(); i++) {
            int destMonkey;
            uint64_t item;
            while (monkeys.at(i).first.executeItem(destMonkey, item)) {
                monkeys.at(i).second++;
                monkeys.at(destMonkey).first.addItem(item);
            }
        }
    }

    cout << "result items:" << endl;
    for (size_t i = 0; i < monkeys.size(); i++) {
        cout << "Monkey " << i << " : " << monkeys.at(i).second << endl;
    }
    sort(monkeys.begin(), monkeys.end(),
         [](const std::pair<Monkey, uint64_t> &left, const std::pair<Monkey, uint64_t> &right) { return left.second > right.second; });
    cout << "Answer " << monkeys.at(0).second << " * " << monkeys.at(1).second << " = " << monkeys.at(0).second * monkeys.at(1).second << endl;
}
