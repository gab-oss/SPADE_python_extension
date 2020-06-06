#include "Spade.h"
#include "EquivalenceClass.h"
#include "FrequentPatternEnumeration.h"
#include "SequenceDatabase.h"

void Spade::run(std::string filepath, double sup, bool depthFirst) {
    auto *db = new SequenceDatabase();
    db->loadFile(filepath, sup);

    frequentItems = db->getFrequentItems();
    auto *rootClass = new EquivalenceClass();

	frequentPatterns = getPatterns(frequentItems);
    for(auto frequentItem : *frequentItems) {
        rootClass->addMember(frequentItem);
    }

    auto frequentPatternEnumeration = new FrequentPatternEnumeration(new CandidateGenerator(), db->getAbsSupport(sup));
    frequentPatternEnumeration->setFrequentPatterns(frequentItems->size());
    frequentPatternEnumeration->execute(rootClass, depthFirst, nullptr, nullptr);

	auto *patterns = frequentPatternEnumeration->getFrequentPatterns();
	frequentPatterns->insert(frequentPatterns->end(), patterns->begin(), patterns->end());
    frequentPatternCount = frequentPatternEnumeration->getFrequentPatternCount();
    joinCount = frequentPatternEnumeration->getJoinCount();
}

std::vector<Pattern*> *Spade::getPatterns(std::vector<EquivalenceClass*> *frequentItems) {
    auto *patterns = new std::vector<Pattern*>;
    for(auto frequentItem : *frequentItems) {
        patterns->push_back(frequentItem->getClassIdentifier());
    }
    return patterns;
}