#include "CandidateGenerator.h"

std::vector<Pattern *> *CandidateGenerator::generateCandidates(Pattern *p1, Pattern *p2, double minSupport,
                                                               bool doNotExploreXY, bool doNotExploreYX,
                                                               bool doNotExploreX_Y, bool doNotExploreY_X) {
    auto *candidates = new std::vector<Pattern *>;
    auto *joinBitmap = new std::vector<bool>(*(p1->getAppearingIn()));
    if (joinBitmap->size() >= minSupport) {
        auto p1Last = p1->getLastElement();
        auto p2Last = p2->getLastElement();
        auto p1LastRel = p1Last->isEqualRelation();
        auto p2LastRel = p2Last->isEqualRelation();

        if (p1LastRel && !p2LastRel) {
            if (p1Last->getId() == p2Last->getId()) {
                Pattern *candEqRel = nullptr;
                if (p1->compareTo(p2) < 0 && !doNotExploreXY) {
                    candEqRel = p1->clonePattern();
                    candEqRel->add(new Item(p2Last->getId(), true));
                } else if (!doNotExploreYX) {
                    candEqRel = p2->clonePattern();
                    candEqRel->add(new Item(p1Last->getId(), true));
                }
                if (candEqRel != nullptr)
                    candidates->push_back(candEqRel);

                if (!doNotExploreY_X) {
                    Pattern *cand = p2->clonePattern();
                    cand->add(p1Last);
                    candidates->push_back(cand);
                }
            }

            if (!doNotExploreX_Y) {
                Pattern *cand = p1->clonePattern();
                cand->add(p2Last);
                candidates->push_back(cand);
            }

        } else if (p1LastRel && p2LastRel) {
            Pattern *candEqRel = nullptr;
            if (p1->compareTo(p2) < 0 && !doNotExploreXY) {
                candEqRel = p1->clonePattern();
                candEqRel->add(new Item(p2Last->getId(), true));
                candidates->push_back(candEqRel);
            } else if (p1->compareTo(p2) < 0 && !doNotExploreYX) {
                candEqRel = p2->clonePattern();
                candEqRel->add(new Item(p1Last->getId(), true));
                candidates->push_back(candEqRel);
            }
        } else {
            Pattern *candBefRel = nullptr;
            if (p1LastRel && !doNotExploreX_Y) {
                candBefRel = p1->clonePattern();
                candBefRel->add(p2Last);
            } else if (!doNotExploreY_X) {
                candBefRel = p2->clonePattern();
                candBefRel->add(p1Last);
            }
            if (candBefRel != nullptr) {
                candidates->push_back(candBefRel);
            }
        }
    }
    return candidates;
}

IdList *CandidateGenerator::join(Pattern *extension, EquivalenceClass *e1, EquivalenceClass *e2, int minSupport) {

    Item *lastButOne = extension->getElements()->at(extension->getElements()->size() - 2);
    Item *last = extension->getLastElement();
    Item *lastFromEq = e2->getClassIdentifier()->getLastElement();

    if (last->isEqualRelation()) {
        if (lastButOne == last)
            return e1->getIdList()->join(e2->getIdList(), true, minSupport);

    } else {
        if (lastFromEq == last) {
            return e1->getIdList()->join(e2->getIdList(), false, minSupport);
        } else {
            return e2->getIdList()->join(e1->getIdList(), false, minSupport);
        }
    }

    return nullptr;
}
