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

struct Atom
{
    ElementID id;
    bool updated;
};

class Board
{
private:
    size_t width, height;
    Atom* board;
    Atom* state;

    std::unordered_map<ElementID, Element*> elements;
    std::vector<Rule> globalRules;
    void Synchronize();
public:
    Board(size_t width, size_t height);
    ~Board();

    void AddElement(ElementID id, Element* element);
    void AddGlobalRule(Rule rule);

    Atom GetAtom(size_t x, size_t y) const;
    void SetAtom(size_t x, size_t y, ElementID element);
    void SetAtom(size_t x, size_t y, ElementID element, bool update);
    
    Element* GetElement(ElementID id);

    BGRA GetPixelColorAt(size_t x, size_t y);
    void Update();
};
