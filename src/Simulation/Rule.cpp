#include "Rule.hpp"

Rule::Rule(std::vector<std::vector<ElementID>> input, std::vector<std::vector<ElementID>> output, ElementID owner)
{
    this->input = input;
    this->output = output;
    this->owner = owner;
}

bool Rule::ApplyRule(Board *board, size_t x0, size_t y0)
{
    int offsetX = 0;
    //int offsetY = 0;

    for (; offsetX < (int)this->input[0].size(); offsetX++)
        if (this->input[0][offsetX] == this->owner)
            break;

    for (size_t y = 0; y < this->input.size(); y++)
        for (size_t x = 0; x < this->input[y].size(); x++)
            if (board->GetAtom(x0 + x - offsetX, y0 + y) != this->input[y][x])
                return false;

    for (size_t y = 0; y < this->output.size(); y++)
    {
        for (size_t x = 0; x < this->output[y].size(); x++)
        {
            board->SetAtom(x0 + x - offsetX, y0 + y, this->output[y][x]);
        }
    }

    // board->SetAtom(x0 + x - offsetX, y0 + y, this->output[y][x]);
    

    return true;
}

bool Rule::ApplyGlobalRule(Board *board, size_t x0, size_t y0)
{
    for (size_t y = 0; y < this->input.size(); y++)
        for (size_t x = 0; x < this->input[y].size(); x++)
            if (board->GetAtom(x0 + x, y0 + y) != this->input[y][x])
                return false;

//ono ho to možná rewritne ??
    for (size_t y = 0; y < this->output.size(); y++)
    {
        for (size_t x = 0; x < this->output[y].size(); x++)
        {
            //board->SetAtom(x0 + x, y0 + y, this->output[y][x]);
            if(this->output[y][x] != board->GetAtom(x0 + x, y0 + y))
                board->SetAtom(x0 + x, y0 + y, this->output[y][x]);
        }
    }

    return true;
}

Rule::~Rule()
{
}
