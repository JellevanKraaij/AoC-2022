#include <fstream>
#include <iostream>
#include <map>

using namespace std;

enum Move {
    Rock = 1,
    Paper = 2,
    Scissor = 3,
};

enum Result {
    Win = 6,
    Draw = 3,
    Loss = 0,
};

const map<char, Move> looupOpponentMove = {
    {'A', Rock},
    {'B', Paper},
    {'C', Scissor},
};

const map<char, Result> convertRoundResult = {
    {'X', Loss},
    {'Y', Draw},
    {'Z', Win},
};

const map<pair<Move, Result>, Move> lookupResult = {
    {{Rock, Loss}, Scissor}, {{Rock, Draw}, Rock},     {{Rock, Win}, Paper},       {{Paper, Loss}, Rock},  {{Paper, Draw}, Paper},
    {{Paper, Win}, Scissor}, {{Scissor, Loss}, Paper}, {{Scissor, Draw}, Scissor}, {{Scissor, Win}, Rock},
};

std::ostream &operator<<(std::ostream &ostream, const Move &move) {
    switch (move) {
        case Rock:
            ostream << "rock";
            break;
        case Paper:
            ostream << "paper";
            break;
        case Scissor:
            ostream << "scissor";
            break;
    }
    return (ostream);
}

std::ostream &operator<<(std::ostream &ostream, const Result &res) {
    switch (res) {
        case Win:
            ostream << "win";
            break;
        case Draw:
            ostream << "draw";
            break;
        case Loss:
            ostream << "loss";
            break;
    }
    return (ostream);
}

template <char C>
istream &expect(istream &s) {
    if (s.flags() & ios_base::skipws) s >> ws;
    if (s.peek() == C)
        s.ignore();
    else
        s.setstate(std::ios_base::failbit);
    return (s);
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
    int totalScore = 0;
    char oppC, myC;

    // clang-format off
    while (inputFile >> noskipws >> oppC >> expect<' '> >> myC >> expect<'\n'>)
    // clang-format on
    {
        Move opponentMove;
        Result roundResult;
        try {
            opponentMove = looupOpponentMove.at(line[0]);
            roundResult = convertRoundResult.at(line[2]);
        } catch (const std::out_of_range &e) {
            cerr << "Invalid input file" << endl;
            exit(EXIT_FAILURE);
        }
        totalScore += static_cast<int>(roundResult);
        totalScore += static_cast<int>(lookupResult.at({opponentMove, roundResult}));

        cout << opponentMove << " : " << lookupResult.at({opponentMove, roundResult}) << " = " << roundResult << endl;
    }
    cout << endl;
    cout << "totalScore = " << totalScore << endl;
}
