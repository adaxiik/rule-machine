#include "Element.hpp"

Element::Element(std::string name, ElementID id, BGRA color)
{
    this->name = name;
    this->id = id;
    this->color = color;
}

Element::~Element()
{
}

void Element::AddRule(Rule rule)
{
    this->rules.push_back(rule);
}

std::string Element::GetName() const
{
    return this->name;
}

ElementID Element::GetID() const
{
    return this->id;
}

BGRA Element::GetColor() const
{
    return this->color;
}

void Element::ApplyRules(Board* board, size_t x, size_t y)
{
    for (size_t i = 0; i < this->rules.size(); i++)
    {
        if(this->rules[i].ApplyRule(board, x, y))
            return;
    }
}







bool operator==(const Element &lhs, const Element &rhs)
{
    return lhs.id == rhs.id;
}

bool operator!=(const Element &lhs, const Element &rhs)
{
    return !(lhs == rhs);
}
