#pragma once
#include <iostream>
#include "Board.hpp"
class Board;
class Rule
{
private:
    std::vector<std::vector<ElementID>> input;
    std::vector<std::vector<ElementID>> output;
public:
    Rule(std::vector<std::vector<ElementID>> input, std::vector<std::vector<ElementID>> output);
    bool ApplyRule(Board* board, size_t x, size_t y);
    ~Rule();
};
