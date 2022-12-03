#include <fstream>
#include <iostream>
#include <map>

using namespace std;

#define stringify(name) #name;

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

const map<char, Move> convertOpponent = {
    {'A', Rock},
    {'B', Paper},
    {'C', Scissor},
};

const map<char, Result> convertRoundResult = {
    {'X', Loss},
    {'Y', Draw},
    {'Z', Win},
};

const map<pair<Move, Result>, Move> checkMyMove = {
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
    int totalScore;
    while (getline(inputFile, line) && !line.empty()) {
        Move opponentMove;
        Result roundResult;
        try {
            opponentMove = convertOpponent.at(line[0]);
            roundResult = convertRoundResult.at(line[2]);
        } catch (const std::out_of_range &e) {
            cerr << "Invalid input file" << endl;
            exit(EXIT_FAILURE);
        }
        totalScore += static_cast<int>(roundResult);
        totalScore += static_cast<int>(checkMyMove.at({opponentMove, roundResult}));

        cout << opponentMove << " : " << checkMyMove.at({opponentMove, roundResult}) << " = " << roundResult << endl;
    }
    cout << endl;
    cout << "totalScore = " << totalScore << endl;
}
