#include "Board.hpp"

Board::Board(size_t width, size_t height)
{
    this->width = width;
    this->height = height;
    this->board = new Atom[width * height];
    this->AddElement(0,new Element("void",0,BGRA{0,0,0,255}));
    for (size_t i = 0; i < width * height; i++)
    {
        this->board[i].id = 0;
        this->board[i].simulated = false;
    }
    
}

void Board::Update()
{
    for (size_t i = 0; i < this->width * this->height; i++)
        this->board[i].simulated = false;

    for (size_t y = 0; y < this->height; y++)
    {
        for (size_t x = 0; x < this->width; x++)
        {
            Atom atom = this->GetAtom(x, y);
            if(!atom.simulated)
                this->GetElement(atom.id)->ApplyRules(this, x, y);                
        }
    }  
}

Board::~Board()
{
    delete[] board;
    for(auto element : this->elements)
        delete element.second;
}

void Board::SetAtom(size_t x, size_t y, ElementID element)
{
    if(x >= this->width || y >= this->height)
        return;
    this->board[x + y * this->width].id = element;
    this->board[x + y * this->width].simulated = true;
}

Atom Board::GetAtom(size_t x, size_t y) const
{
    if(x >= this->width || y >= this->height)
        return Atom{0,false};
    return this->board[x + y * this->width];
}

Element* Board::GetElement(ElementID id) 
{
    return this->elements[id];
}

void Board::AddElement(ElementID id, Element* element)
{
    this->elements[id] = element;
}

void Board::DrawPixels(BGRA* pixels)
{
    for (size_t i = 0; i < this->width*this->height; i++)
    {
        pixels[i] = this->GetElement(this->board[i].id)->GetColor();
    }
}