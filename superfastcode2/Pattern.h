#ifndef SPADE_PATTERN_H
#define SPADE_PATTERN_H

#include <vector>
#include "Item.h"
#include <iostream>

class Pattern {
    std::vector<Item*> *elements = new std::vector<Item*>;
    std::vector<bool> *appearingIn = new std::vector<bool>(0, false);

public:
    explicit Pattern(std::vector<Item*> *elements) : elements(elements) {
        appearingIn = new std::vector<bool>(elements->size(), false);
    }

	bool isPrefix(Pattern *p) {
		return p->getElements()->at(p->getElements()->size() - 2) == elements->back();
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

	int getSupport() {
		return std::count(appearingIn->begin(), appearingIn->end(), true);
	}

    void add(Item* item) {
        elements->push_back(item);
    }

    Pattern *clonePattern(){
        auto elementsCopy = new std::vector<Item*>(*elements);
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
