#include "SequenceDatabase.h"
#include "Event.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>

void SequenceDatabase::loadFile(std::string path, double minSupport) {
	// load file to a list of Event objects
	// eventually should only contain algorithm's main function call with loading moved to SequenceDatabase > loadFile(...) (?)
	/*
	std::string line;
	std::ifstream myfile(path);
	//std::list<Event*> events; // DANE
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			std::stringstream lineStream(line);
			int seqId, numItems, item;
			std::string eventId; // convertion to unix time (int)?
			auto *items = new std::vector<int>;
			lineStream >> seqId;
			lineStream >> eventId;
			lineStream >> numItems;
			for (int i = 0; i < numItems; ++i) {
				lineStream >> item;
				items->push_back(item);
			}
			//events.push_back(new Event(seqId, eventId, items));
			addSequence(eventId, items);
		}
		myfile.close();
	}
	else std::cout << "Unable to open file"; // should throw
	*/
	addSequence("a", new std::map<long, std::vector<int>*>({ {10, new std::vector<int>({2,2,2,4})},
															{15, new std::vector<int>({1,2,2,4})} }));
	addSequence("b", new std::map<long, std::vector<int>*>({ {15, new std::vector<int>({3,4,4})} }));
	addSequence("c", new std::map<long, std::vector<int>*>({ {10, new std::vector<int>({3,1,4})}, 
															{20, new std::vector<int>({2,5,4}) }}));

    //double support = minSupport * sequences->size();

    auto *itemsToRemove = new std::vector<Item*>;
    for(auto& pair : *frequentItems) {
        if(pair.second->getIdList()->getSupport() < minSupport) {	//prev support
            itemsToRemove->push_back(pair.first);
        } else {
            pair.second->getIdList()->setAppearingSequences(pair.second->getClassIdentifier());
        }
    }
    for(auto &item : *itemsToRemove) {
        frequentItems->erase(item);
    }

}

void SequenceDatabase::addSequence(std::string seqId, std::map<long, std::vector<int>*> *integers) {
    auto *sequence = new std::map<long, std::vector<Item *> *>;

    for (auto &integer : *integers) {
		long timestamp = integer.first;
		auto *itemset = new std::vector<Item *>;
        for (auto &id : *integer.second) {
            auto existing = std::find_if(frequentItems->begin(), frequentItems->end(), [id](std::pair<Item* const, EquivalenceClass*> pair) {
                return pair.first->getId() == id;
            });
            EquivalenceClass *ec = *existing == *(frequentItems->end()) ? nullptr : existing->second;
            IdList *idList = nullptr;
            if (ec == nullptr) {
                idList = new IdList();
                auto *item = new Item(id, false);
                ec = new EquivalenceClass(new Pattern(new std::vector<Item*>({item})), idList);
                frequentItems->insert({item, ec});
            }
            idList = ec->getIdList();
            idList->addAppereance(sequences->size(), timestamp);

            auto *item = new Item(id, true);
            itemset->push_back(item);
        }
        sequence->insert({timestamp, itemset});
        timestamp++;
    }
	sequences->insert({seqId, sequence });
}

void SequenceDatabase::reduceDatabase(std::vector<Item *> *items) {
    for(auto &s : *sequences) {
        auto itemset = s.second->begin();
        while(itemset != s.second->end()) {
            auto item = (*itemset).second->begin();
            while(item != (*itemset).second->end()) {
                if(std::find(items->begin(),items->end(),*item) == items->end()) {
                    (*itemset).second->erase(item);
                } else {
                    item++;
                }
            }
        }
        if((*itemset).second->empty()) {
            s.second->erase(itemset);
        } else {
            itemset++;
        }
    }
}
