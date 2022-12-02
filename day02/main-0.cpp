#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

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

const map<char, Move> convertResponse = {
    {'X', Rock},
    {'Y', Paper},
    {'Z', Scissor},
};

const map<pair<Move, Move>, Result> checkMyMove = {
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
        Move myResponse;
        try {
            opponentMove = convertOpponent.at(line[0]);
            myResponse = convertResponse.at(line[2]);
        } catch (const std::out_of_range &e) {
            cerr << "Invalid input file" << endl;
            exit(EXIT_FAILURE);
        }
        totalScore += static_cast<int>(myResponse);
        totalScore += static_cast<int>(checkMyMove.at({opponentMove, myResponse}));

        cout << opponentMove << " : " << myResponse << " = " << checkMyMove.at({opponentMove, myResponse}) << endl;
    }
    cout << endl;
    cout << "totalScore = " << totalScore << endl;
}
