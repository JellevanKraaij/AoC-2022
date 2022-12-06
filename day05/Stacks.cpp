#include "Stacks.hpp"

#include <algorithm>

void Stacks::printStacks(std::ostream &stream) const {
    size_t longest = 0;

    for (size_t i = 0; i < _stacks.size(); i++) {
        {
            if (_stacks[i].size() > longest)
                longest = _stacks[i].size();
        }
    }
    if (longest > 0) {
        for (ssize_t line_it = longest - 1; line_it >= 0; line_it--) {
            for (size_t stack_it = 0; stack_it < _stacks.size(); stack_it++) {
                if (line_it < _stacks[stack_it].size()) {
                    stream << '[' << _stacks[stack_it][line_it] << ']';
                } else
                    stream << "   ";
                if (stack_it + 1 < _stacks.size())
                    stream << ' ';
            }
            stream << std::endl;
        }
    }
    for (size_t i = 0; i < _stacks.size(); i++) {
        char c;
        stream << ' ' << _stackNames[i] << ' ';
        if (i + 1 < _stacks.size())
            stream << ' ';
    }
}

std::vector<std::string> Stacks::_createChunks(const std::string &input) {
    std::vector<std::string> result;
    if ((input.length() + 1) % 4 != 0) {
        throw(std::invalid_argument("invalid line format"));
    }
    for (size_t i = 0; i < input.length() + 1; i += 4) {
        if (i + 3 < input.length() && input[i + 3] != ' ') {
            throw(std::invalid_argument("invalid line format"));
        }
        result.push_back(input.substr(i, 3));
    }
    return (result);
}

bool Stacks::_parseNames(const std::string &input) {
    _Chunks chunks;
    try {
        chunks = Stacks::_createChunks(input);
    } catch (std::invalid_argument) {
        return (false);
    }
    for (size_t i = 0; i < chunks.size(); i++) {
        if (chunks[i][0] != ' ' || chunks[i][2] != ' ')
            return (false);
        _StackName name = chunks[i][1];
        if (std::find(_stackNames.begin(), _stackNames.end(), name) != _stackNames.end())
            return (false);
        _stackNames.push_back(name);
    }
    _stacks.resize(_stackNames.size());
    return (true);
}

bool Stacks::_parseStacks(const std::vector<std::string> &input) {
    for (ssize_t input_it = input.size() - 1; input_it >= 0; input_it--) {
        _Chunks chunks;
        try {
            chunks = Stacks::_createChunks(input[input_it]);
        } catch (std::invalid_argument) {
            return (false);
        }
        if (chunks.size() != _stacks.size())
            return (false);
        for (size_t stack_it = 0; stack_it < _stacks.size(); stack_it++) {
            if (chunks[stack_it] == "   ")
                continue;
            if (chunks[stack_it][0] != '[' || chunks[stack_it][2] != ']')
                return (false);
            _stacks[stack_it].push_back(chunks[stack_it][1]);
        }
    }
    return (true);
}

bool Stacks::parseStacks(std::vector<std::string> input) {
    if (input.empty())
        return (false);
    if (!_parseNames(input.back()))
        return (false);
    input.pop_back();
    if (!_parseStacks(input))
        return (false);
    return (true);
}

bool Stacks::_moveStacks(const size_t src, const size_t dst, const unsigned int amount, const MoveType type) {
    if (amount > _stacks[src].size())
        return (false);
    if (type == AllInOne) {
        std::move(_stacks[src].end() - amount, _stacks[src].end(), std::back_inserter(_stacks[dst]));
        _stacks[src].erase(_stacks[src].end() - amount, _stacks[src].end());
    } else {
        for (unsigned i = 0; i < amount; i++) {
            _stacks[dst].push_back(_stacks[src].back());
            _stacks[src].pop_back();
        }
    }
    return (true);
}

bool Stacks::executeMove(const std::string &move, const MoveType type) {
    unsigned int amount;
    _StackName source;
    _StackName destination;

    char end;

    if (sscanf(std::string(move + '\n').c_str(), "move %u from %c to %c%c", &amount, &source, &destination, &end) != 4 || end != '\n')
        return (false);
    const std::vector<_StackName>::iterator source_it = std::find(_stackNames.begin(), _stackNames.end(), source);
    const std::vector<_StackName>::iterator destination_it = std::find(_stackNames.begin(), _stackNames.end(), destination);
    const size_t source_idx = std::distance(_stackNames.begin(), source_it);
    const size_t dest_idx = std::distance(_stackNames.begin(), destination_it);
    if (source_it == _stackNames.end() || destination_it == _stackNames.end())
        return (false);

    return (_moveStacks(source_idx, dest_idx, amount, type));
}
