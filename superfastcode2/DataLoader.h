#ifndef SPADE_SEQUENCEDATABASE_H
#define SPADE_SEQUENCEDATABASE_H

#include <string>
#include <vector>
#include "EquivalenceClass.h"

class DataLoader {

    std::map<Item*, EquivalenceClass*> *frequentItems = new std::map<Item*, EquivalenceClass*>;
    std::map<int, std::map<int, std::vector<Item*>*>*> *sequences = new std::map<int, std::map<int, std::vector<Item*>*>*>;
    double absSupport;
public:
    void loadFile(std::string path, double minSupport);

    void addSequence(int seqId, std::map<int, std::vector<int>*>* integers);

    std::vector<EquivalenceClass*>* getFrequentItems() {
        auto* items = new std::vector<EquivalenceClass*>;
        for (auto &frequentItem : *frequentItems) {
            items->push_back(frequentItem.second);
        }
        return items;
    }

    void reduceDatabase(std::vector<Item*> *items);

	double getAbsSupport() {
	    return absSupport;
	}
};


#endif //SPADE_SEQUENCEDATABASE_H
