#include "Spade.h"
#include "EquivalenceClass.h"
#include "FrequentPatternEnumeration.h"
#include "DataLoader.h"

void Spade::run(std::string filepath, double sup, bool depthFirst) {
    auto *db = new DataLoader();
    db->loadFile(filepath, sup);
    frequentItems = db->getFrequentItems();
    auto *rootClass = new EquivalenceClass();

	frequentPatterns->at(1) = getPatterns(frequentItems);
    for(auto frequentItem : *frequentItems) {
        rootClass->addMember(frequentItem);
    }
    auto frequentPatternEnumeration = new FrequentPatternEnumeration(new CandidateGenerator(), db->getAbsSupport());
    frequentPatternEnumeration->setFrequentPatterns(frequentItems->size());
    frequentPatternEnumeration->execute(rootClass, depthFirst);

	auto *patterns = frequentPatternEnumeration->getFrequentPatterns();
	addPatterns(patterns);
    frequentPatternCount = frequentPatternEnumeration->getFrequentPatternCount();
}

std::vector<Pattern*> *Spade::getPatterns(std::vector<EquivalenceClass*> *frequentItems) {
    auto *patterns = new std::vector<Pattern*>;
    for(auto frequentItem : *frequentItems) {
        patterns->push_back(frequentItem->getClassIdentifier());
    }
    return patterns;
}