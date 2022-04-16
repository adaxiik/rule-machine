#pragma once
#include <iostream>
#include "Board.hpp"
class Board;
class Rule
{
private:
    std::vector<std::vector<ElementID>> input;
    std::vector<std::vector<ElementID>> output;
    ElementID owner;
public:
    Rule(std::vector<std::vector<ElementID>> input, std::vector<std::vector<ElementID>> output, ElementID owner);
    bool ApplyRule(Board* board, size_t x, size_t y);
    bool ApplyGlobalRule(Board* board, size_t x, size_t y);
    ~Rule();
};
