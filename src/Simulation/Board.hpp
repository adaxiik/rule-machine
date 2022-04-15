#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>

typedef size_t ElementID;
#include "Element.hpp"
#include "Rule.hpp"

struct Atom
{
    ElementID id;
    bool simulated;
};
class Element;
struct BGRA;

class Board
{
private:
    size_t width, height;
    Atom* board;
    std::map<ElementID, Element*> elements;
public:
    Board(size_t width, size_t height);

    void AddElement(ElementID id, Element* element);


    Atom GetAtom(size_t x, size_t y) const;
    void SetAtom(size_t x, size_t y, ElementID element);
    
    Element* GetElement(ElementID id);

    void DrawPixels(BGRA* pixels);
    void Update();
    ~Board();
};
