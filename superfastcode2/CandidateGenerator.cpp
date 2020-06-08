#include "CandidateGenerator.h"

std::vector<Pattern *> *CandidateGenerator::generateCandidates(Pattern *p1, Pattern *p2, double minSupport) {
    auto *candidates = new std::vector<Pattern *>;
    auto *joinBitmap = new std::vector<bool>(p1->getAppearingIn()->size());
    std::copy(p1->getAppearingIn()->begin(), p1->getAppearingIn()->end(), joinBitmap->begin());

    for (int i = 0; i < joinBitmap->size(); i++) {
        if (p2->getAppearingIn()->size() <= i) {
            joinBitmap->at(i) = false;
        } else {
            joinBitmap->at(i) = joinBitmap->at(i) && p2->getAppearingIn()->at(i);
        }
    }

    if (std::count(joinBitmap->begin(), joinBitmap->end(), true) >= minSupport) {
        auto p1Last = p1->getLastElement();
        auto p2Last = p2->getLastElement();
        auto p1LastRel = p1Last->isEqualRelation();
        auto p2LastRel = p2Last->isEqualRelation();

        if (!p1LastRel && !p2LastRel) {
            if (p1Last->getId() != p2Last->getId()) {
                Pattern *candEqRel = nullptr;
                if (p1->compareTo(p2) < 0) {
                    candEqRel = p1->clonePattern();
                    candEqRel->add(new Item(p2Last->getId(), true));
                } else {
                    candEqRel = p2->clonePattern();
                    candEqRel->add(new Item(p1Last->getId(), true));
                }
                candidates->push_back(candEqRel);

                Pattern *cand = p2->clonePattern();
                cand->add(p1Last);
                candidates->push_back(cand);

            }

            Pattern *cand = p1->clonePattern();
            cand->add(p2Last);
            candidates->push_back(cand);

        } else if (p1LastRel && p2LastRel) {
            Pattern *candEqRel = nullptr;
            if (p1->compareTo(p2) < 0) {
                candEqRel = p1->clonePattern();
                candEqRel->add(new Item(p2Last->getId(), true));
                candidates->push_back(candEqRel);
            } else if (p1->compareTo(p2) > 0) {
                candEqRel = p2->clonePattern();
                candEqRel->add(new Item(p1Last->getId(), true));
                candidates->push_back(candEqRel);
            }
        } else {
            Pattern *candBefRel = nullptr;
            if (p1LastRel) {
                candBefRel = p1->clonePattern();
                candBefRel->add(p2Last);
            } else {
                candBefRel = p2->clonePattern();
                candBefRel->add(p1Last);
            }
            candidates->push_back(candBefRel);
        }
    }
    return candidates;
}

IdList *CandidateGenerator::join(Pattern *extension, EquivalenceClass *e1, EquivalenceClass *e2) {

    Item *lastButOne = extension->getElements()->at(extension->getElements()->size() - 2);
    Item *last = extension->getLastElement();
    Item *lastFromEq = e2->getClassIdentifier()->getLastElement();

    if (last->isEqualRelation()) {
        if (lastButOne != last)
            return e1->getIdList()->join(e2->getIdList(), true);

    } else {
        if (lastFromEq == last) {
            return e1->getIdList()->join(e2->getIdList(), false);
        } else {
            return e2->getIdList()->join(e1->getIdList(), false);
        }
    }

    return nullptr;
}
