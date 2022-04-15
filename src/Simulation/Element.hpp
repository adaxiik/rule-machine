#pragma once
#include "Board.hpp"
#include "Rule.hpp"
#include <string>

class Rule;
class Board;

struct BGRA
{
    u_char b;
    u_char g;
    u_char r;
    u_char a;
};


class Element
{
private:
    std::string name;
    std::vector <Rule> rules;
    ElementID id;
    BGRA color;
public:
    Element(std::string name, ElementID id, BGRA color);
    ~Element();
    void AddRule(Rule rule);

    std::string GetName() const;
    ElementID GetID() const;
    void ApplyRules(Board* board, size_t x, size_t y);
    BGRA GetColor() const;

    friend bool operator==(const Element& lhs, const Element& rhs);
    friend bool operator!=(const Element& lhs, const Element& rhs);



};
