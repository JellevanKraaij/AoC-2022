#pragma once

#include <istream>
#include <ostream>
#include <string>
#include <vector>

class Stacks {
   public:
    enum MoveType { OneByOne, AllInOne };

    bool parseStacks(std::vector<std::string> input);
    void printStacks(std::ostream &stream) const;
    bool executeMove(const std::string &move, const MoveType type);

   private:
    using _StackName = char;
    using _ElemData = char;

    using _Chunks = std::vector<std::string>;

    std::vector<_StackName> _stackNames;
    std::vector<std::vector<_ElemData>> _stacks;

    static _Chunks _createChunks(const std::string &input);
    bool _parseNames(const std::string &input);
    bool _parseStacks(const std::vector<std::string> &input);
    bool _moveStacks(const size_t src, const size_t dst, const unsigned int amount, const MoveType type);
};
