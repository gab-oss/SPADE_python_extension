#ifndef SPADE_SPADE_HPP
#define SPADE_SPADE_HPP

#include <iostream>
#include <vector>
#include "EquivalenceClass.h"
#include "Pattern.h"

class Spade {
    std::vector<EquivalenceClass *> *frequentItems;

	std::map<int, std::vector<Pattern *> *> *frequentPatterns;

    std::vector<Pattern *> *getPatterns(std::vector<EquivalenceClass *> *frequentItems);

    int frequentPatternCount;

    int joinCount;

public:
	Spade() {
		frequentPatterns = new std::map<int, std::vector<Pattern *> *>;
		for (int i = 1; i < 10; i++)
			frequentPatterns->insert({ i, new std::vector<Pattern *> });
	}

    void run(std::string filepath, double sup, bool depthFirst);

	void addPatterns(std::vector<Pattern *> *patterns) {
		for (auto &pattern : *patterns) {
			frequentPatterns->at(pattern->getElements()->size())->push_back(pattern);
		}
	}

    void printResults() {
        std::cout << "frequentPatternCount:" << frequentPatternCount << std::endl;
        std::cout << "joinCount:" << joinCount << std::endl;
        for(auto &item : *frequentItems) {
            for(auto &el : *item->getClassIdentifier()->getElements()) {
                std::cout << el->getId() << ", ";
            }
            std::cout << "sup:" << item->getIdList()->getSupport() << " (";
            for(auto &entry : *item->getIdList()->getEntries()) {
                std::cout << entry.first << " | ";
                for(auto &id : *entry.second) {
                    std::cout << id << ", ";
                }
            }
            std::cout << ")" << std::endl << std::endl;
        }
		for (auto &patternList : *frequentPatterns) {
			for (auto &pattern : *patternList.second) {
				for (auto &el : *pattern->getElements()) {
					std::cout << el->getId() << ", ";
				}
				std::cout << " | ";
			}
			std::cout << std::endl;
		}
    }
};


#endif //SPADE_SPADE_HPP
