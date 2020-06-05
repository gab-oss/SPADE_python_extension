#ifndef SPADE_PATTERN_H
#define SPADE_PATTERN_H

#include <vector>
#include "Item.h"

class Pattern {
    std::vector<Item*> *elements = new std::vector<Item*>;
    std::vector<bool> *appearingIn = new std::vector<bool>;

public:
    explicit Pattern(std::vector<Item*> *elements) : elements(elements) {}

    bool isPrefix(Pattern *p) {
        bool output = false;
        std::vector<Item*> *pElements = p->getElements();
        pElements->pop_back();
        if (pElements->back() == elements->back())
            output = true;
        return output;
    }

    std::vector<Item*> *getElements() {
        return elements;
    }

    Item* getLastElement() {
        if (elements->empty())
            return nullptr;
        return elements->back();
    }

    void setAppearingIn(std::vector<bool> *appearingIn) {
        this->appearingIn = appearingIn;
    }

    std::vector<bool> *getAppearingIn() {
        return appearingIn;
    }

    void add(Item* item) {
        elements->push_back(item);
    }

    Pattern *clonePattern(){
        auto *elementsCopy = new std::vector<Item*>(*elements);
        auto *clone = new Pattern(elementsCopy);
        return clone;
    }

    int compareTo(Pattern *p){
        int comp;
        if(elements->back()->getId() > p->elements->back()->getId())
            comp = 1;
        else if(elements->back()->getId() < p->elements->back()->getId())
            comp = -1;
        else if(elements->back()->isEqualRelation() && p->elements->back()->isEqualRelation())
            comp = 0;
        else if(!elements->back()->isEqualRelation() && p->elements->back()->isEqualRelation())
            comp = -1;
        else
            comp = 1;

        return comp;
    }
};


#endif //SPADE_PATTERN_H
