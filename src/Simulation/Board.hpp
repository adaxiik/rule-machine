#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

typedef size_t ElementID;
#include "Element.hpp"
#include "Rule.hpp"



class Element;
struct BGRA;


class Board
{
private:
    size_t width, height;
    ElementID* board;
    ElementID* state;

    std::unordered_map<ElementID, Element*> elements;
    std::vector<Rule> globalRules;
    void Synchronize();
public:
    Board(size_t width, size_t height);
    ~Board();

    void AddElement(ElementID id, Element* element);
    void AddGlobalRule(Rule rule);

    ElementID GetAtom(size_t x, size_t y) const;
    void SetAtom(size_t x, size_t y, ElementID element);
    
    Element* GetElement(ElementID id);

    BGRA GetPixelColorAt(size_t x, size_t y);
    void Update();
};
