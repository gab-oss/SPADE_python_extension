#include "IdList.h"

IdList *IdList::join(IdList *idList, bool equals, int minSupport) {
    auto *intersection = new std::map<int, std::vector<int>*>();
    auto *newSequences = new std::vector<bool>;

    for(auto& entry : *idList->entries) {
        std::vector<int> *transAppereances = nullptr;
        if(equals) {
            transAppereances = equalOperation(entry.first, entry.second);
        } else {
            transAppereances = laterOperation(entry.first, entry.second);
        }

        if(transAppereances != nullptr) {
            intersection->emplace(entry.first, transAppereances);
            if(newSequences->size() <= entry.first) {
                int size = entry.first - newSequences->size() + 1;
                for(int i = 0; i < size; i++) {
                    newSequences->push_back(false);
                }
            }
            newSequences->at(entry.first) = true;
        }
    }
    auto output = new IdList(intersection);
    output->sequences = newSequences;
    return output;
}

std::vector<int> *IdList::equalOperation(int sid, std::vector<int> *transAppereances) {
    if(entries->find(sid) == entries->end() || entries->at(sid)->empty())
        return nullptr;
    auto transAppearOfIdList = entries->at(sid);
    auto result = new std::vector<int>();
    int idx = -1;

    for(int i = 0; i < transAppereances->size() && idx < 0; i++) {
        int eid = transAppereances->at(i);
        if(transAppearOfIdList->at(0) < eid)
            idx = i;
    }

    if(idx >= 0) {
        for(int i = idx; i < transAppereances->size(); i++) {
            result->push_back(transAppereances->at(i));
        }
    }

    if(result->empty())
        return nullptr;

    return  result;
}

std::vector<int> *IdList::laterOperation(int sid, std::vector<int> *transAppereances) {
    if(entries->find(sid) == entries->end() || entries->at(sid)->empty())
        return nullptr;
    auto transAppearOfIdList = entries->at(sid);
    auto result = new std::vector<int>();
    int idx = 0;
    std::vector<int> *exploreVec, *searchVec;
    if(transAppearOfIdList->size() <= transAppereances->size()) {
        exploreVec = transAppearOfIdList;
        searchVec = transAppereances;
    } else {
        exploreVec = transAppereances;
        searchVec = transAppearOfIdList;
    }

    for(auto eid : *exploreVec) {
        for(int i = idx; i < searchVec->size(); i++) {
            int comp;
            if(searchVec->at(i) > eid) comp = 1;
            else if (searchVec->at(i) < eid) comp = -1;
            else comp = 0;

            if(comp >= 0) {
                if(comp == 0) {
                    result->push_back(eid);
                    idx = ++i;
                }
                break;
            }
        }
    }

    if(result->empty())
        return nullptr;

    return result;
}
