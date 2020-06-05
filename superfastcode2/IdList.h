#ifndef SPADE_IDLIST_H
#define SPADE_IDLIST_H

#include "Pattern.h"
#include <map>
#include <algorithm>

class IdList {
    std::map<int, std::vector<int> *> *entries = new std::map<int, std::vector<int> *>();
    std::vector<bool> *sequences = new std::vector<bool>;

    std::vector<int> *equalOperation(int sid, std::vector<int> *transAppereances);

    std::vector<int> *laterOperation(int sid, std::vector<int> *transAppereances);

public:
    IdList() = default;

    explicit IdList(std::map<int, std::vector<int> *> *entries) : entries(entries) {
        sequences = new std::vector<bool>(entries->size());
    }

    int getSupport() {
        return sequences->size();
    }

    void setAppearingSequences(Pattern *pattern) {
        pattern->setAppearingIn(sequences);
    }

    void addAppereance(int seq, long timestamp) {
        std::vector<int> *entry = nullptr;
        if(entries->find(seq) == entries->end()) {
            entry = new std::vector<int>;
        } else {
            entry = entries->at(seq);
        }
        if(std::find(entry->begin(), entry->end(), timestamp) == entry->end()) {
            entry->push_back(timestamp);
            entries->insert({seq, entry});
            if(sequences->size() <= seq) {
                int size = seq - sequences->size() + 1;
                for(int i = 0; i < size; i++) {
                    sequences->push_back(false);
                }
            }
            sequences->at(seq) = true;
        }
    }

    IdList *join(IdList *idList, bool equals, int minSupport);

    std::map<int, std::vector<int> *> *getEntries() { return entries; };
};


#endif //SPADE_IDLIST_H
