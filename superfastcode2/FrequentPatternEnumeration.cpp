#include "FrequentPatternEnumeration.h"
#include <iostream>

void FrequentPatternEnumeration::execute(EquivalenceClass *eq, bool depthFirst) {
    bool anyPatternCreated = false;
    auto eqMembers = eq->getClassMembers();
	for (auto it = eqMembers->crbegin(); it != eqMembers->crend(); ++it) {
        for (auto jt = it; jt != eqMembers->crend(); ++jt) {
            auto *extensions = candidateGenerator->generateCandidates((*it)->getClassIdentifier(), (*jt)->getClassIdentifier(), minSupport);
			
			for (auto &extension : *extensions) {
                IdList *newIdList = candidateGenerator->join(extension, *it, *jt);

                if(newIdList != nullptr && newIdList->getSupport() >= minSupport) {
                    anyPatternCreated = true;
                    newIdList->setAppearingSequences(extension);
					frequentPatterns->push_back(extension);
                    auto *newEq = new EquivalenceClass(extension);
                    newEq->setIdList(newIdList);
                    frequentPatternCount++;
					insertClassByPrefix(newEq, *it, *jt);
                }
            }
        }

        if (depthFirst) {

			eqMembers->erase(std::next(it).base());

			if (anyPatternCreated) {
                execute(*it, depthFirst);
            }
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
