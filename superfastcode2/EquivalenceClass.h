#ifndef SPADE_EQUIVALENCECLASS_H
#define SPADE_EQUIVALENCECLASS_H

#include <list>
#include "Pattern.h"
#include "IdList.h"

class EquivalenceClass {

    Pattern *classId;
    IdList *idList;
    std::list<EquivalenceClass *> *members = new std::list<EquivalenceClass *>;
public:
    explicit EquivalenceClass(Pattern *classId = nullptr, IdList *idList = nullptr,
                     std::list<EquivalenceClass *> *members = new std::list<EquivalenceClass *>) : classId(classId), idList(idList),
                                                                         members(members) {}

    void addMember(EquivalenceClass *eqClass) { members->push_back(eqClass); }

    void setIdList(IdList *idList) { this->idList = idList; }

    IdList *getIdList() { return idList; }

    Pattern *getClassIdentifier() const { return classId; }

    std::list<EquivalenceClass *> *getClassMembers() const { return members; }
};


#endif //SPADE_EQUIVALENCECLASS_H
