#include "FrequentPatternEnumeration.h"

void FrequentPatternEnumeration::execute(EquivalenceClass *eq, bool depthFirst,
                                         std::map<int, std::map<int, int>> *coocMapAfter,
                                         std::map<int, std::map<int, int>> *coocMapEquals) {
    bool anyPatternCreated = false;
    auto eqMembers = eq->getClassMembers();
    for (auto it = eqMembers->crbegin(); it != eqMembers->crend(); ++it) {
        std::map<int, int> *cmapX = nullptr;
        std::map<int, int> *cmapX_equals = nullptr;
        int itemX;
        if (coocMapAfter != nullptr || coocMapEquals != nullptr) {
            itemX = (*it)->getClassIdentifier()->getLastElement()->getId();
            cmapX = (coocMapAfter == nullptr) ? nullptr : &coocMapAfter->at(itemX);
            cmapX_equals = (coocMapEquals == nullptr) ? nullptr : &coocMapEquals->at(itemX);
        }

        for (auto jt = it; jt != eqMembers->crend(); ++jt) {
            bool doNotExploreXY = false;
            bool doNotExploreYX = false;
            bool doNotExploreX_Y = false;
            bool doNotExploreY_X = false;
            if (coocMapEquals != nullptr) {
                int itemY = (*jt)->getClassIdentifier()->getLastElement()->getId();
                auto *cmapY = &coocMapEquals->at(itemY);
                int count1 = cmapX_equals == nullptr ? 0 : cmapX_equals->at(itemY);
                int count2 = cmapY == nullptr ? 0 : cmapY->at(itemX);
                doNotExploreYX = count2 == 0 || count2 < minSupport;
                doNotExploreXY = count1 == 0 || count1 < minSupport;
            }
            if (coocMapAfter != nullptr) {
                int itemY = (*jt)->getClassIdentifier()->getLastElement()->getId();
                auto *cmapY = &coocMapAfter->at(itemY);
                int count1 = cmapX == nullptr ? 0 : cmapX->at(itemY);
                int count2 = cmapY == nullptr ? 0 : cmapY->at(itemX);
                doNotExploreY_X = count2 == 0 || count2 < minSupport;
                doNotExploreX_Y = count1 == 0 || count1 < minSupport;
            }
            if (doNotExploreXY && doNotExploreYX && doNotExploreX_Y && doNotExploreY_X) {
                continue;
            }

            std::vector<Pattern *> *extensions = candidateGenerator->generateCandidates((*it)->getClassIdentifier(), (*jt)->getClassIdentifier(),
                                                                                      minSupport, doNotExploreXY, doNotExploreYX, doNotExploreX_Y, doNotExploreY_X);
            for (auto &extension : *extensions) {
                IdList *newIdList = candidateGenerator->join(extension, *it, *jt, minSupport);
                joinCount++;
                if(newIdList != nullptr && newIdList->getSupport() >= minSupport) {
                    anyPatternCreated = true;
                    newIdList->setAppearingSequences(extension);
                    auto *newEq = new EquivalenceClass(extension);
                    newEq->setIdList(newIdList);
                    frequentPatterns++;
                }
            }
        }

        if (depthFirst) {
            if (anyPatternCreated) {
                execute(*it, depthFirst, coocMapAfter, coocMapEquals);
            }
            eqMembers->erase(std::next(it).base());
        }
    }

    if (!depthFirst) {
        if (anyPatternCreated) {
            for (auto it = eqMembers->crbegin(); it != eqMembers->crend(); ++it) {
                execute(*it, depthFirst, coocMapAfter, coocMapEquals);
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
