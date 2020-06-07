#ifndef SPADE_EQUIVALENCECLASS_H
#define SPADE_EQUIVALENCECLASS_H

#include <deque>
#include "Pattern.h"
#include "IdList.h"

class EquivalenceClass {

    Pattern *classId;
    IdList *idList;
    std::deque<EquivalenceClass *> *members = new std::deque<EquivalenceClass *>;
public:
    explicit EquivalenceClass(Pattern *classId = nullptr, IdList *idList = nullptr,
                     std::deque<EquivalenceClass *> *members = new std::deque<EquivalenceClass *>) : classId(classId), idList(idList),
                                                                         members(members) {}

    void addMember(EquivalenceClass *eqClass) { members->push_back(eqClass); }

    void setIdList(IdList *idList) { this->idList = idList; }

    IdList *getIdList() { return idList; }

    Pattern *getClassIdentifier() const { return classId; }

    std::deque<EquivalenceClass *> *getClassMembers() const { return members; }
};


#endif //SPADE_EQUIVALENCECLASS_H
