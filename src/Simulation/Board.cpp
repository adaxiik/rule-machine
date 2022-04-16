#include "Board.hpp"

Board::Board(size_t width, size_t height)
{
    this->width = width;
    this->height = height;
    this->board = new Atom[width * height];
    this->state = new Atom[width * height];
    this->AddElement(0, new Element("void", 0, BGRA{0, 0, 0, 255}));
    for (size_t i = 0; i < width * height; i++)
    {
        this->board[i].id = 0;
        this->state[i].id = 0;
        this->board[i].updated = false;
        this->state[i].updated = false;
    }
}

void Board::Update()
{
    this->Synchronize();
    //#pragma omp parallel for
    for (size_t y = 0; y < this->width; y++)
    {
        for (size_t x = 0; x < this->width; x++)
        {
            this->GetElement(this->GetAtom(x, y).id)->ApplyRules(this, x, y);          
            
            for (auto &rule : this->globalRules)
                rule.ApplyGlobalRule(this, x, y);
        }
    }
    
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
    this->board[x + y * this->width].id = element;
    this->board[x + y * this->width].updated = true;
}

void Board::SetAtom(size_t x, size_t y, ElementID element, bool update)
{
    if (x >= this->width || y >= this->height)
        return;
    this->board[x + y * this->width].id = element;
    this->state[x + y * this->width].updated = update;
}

Atom Board::GetAtom(size_t x, size_t y) const
{
    if (x >= this->width || y >= this->height)
        return Atom{0, false};
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
    return this->GetElement(this->GetAtom(x, y).id)->GetColor();
}

void Board::Synchronize()
{
    for (size_t i = 0; i < this->width * this->height; i++)
    {
        this->board[i].updated = false;
        this->state[i] = this->board[i];
    }
}