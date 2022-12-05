#include <fstream>
#include <iostream>

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

using Jobs = pair<int, int>;

bool checkValidElfJobs(const Jobs &elf1, const Jobs &elf2) {
    return (elf1.first > elf1.second || elf2.first > elf2.second);
}

bool checkElfJobs(const Jobs &elf1, const Jobs &elf2) {
    if (elf1.first >= elf2.first && elf1.second <= elf2.second)
        return (true);
    if (elf2.first >= elf1.first && elf2.second <= elf1.second)
        return (true);
    return (false);
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
    int totalOverlap = 0;
    Jobs elf1;
    Jobs elf2;

    // clang-format off
    while (inputFile >> noskipws >> elf1.first >> expect<'-'> >> elf1.second >> expect<','> >> elf2.first >> expect<'-'> >> elf2.second >> expect<'\n'>)
    // clang-format on
    {
        if (checkValidElfJobs(elf1, elf2)) {
            cerr << "Input range error" << endl;
            return (EXIT_FAILURE);
        }
        if (checkElfJobs(elf1, elf2))
            totalOverlap++;
    }
    if (!inputFile.eof()) {
        cerr << "Input file error Error" << endl;
        return (EXIT_FAILURE);
    }
    cout << endl;
    cout << "overlapping jobs = " << totalOverlap << endl;
}
