#include "Board.hpp"

Board::Board(size_t width, size_t height)
{
    this->width = width;
    this->height = height;
    this->board = new ElementID[width * height];
    this->state = new ElementID[width * height];
    this->AddElement(0, new Element("void", 0, BGRA{0, 0, 0, 255}));
    for (size_t i = 0; i < width * height; i++)
    {
        this->board[i] = 0;
        this->state[i] = 0;
    }
}

void Board::Update()
{

    for (int64_t y = this->height - 1; y >= 0; y--)
    {
        for (size_t x = 0; x < this->width; x++)
        {
            ElementID atom = this->GetAtom(x, y);
            this->GetElement(atom)->ApplyRules(this, x, y);          
            
            for (auto &rule : this->globalRules)
                rule.ApplyGlobalRule(this, x, y);
        }
    }
    this->Synchronize();
    
}
void Board::AddGlobalRule(Rule rule)
{
    this->globalRules.push_back(rule);
}

Board::~Board()
{
    delete[] board;
    delete[] state;
    for (auto element : this->elements)
        delete element.second;

    
}

void Board::SetAtom(size_t x, size_t y, ElementID element)
{
    if (x >= this->width || y >= this->height)
        return;
    this->board[x + y * this->width] = element;
}

ElementID Board::GetAtom(size_t x, size_t y) const
{
    if (x >= this->width || y >= this->height)
        return 0;
    return this->state[x + y * this->width];
}

Element *Board::GetElement(ElementID id)
{
    return this->elements[id];
}

void Board::AddElement(ElementID id, Element *element)
{
    this->elements[id] = element;
}

BGRA Board::GetPixelColorAt(size_t x, size_t y)
{
    return this->GetElement(this->GetAtom(x, y))->GetColor();
}

void Board::Synchronize()
{
    for (size_t i = 0; i < this->width * this->height; i++)
        this->state[i] = this->board[i];
}