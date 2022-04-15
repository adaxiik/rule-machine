#include "Rule.hpp"

Rule::Rule(std::vector<std::vector<ElementID>> input, std::vector<std::vector<ElementID>> output)
{
    this->input = input;
    this->output = output;
}

bool Rule::ApplyRule(Board *board, size_t x, size_t y)
{
    for (size_t i = 0; i < this->input.size(); i++)
        for (size_t j = 0; j < this->input[i].size(); j++)
            if (board->GetAtom(x + j, y + i).id != this->input[i][j] || board->GetAtom(x + j, y + i).simulated)
                return false;

    for (size_t i = 0; i < this->output.size(); i++)
        for (size_t j = 0; j < this->output[i].size(); j++)
            board->SetAtom(x + j, y + i, this->output[i][j]);

    return true;
}

Rule::~Rule()
{
}
