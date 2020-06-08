#include "SequenceDatabase.h"
#include "Event.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>

void SequenceDatabase::loadFile(std::string path, double minSupport) {
	// load file to a list of Event objects
	// eventually should only contain algorithm's main function call with loading moved to SequenceDatabase > loadFile(...) (?)
	
	std::string line;
	std::ifstream myfile(path);
	auto events = new std::map<int, std::map<int, std::vector<int>*>*>; 
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			std::stringstream lineStream(line);
			int seqId, eventId, numItems, item;
			auto items = new std::vector<int>;
			lineStream >> seqId;
			lineStream >> eventId;
			lineStream >> numItems;
			for (int i = 0; i < numItems; ++i) {
				lineStream >> item;
				items->push_back(item);
			}
			auto event = new std::vector<int>({ *items });
			if (events->find(seqId) == events->end())
				events->insert({ seqId, new std::map<int, std::vector<int>*>({{eventId, event}}) });
			else
				events->at(seqId)->insert({ eventId, event });
		}
		myfile.close();
	}
	else std::cout << "Unable to open file"; // should throw
	
	for(auto e : *events)
		addSequence(e.first, e.second);
	/*
	addSequence(1, new std::map<int, std::vector<int>*>({ {1, new std::vector<int>({8,37,42})},
															{2, new std::vector<int>({4,11,37,42})} 
		}));
	addSequence(2, new std::map<int, std::vector<int>*>({ {1, new std::vector<int>({10,73})},
															{2, new std::vector<int>({72})},
															{3, new std::vector<int>({4,24,77})}
		}));
	addSequence(3, new std::map<int, std::vector<int>*>({ {1, new std::vector<int>({8,73,11})},
															{2, new std::vector<int>({4,77})},
															{3, new std::vector<int>({77,10})}
		}));*/
	
    absSupport = minSupport * sequences->size();
    if(absSupport < 1) absSupport = 1;

    for(auto s : *sequences) std::cout << s.first;
    std::cout<<std::endl;

    auto *itemsToRemove = new std::vector<Item*>;
    for(auto& pair : *frequentItems) {
        if(pair.second->getIdList()->getSupport() < absSupport) {
            itemsToRemove->push_back(pair.first);
            for(auto s : *sequences) std::cout << s.first;
            std::cout<<std::endl;
        } else {
            pair.second->getIdList()->setAppearingSequences(pair.second->getClassIdentifier());
            for(auto s : *sequences) std::cout << s.first;
            std::cout<<std::endl;
        }
    }
    for(auto s : *sequences) std::cout << s.first;
    std::cout<<std::endl;
    for(auto &item : *itemsToRemove) {
        frequentItems->erase(item);
    }
    for(auto s : *sequences) std::cout << s.first;
    std::cout<<std::endl;
}

void SequenceDatabase::addSequence(int seqId, std::map<int, std::vector<int>*> *integers) {
    auto *sequence = new std::map<int, std::vector<Item *> *>;

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
                ec = new EquivalenceClass(new Pattern(new std::vector<Item*>{item}), idList);
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
