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

const map<char, Move> lookupMyMove = {
    {'X', Rock},
    {'Y', Paper},
    {'Z', Scissor},
};

const map<pair<Move, Move>, Result> lookupResult = {
    {{Rock, Rock}, Draw},    {{Rock, Paper}, Win},   {{Rock, Scissor}, Loss},  {{Paper, Rock}, Loss},      {{Paper, Paper}, Draw},
    {{Paper, Scissor}, Win}, {{Scissor, Rock}, Win}, {{Scissor, Paper}, Loss}, {{Scissor, Scissor}, Draw},
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

    int totalScore = 0;
    char myC, oppC;

    // clang-format off
    while (inputFile >> noskipws >> oppC >> expect<' '> >> myC >> expect<'\n'>)
    // clang-format on
    {
        Move opponentMove;
        Move myMove;

        try {
            opponentMove = looupOpponentMove.at(oppC);
            myMove = lookupMyMove.at(myC);
        } catch (const std::out_of_range &e) {
            cerr << "Invalid input file" << endl;
            return (EXIT_FAILURE);
        }

        Result result = lookupResult.at({opponentMove, myMove});

        totalScore += static_cast<int>(myMove);
        totalScore += static_cast<int>(result);

        cout << opponentMove << " : " << myMove << " = " << lookupResult.at({opponentMove, myMove}) << endl;
    }
    cout << endl;
    cout << "totalScore = " << totalScore << endl;
}
