#include "FrequentPatternEnumeration.h"
#include <iostream>

void FrequentPatternEnumeration::execute(EquivalenceClass *eq, bool depthFirst) {
    bool anyPatternCreated = false;
    auto eqMembers = eq->getClassMembers();
	for (auto it = eqMembers->crbegin(); it != eqMembers->crend(); ++it) {

		std::cout << "start:";
		for (auto m : *(*it)->getClassMembers()){
			for (auto n : *m->getClassIdentifier()->getElements())
				std::cout << n->getId() << ", ";
		std::cout << " | ";
		}
		std::cout << std::endl;

        for (auto jt = it; jt != eqMembers->crend(); ++jt) {
            auto *extensions = candidateGenerator->generateCandidates((*it)->getClassIdentifier(), (*jt)->getClassIdentifier(), minSupport);

			std::cout << "gener:";
			for (auto m : *(*it)->getClassMembers()) {
				for (auto n : *m->getClassIdentifier()->getElements())
					std::cout << n->getId() << ", ";
				std::cout << " | ";
			}
			std::cout << std::endl;
			
			for (auto &extension : *extensions) {

				std::cout << "extension:";
				for (auto e : *extension->getElements())
					std::cout << e->getId() << ", ";
				std::cout << std::endl;

                IdList *newIdList = candidateGenerator->join(extension, *it, *jt);
				joinCount++;

				std::cout << "join:";
				for (auto m : *(*it)->getClassMembers()) {
					for (auto n : *m->getClassIdentifier()->getElements())
						std::cout << n->getId() << ", ";
					std::cout << " | ";
				}
				std::cout << std::endl;

                if(newIdList != nullptr && newIdList->getSupport() >= minSupport) {
                    anyPatternCreated = true;
                    newIdList->setAppearingSequences(extension);
					frequentPatterns->push_back(extension);
                    auto *newEq = new EquivalenceClass(extension);
                    newEq->setIdList(newIdList);
                    frequentPatternCount++;
					insertClassByPrefix(newEq, *it, *jt);

					std::cout << "insert:";
					for (auto m : *(*it)->getClassMembers()) {
						for (auto n : *m->getClassIdentifier()->getElements())
							std::cout << n->getId() << ", ";
						std::cout << " | ";
					}
					std::cout << std::endl;
                }
            }
        }

        if (depthFirst) {
			std::cout << "end:";
			for (auto m : *eq->getClassMembers()) {
				for (auto n : *m->getClassIdentifier()->getElements())
					std::cout << n->getId() << ", ";
				std::cout << " | ";
			}
			std::cout << std::endl;

			for (auto id : *(*it)->getClassIdentifier()->getElements())
				std::cout << id->getId() << ", ";
			std::cout << " => ";

			eqMembers->erase(std::next(it).base());

			for (auto id : *(*it)->getClassIdentifier()->getElements())
				std::cout << id->getId() << ", ";
			std::cout << std::endl << std::endl;

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
	std::cout << "new:";
	for (auto n : *eq->getClassIdentifier()->getElements())
		std::cout << n->getId() << ", ";
	std::cout << " | ";
	if(eqX->getClassIdentifier()->isPrefix(eq->getClassIdentifier())) {
		for (auto n : *eq->getClassIdentifier()->getElements())
			std::cout << n->getId() << ", ";
        eqX->addMember(eq);
    } else {
		for (auto n : *eq->getClassIdentifier()->getElements())
			std::cout << n->getId() << ", ";
        eqY->addMember(eq);
    }
	std::cout << std::endl;
}
