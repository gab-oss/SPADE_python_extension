#include "FrequentPatternEnumeration.h"
#include <iostream>

void FrequentPatternEnumeration::execute(EquivalenceClass *eq, bool depthFirst) {
    bool anyPatternCreated = false;
    auto eqMembers = eq->getClassMembers();
    for (auto it = eqMembers->crbegin(); it != eqMembers->crend(); ++it) {
        for(auto el : *(*it)->getClassIdentifier()->getElements())
            std::cout << el->getId() << ",";
        std::cout << " | "<< "eq" <<std::endl;

        for (auto jt = it; jt != eqMembers->crend(); ++jt) {
            auto *extensions = candidateGenerator->generateCandidates((*it)->getClassIdentifier(), (*jt)->getClassIdentifier(), minSupport);
            for (auto &extension : *extensions) {
                for(auto el : *extension->getElements())
                    std::cout << el->getId() << ",";
                std::cout << " | ";
                IdList *newIdList = candidateGenerator->join(extension, *it, *jt, minSupport);

                std::cout << std::endl;
                joinCount++;
                if(newIdList != nullptr && newIdList->getSupport() >= minSupport) {
                    anyPatternCreated = true;
                    newIdList->setAppearingSequences(extension);
					frequentPatterns->push_back(extension);
                    auto *newEq = new EquivalenceClass(extension);
                    newEq->setIdList(newIdList);
                    frequentPatternCount++;
					std::cout << newIdList->getSupport() << std::endl;
					insertClassByPrefix(newEq, *it, *jt);
                }
            }
        }

        if (depthFirst) {
            if (anyPatternCreated) {
                execute(*it, depthFirst);
            }
            eqMembers->erase(std::next(it).base());
        }
    }

    if (!depthFirst) {
        if (anyPatternCreated) {
            for (auto it = eqMembers->crbegin(); it != eqMembers->crend(); ++it) {
                execute(*it, depthFirst);
                eqMembers->erase(std::next(it).base());
            }
        }

        eqMembers = nullptr;
    }

}

void FrequentPatternEnumeration::insertClassByPrefix(EquivalenceClass *eq, EquivalenceClass *eqX, EquivalenceClass *eqY) {
    if(eqX->getClassIdentifier()->isPrefix(eq->getClassIdentifier())) {
        eqX->addMember(eq);
    } else {
        eqY->addMember(eq);
    }
}
